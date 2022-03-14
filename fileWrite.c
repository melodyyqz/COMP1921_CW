// library for I/O routines
#include <stdio.h>

// library for memory routines
#include <stdlib.h>

// definitions for error codes and maximum values
#include "definitions.h"


int checkFileOpen(FILE *outputFile, char *commentLine, unsigned char *imageData, char* outputFileName)
{
    // NULL output file
    if (outputFile == NULL)
    {
        // free memory
        free(commentLine);
        free(imageData);

        // print an error message and return error code
        printf("Error: Failed to write pgm image to file %s\n", outputFileName);
        return EXIT_BAD_OUTPUT_FILE;
    }
    return EXIT_NO_ERRORS;
}

int checkDimensionalWrite(size_t nBytesWritten, char *commentLine, unsigned char *imageData, char* outputFileName)
{
    if (nBytesWritten < 0)
    {
        // dimensional write failed then free memory
        free(commentLine);
        free(imageData);

        // print an error message and return error code
        printf("Error: Failed to write pgm image to file %s\n", outputFileName);
        return EXIT_BAD_OUTPUT_FILE;
    }
    return EXIT_NO_ERRORS;
}

int effWriteCode(unsigned char *imageData, long nImageBytes, unsigned int width, size_t nBytesWritten, FILE *outputFile, 
                char *commentLine, char* outputFileName)
{
    // pointer for efficient write code
    unsigned char *nextGrayValue;
    for (nextGrayValue = imageData; nextGrayValue < imageData + nImageBytes; nextGrayValue++)
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
            printf("Error: Failed to write pgm image to file %s\n", outputFileName);
            return EXIT_BAD_OUTPUT_FILE;
        }
    }     // per gray value

    // at this point, we are done and can exit with a success code
    return EXIT_NO_ERRORS;
}


int FileWrite(char* outputFileName, pgmFile *pgm)
{
    // open a file for writing
    FILE *outputFile = fopen(outputFileName, "w");
    checkFileOpen(outputFile, pgm->commentLine, pgm->imageData, outputFileName);
    size_t nBytesWritten = fprintf(outputFile, "P2\n%d %d\n%d\n", pgm->width, pgm->height, pgm->gray);
    checkDimensionalWrite(nBytesWritten, pgm->commentLine, pgm->imageData, outputFileName);
    effWriteCode(pgm->imageData, pgm->nImageBytes, pgm->width, nBytesWritten, outputFile, pgm->commentLine, outputFileName);
}