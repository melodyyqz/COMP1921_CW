// library for I/O routines
#include <stdio.h>

// library for memory routines
#include <stdlib.h>

// definitions for error codes and maximum values
#include "definitions.h"

int checkFileOpen(char *outputFile, char *commentLine, unsigned char *imageData)
{
    // NULL output file
    if (outputFile == NULL)
    {
        // free memory
        free(commentLine);
        free(imageData);

        // print an error message and return error code
        printf("Error: Failed to write pgm image to file %s\n", argv[2]);
        return EXIT_BAD_OUTPUT_FILE;
    }
    return EXIT_NO_ERRORS;
}

int checkDimensionalWrite(size_t nBytesWritten, char *commentLine, unsigned char *imageData)
{
    if (nBytesWritten < 0)
    {
        // dimensional write failed then free memory
        free(commentLine);
        free(imageData);

        // print an error message and return error code
        printf("Error: Failed to write pgm image to file %s\n", argv[2]);
        return EXIT_BAD_OUTPUT_FILE;
    }
    return EXIT_NO_ERRORS;
}

int effWriteCode()
{
    // pointer for efficient write code
    for (unsigned char *nextGrayValue = imageData; nextGrayValue < imageData + nImageBytes; nextGrayValue++)
    { // per gray value get next char's column
        int nextCol = (nextGrayValue - imageData + 1) % width;

        // write the entry & whitespace
        nBytesWritten = fprintf(outputFile, "%d%c", *nextGrayValue, (nextCol ? ' ' : '\n'));

        // sanity check on write
        if (nBytesWritten < 0)
        { // data write failed then free memory
            free(commentLine);
            free(imageData);

            // print error message and return error code
            printf("Error: Failed to write pgm image to file %s\n", argv[2]);
            return EXIT_BAD_OUTPUT_FILE;
        }
    }     // per gray value

    // at this point, we are done and can exit with a success code
    return EXIT_NO_ERRORS;
}


int mainFileWrite()
{
    // open a file for writing
    FILE *outputFile = fopen(argv[2], "w");
    checkFileOpen();
    size_t nBytesWritten = fprintf(outputFile, "P2\n%d %d\n%d\n", width, height, maxGray);
}
