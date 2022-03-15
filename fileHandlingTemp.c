// library for I/O routines
#include <stdio.h>

// library for memory routines
#include <stdlib.h>

// definitions for error codes and maximum values
#include "definitions.h"


// argCheck function
int argCheck(int argNum, int correctArgNum, char* fileName)
{
	// if number of arguments is only 1
	if (argNum == 1)
	{
		// print error message
		printf("Usage: %s input_file output_file\n", fileName);
		// return error code
		return 0;
	}
	else if (argNum != correctArgNum)
	{
		// return error code
		return EXIT_WRONG_ARG_COUNT;
	}
	return EXIT_NO_ERRORS;
}

int checkMN(FILE *inputFile, unsigned char *magic_number, unsigned short *magic_Number, char* fileName)
{
	// read in the magic number
	magic_number[0] = getc(inputFile);
	magic_number[1] = getc(inputFile);
	// sanity check on the magic number
	// failed magic number check
	if (*magic_Number != MAGIC_NUMBER_ASCII_PGM)
	{
		fclose(inputFile);

		// print an error message
		printf("Error: Bad magic number from %s\n", fileName);

		// and return
		return EXIT_BAD_MAGIC_NUM;
	} // failed magic number check
	return EXIT_NO_ERRORS;
}

int commentLine(FILE *inputFile, char* fileName, char *commentLine)
{
	// check for a comment line
	char nextChar = fgetc(inputFile);
	// comment line
	if (nextChar == '#')
	{
		// allocate buffer
		commentLine = (char *)malloc(MAX_COMMENT_LINE_LENGTH);
		// reads a line and capture return value
		char *commentString = fgets(commentLine, MAX_COMMENT_LINE_LENGTH, inputFile);
		// NULL comment read
		if (commentString == NULL)
		{
			// free memory
			free(commentLine);
			// close file
			fclose(inputFile);

			// print an error message
			printf("Error: Bad comment line in %s\n", fileName);

			// and return
			return EXIT_BAD_COMMENT;
		} // NULL comment read
	}	  // comment line
	else
	{
		// not a comment line so put character back
		ungetc(nextChar, inputFile);
	}
	return EXIT_NO_ERRORS;
}

int widthHeightGray(FILE *inputFile, char* fileName, unsigned int width, unsigned int height, unsigned int maxGray)
{
	// scan whitespace if present
	int scanCount = fscanf(inputFile, " ");

	// read in width, height, grays; whitespace to skip blanks
	scanCount = fscanf(inputFile, " %u %u %u", &(width), &(height), &(maxGray));

	// sanity checks on size & grays - must read exactly three values
	if (
		(scanCount != 3) ||
		(width < MIN_IMAGE_DIMENSION) || (width > MAX_IMAGE_DIMENSION) ||
		(height < MIN_IMAGE_DIMENSION) || (height > MAX_IMAGE_DIMENSION) ||
		(maxGray != 255))
	{
		// failed size sanity check then free up the memory
		free(commentLine);

		// close file pointer
		fclose(inputFile);

		if (maxGray != 255){
			// print an error message and return error code
			printf("Error: Bad gray value from file %s\n", fileName);
			return EXIT_BAD_MAX_GRAY;
		}

		// print an error message and return error code
		printf("Error: Bad dimensions from file %s\n", fileName);
		return EXIT_BAD_DIMENSIONS;
	}
	return EXIT_NO_ERRORS;
}

int memalloc(unsigned char *imageData, FILE *inputFile, char* fileName, unsigned int width, unsigned int height)
{
	// sanity check for memory allocation
	if (imageData == NULL)
	{ // malloc failed
		// free up memory
		free(commentLine);

		// close file pointer
		fclose(inputFile);

		// print an error message
		printf("Error: Failed to allocate memory\n");

		// return error code
		return EXIT_IMAGE_MALLOC_FAIL;
	} // malloc failed
	// allocate the data pointer

	return EXIT_NO_ERRORS;
}

int effread(unsigned char *imageData, FILE *inputFile, char* fileName, long nImageBytes)
{
	// pointer for efficient read code
	unsigned char *nextGrayValue;
	for (nextGrayValue = imageData; nextGrayValue < imageData + nImageBytes; nextGrayValue++)
	{
		// per gray value read next value
		int grayValue = -1;
		int scanCount = fscanf(inputFile, " %u", &grayValue);

		// sanity check
		if ((scanCount != 1) || (grayValue < 0) || (grayValue > 255))
		{ // fscanf failed
			// free memory
			free(commentLine);
			free(imageData);

			// close file
			fclose(inputFile);

			// print error message and return error code
			printf("Error: Failed on reading in data from file %s\n", fileName);
			return EXIT_BAD_DATA;
		} // fscanf failed

		// set the pixel value
		*nextGrayValue = (unsigned char)grayValue;
	}
	return EXIT_NO_ERRORS;
}

int FileHandling(char* fileName, pgmFile *pgm)
{
	FILE *inputFile = fopen(fileName, "r");
	// if it fails, return error code
	if (inputFile == NULL)
		return EXIT_BAD_FILENAME;
	checkMN(inputFile, pgm->magic_number, pgm->magic_Number, fileName);
	commentLine(inputFile, fileName, pgm->commentLine);
	widthHeightGray(inputFile, fileName, pgm->width, pgm->height, pgm->gray);
	memalloc(pgm->imageData, inputFile, fileName, pgm->width, pgm->height);
	pgm->nImageBytes = pgm->width * pgm->height * sizeof(unsigned char);
	pgm->imageData = (unsigned char *)malloc(pgm->nImageBytes);
	effread(pgm->imageData, inputFile, fileName, pgm->nImageBytes);

	// we're done with the file, so close it
	fclose(inputFile);
	return EXIT_NO_ERRORS;
}
