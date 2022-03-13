// library for I/O routines
#include <stdio.h>

// library for memory routines
#include <stdlib.h>

// definitions for error codes and maximum values
#include "definitions.h"

// argCheck function
int argCheck(int argNum, int correctArgNum, char** argv){
	// if actual number of arguments is different to what it should be
	if (argNum != correctArgNum)
	{
	// print error message
	printf("Usage: %s input_file output_file\n", argv[0]);
	// return error code
	return EXIT_WRONG_ARG_COUNT;
	}
	return EXIT_NO_ERRORS;
}

int checkMN(char* inputFile, unsigned char* magic_number, unsigned short *magic_Number, char** argv){
	

	// read in the magic number
	magic_number[0] = getc(inputFile);
	magic_number[1] = getc(inputFile); 

	// sanity check on the magic number
	// failed magic number check
	if (*magic_Number != MAGIC_NUMBER_ASCII_PGM){
		fclose(inputFile);

		// print an error message
		printf("Error: Failed to read pgm image from file %s\n", argv[1]);	
		
		// and return
		return EXIT_BAD_INPUT_FILE;
	} // failed magic number check
	return EXIT_NO_ERRORS;

}

int commentLine(char* inputFile, char** argv){
	char *commentLine = NULL;
	// check for a comment line
	char nextChar = fgetc(inputFile);
	// comment line
	if (nextChar == '#')
		{
		// allocate buffer
		commentLine = (char *) malloc(MAX_COMMENT_LINE_LENGTH);
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
			printf("Error: Failed to read pgm image from file %s\n", argv[1]);	
		
			// and return
			return EXIT_BAD_INPUT_FILE;
			} // NULL comment read
		} // comment line
	else {
		// not a comment line so put character back
		ungetc(nextChar, inputFile);
		}
	return EXIT_NO_ERRORS;
}

int whg(char* inputFile, char** argv, unsigned int width, unsigned int height, unsigned int maxGray){
	// scan whitespace if present
	int scanCount = fscanf(inputFile, " ");

	// read in width, height, grays
	// whitespace to skip blanks
	scanCount = fscanf(inputFile, " %u %u %u", &(width), &(height), &(maxGray));

	// sanity checks on size & grays
	// must read exactly three values
	if 	(
		(scanCount != 3				)	||
		(width 	< MIN_IMAGE_DIMENSION	) 	||
		(width 	> MAX_IMAGE_DIMENSION	) 	||
		(height < MIN_IMAGE_DIMENSION	) 	||
		(height > MAX_IMAGE_DIMENSION	) 	||
		(maxGray	!= 255		)
		)
		{ // failed size sanity check
		// free up the memory
		free(commentLine);

		// close file pointer
		fclose(inputFile);

		// print an error message
		printf("Error: Failed to read pgm image from file %s\n", argv[1]);	
		
		// and return
		return EXIT_BAD_INPUT_FILE;
		} // failed size sanity check
	return EXIT_NO_ERRORS;
}

int memalloc(unsigned char* imageData, char* inputFile, char** argv, unsigned int width, unsigned int height){
	// sanity check for memory allocation
	if (imageData == NULL)
		{ // malloc failed
		// free up memory
		free(commentLine);

		// close file pointer
		fclose(inputFile);

		// print an error message */
		printf("Error: Failed to read pgm image from file %s\n", argv[1]);	
		
		// return error code
		return EXIT_BAD_INPUT_FILE;
		} // malloc failed
	// allocate the data pointer
	long nImageBytes = width * height * sizeof(unsigned char);
	imageData = (unsigned char *) malloc(nImageBytes);
	return EXIT_NO_ERRORS;
}

int effread(unsigned char* imageData, char* inputFile, char** argv, long nImageBytes){ 
	// pointer for efficient read code
	for (unsigned char *nextGrayValue = imageData; nextGrayValue < imageData + nImageBytes; nextGrayValue++){
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

			// print error message
			printf("Error: Failed to read pgm image from file %s\n", argv[1]);	
		
			// and return
			return EXIT_BAD_INPUT_FILE;
			} // fscanf failed

		// set the pixel value
		*nextGrayValue = (unsigned char) grayValue;
		}
	return EXIT_NO_ERRORS;
}

int mainFileHandling(char** argv, unsigned char* magic_number, 
					unsigned int width, unsigned int height, unsigned int maxGray,
					unsigned char* imageData, long nImageBytes){
    FILE *inputFile = fopen(argv[1], "r");
    /* if it fails, return error code        */
	if (inputFile == NULL)
		return EXIT_BAD_INPUT_FILE;
	checkMN(inputFile, magic_number, argv);
	commentLine(inputFile, argv);
	whg(inputFile, argv, width, height, maxGray);
	memalloc(imageData, inputFile, argv, width, height);
	effread(imageData, inputFile, argv, nImageBytes);

	/* we're done with the file, so close it */
	fclose(inputFile);
	return EXIT_NO_ERRORS;
}