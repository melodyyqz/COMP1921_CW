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
	if (magic_number[1] != '2')
	{
		fclose(inputFile);

		// print an error message
		printf("Error: Bad magic number from %s\n", fileName);

		// and return
		return EXIT_BAD_MAGIC_NUM;
	} // failed magic number check
	return EXIT_NO_ERRORS;
}