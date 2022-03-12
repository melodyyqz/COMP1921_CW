/***********************************/
/* COMP 1921M Programming Project  */
/* 2021-22 Spring Semester         */
/*                                 */
/* Hamish Carr                     */
/***********************************/

/***********************************/
/* A first iteration to take a pgm */
/* file in binary and convert to   */
/* ASCII or vice versa             */
/***********************************/

/***********************************/
/* Main Routine                    */
/***********************************/

/* library for I/O routines        */
#include <stdio.h>

/* library for memory routines     */
#include <stdlib.h>

// definitions for error codes and maximum values
#include "definitions.h"

// argCheck function
int argCheck(int argNum, int correctArgNum){
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

int effread(unsigned char* imageData, char* inputFile, char** argv){ 
	// pointer for efficient read code
	for (unsigned char *nextGrayValue = imageData; nextGrayValue < imageData + nImageBytes; nextGrayValue++)
		{ // per gray value
		// read next value
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
		} // per gray value

}

/***********************************/
/* main routine                    */
/*                                 */
/* CLI parameters:                 */
/* argv[0]: executable name        */
/* argv[1]: input file name        */
/* argv[2]: output file name       */
/* returns 0 on success            */
/* non-zero error code on fail     */
/***********************************/
int main(int argc, char **argv)
	{ /* main() */
	// initialising

	// the logical width & height
	// note: cannot be negative
	unsigned int width = 0, height = 0;

	// maximum gray value (assumed)
	// make it an integer for ease
	unsigned int maxGray = 255;

	// pointer to raw image data
	unsigned char *imageData = NULL;

	/* now start reading in the data         */
	/* try to open the file for text I/O     */
	/* in ASCII mode b/c the header is text  */
	// FILE *inputFile = fopen(argv[1], "r");

	// /* if it fails, return error code        */
	// if (inputFile == NULL)
	// 	return EXIT_BAD_INPUT_FILE;


	// /* we're done with the file, so close it */
	// fclose(inputFile);

	/* open a file for writing               */
	FILE *outputFile = fopen(argv[2], "w");

	/* check whether file opening worked     */
	if (outputFile == NULL)
		{ /* NULL output file */
		/* free memory                   */
		free(commentLine);
		free(imageData);

		/* print an error message        */
		printf("Error: Failed to write pgm image to file %s\n", argv[2]);	

		/* return an error code          */
		return EXIT_BAD_OUTPUT_FILE;
		} /* NULL output file */
	
	/* write magic number, size & gray value */
	size_t nBytesWritten = fprintf(outputFile, "P2\n%d %d\n%d\n", width, height, maxGray);

	/* check that dimensions wrote correctly */
	if (nBytesWritten < 0)
		{ /* dimensional write failed    */
		/* free memory                   */
		free(commentLine);
		free(imageData);

		/* print an error message        */
		printf("Error: Failed to write pgm image to file %s\n", argv[2]);	

		/* return an error code          */
		return EXIT_BAD_OUTPUT_FILE;
		} /* dimensional write failed    */

        /* pointer for efficient write code      */
        for (unsigned char *nextGrayValue = imageData; nextGrayValue < imageData + nImageBytes; nextGrayValue++)
                { /* per gray value */
		/* get next char's column        */
		int nextCol = (nextGrayValue - imageData + 1) % width;

		/* write the entry & whitespace  */
		nBytesWritten = fprintf(outputFile, "%d%c", *nextGrayValue, (nextCol ? ' ' : '\n') );

		/* sanity check on write         */
		if (nBytesWritten < 0)
			{ /* data write failed   */
			/* free memory           */
			free(commentLine);
			free(imageData);

			/* print error message   */
			printf("Error: Failed to write pgm image to file %s\n", argv[2]);	

			/* return an error code  */
			return EXIT_BAD_OUTPUT_FILE;
			} /* data write failed   */
		} /* per gray value */

	/* at this point, we are done and can exit with a success code */
	return EXIT_NO_ERRORS;
	} /* main() */