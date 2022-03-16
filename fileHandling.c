// library for I/O routines
#include <stdio.h>

// library for memory routines
#include <stdlib.h>

// definitions for error codes and maximum values
#include "definitions.h"

// initialise the pgm structure
int initialiseStruct(pgmFile *pgm){
    pgm->width = 0;
    pgm->height = 0;
    pgm->gray = 255;
    pgm->imageData = NULL;
    pgm->commentLine = NULL;
    pgm->magic_number[0] = '0';
	pgm->magic_number[1] = '0';
	pgm->magic_Number = NULL;
    return EXIT_NO_ERRORS;
}

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
		printf("ERROR: Bad Argument Count\n");
		return EXIT_WRONG_ARG_COUNT;
	}
	return EXIT_NO_ERRORS;
}

int checkMN(FILE *inputFile, unsigned char *magic_number, char* fileName)
{
	// read in the magic number
	magic_number[0] = getc(inputFile);
	magic_number[1] = getc(inputFile);
	// sanity check on the magic number
	// failed magic number check
	printf("magic num %c", magic_number[1]);
	if (magic_number[1] != '2' && magic_number[1] != '5')
	{
		fclose(inputFile);

		// print an error message
		printf("ERROR: Bad Magic Number %s\n", fileName);

		// and return
		return EXIT_BAD_MAGIC_NUM;
	} // failed magic number check
	return EXIT_NO_ERRORS;
}

int commentLine(FILE *inputFile, char* fileName, char *commentLine)
{
	// skip past space
	int scanCount = fscanf(inputFile, " ");
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

			// print an error message and return error code
			printf("ERROR: Bad Comment Line %s\n", fileName);
			return EXIT_BAD_COMMENT;
		}
	}
	else
	{
		// not a comment line so put character back
		ungetc(nextChar, inputFile);
	}
	return EXIT_NO_ERRORS;
}

int widthHeightGray(FILE *inputFile, char* fileName, pgmFile *pgm)
{
	// scan whitespace if present
	int scanCount = fscanf(inputFile, " ");
	char *commentLine = (char *)malloc(MAX_COMMENT_LINE_LENGTH);
	// read in width, height, grays; whitespace to skip blanks
	scanCount = fscanf(inputFile, " %u %u %u", &(pgm->width), &(pgm->height), &(pgm->gray));
	// sanity checks on size & grays - must read exactly three values
	if (
		(scanCount != 3) ||
		(pgm->width < MIN_IMAGE_DIMENSION) || (pgm->width > MAX_IMAGE_DIMENSION) ||
		(pgm->height < MIN_IMAGE_DIMENSION) || (pgm->height > MAX_IMAGE_DIMENSION) ||
		(pgm->gray != 255))
	{
		// failed size sanity check then free up the memory
		free(commentLine);

		// close file pointer
		fclose(inputFile);

		if (pgm->gray != 255){
			// print an error message and return error code
			printf("ERROR: Bad Max Gray Value %s\n", fileName);
			return EXIT_BAD_MAX_GRAY;
		}

		// print an error message and return error code
		printf("ERROR: Bad Dimensions %s\n", fileName);
		return EXIT_BAD_DIMENSIONS;
	}
	return EXIT_NO_ERRORS;
}

int memAlloc(unsigned char *imageData, FILE *inputFile, char* fileName, unsigned int width, unsigned int height)
{
	// sanity check for memory allocation
	char *commentLine = (char *)malloc(MAX_COMMENT_LINE_LENGTH);
	if (imageData == NULL)
	{ // malloc failed
		// free up memory
		free(commentLine);

		// close file pointer
		fclose(inputFile);

		// print an error message
		printf("ERROR: Image Malloc Failed\n");

		// return error code
		return EXIT_IMAGE_MALLOC_FAIL;
	} // malloc failed
	// allocate the data pointer
	return EXIT_NO_ERRORS;
}

int effRead(unsigned char *imageData, FILE *inputFile, char* fileName, long nImageBytes)
{
	char *commentLine = (char *)malloc(MAX_COMMENT_LINE_LENGTH); 
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
			printf("ERROR: Bad Data %s\n", fileName);
			return EXIT_BAD_DATA;
		} // fscanf failed
		// set the pixel value
		*nextGrayValue = (unsigned char)grayValue;
	}
	return EXIT_NO_ERRORS;
}

int binaryRead(unsigned char *imageData, FILE *inputFile, char* fileName, long nImageBytes)
{
	char *commentLine = (char *)malloc(MAX_COMMENT_LINE_LENGTH); 
	// pointer for efficient read code
	unsigned char *nextGrayValue;
	printf("here");
	for (nextGrayValue = imageData; nextGrayValue < imageData + nImageBytes; nextGrayValue++)
	{
		// per gray value read next value
		int grayValue = -1;
		int scanCount = fread(nextGrayValue, 1, 1, inputFile);

		// sanity check
		if ((scanCount != 1) || (grayValue < 0) || (grayValue > 255))
		{ // fscanf failed
			// free memory
			free(commentLine);
			free(imageData);

			// close file
			fclose(inputFile);

			// print error message and return error code
			printf("ERROR: Bad Data %s\n", fileName);
			return EXIT_BAD_DATA;
		} // fscanf failed
		// set the pixel value
		*nextGrayValue = (unsigned char)grayValue;
	}
	return EXIT_NO_ERRORS;
}

