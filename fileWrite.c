// library for I/O routines
#include <stdio.h>

// library for memory routines
#include <stdlib.h>

// definitions for error codes and maximum values
#include "definitions.h"


int checkFileOpen(FILE *outputFile, char *commentLine, unsigned char *imageData, char* outputFileName)
{
    // NULL output file
    printf("in checkFileOpen function");
    if (outputFile == NULL)
    {
        printf("in if statement");
        // free memory
        free(commentLine);
        free(imageData);

        // print an error message and return error code
        printf("Error: Failed to write pgm image to file %s\n", outputFileName);
        return EXIT_BAD_FILENAME;
    }
    printf("not null file");
    return EXIT_NO_ERRORS;
}
