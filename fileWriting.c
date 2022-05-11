// library for I/O routines
#include <stdio.h>

// library for memory routines
#include <stdlib.h>

// definitions for error codes and maximum values
#include "definitions.h"

int checkFileOpen(FILE *outputFile, pgmFile* pgm, char *outputFileName)
{
    // NULL output file
    if (outputFile == NULL)
    {
        // free memory
        free(pgm->commentLine);
        free(*pgm->imageData);

        // print an error message and return error code
        printf("ERROR: Bad File Name (%s)\n", outputFileName);
        return EXIT_BAD_FILENAME;
    }
    return EXIT_NO_ERRORS;
}

int checkDimensionalWrite(size_t nBytesWritten, pgmFile *pgm, char *outputFileName)
{
    if (nBytesWritten < 0)
    {
        // dimensional write failed then free memory
        free(pgm->commentLine);
        free(*pgm->imageData);

        // print an error message and return error code
        printf("ERROR: Bad Dimensions (%s)\n", outputFileName);
        return EXIT_BAD_DIMENSIONS;
    }
    return EXIT_NO_ERRORS;
}

int effWriteCode(pgmFile *pgm, size_t nBytesWritten, FILE *outputFile, char *outputFileName, int targetMagicNum)
{
    // loop through height of 2d array storing image data
    for (int i=0; i<pgm->height; i++){
        // loop through width
        for (int j=0; j<pgm->width; j++){
            // check if ASCII
            if (targetMagicNum == 2)
                {
                    nBytesWritten = fprintf(outputFile, "%d%c", pgm->imageData[i][j], ' ');
                }
            // check if binary
            if (targetMagicNum == 5)
                {
                    nBytesWritten = fwrite(&pgm->imageData[i][j], sizeof(unsigned char), 1, outputFile);
                }
            if (nBytesWritten < 0)
            { // data write failed then free memory
                free(pgm->commentLine);
                free(*pgm->imageData);

                // print error message and return error code
                printf("write");
                printf("ERROR: Bad Data (%s)\n", outputFileName);
                return EXIT_BAD_DATA;
            }
        }
        nBytesWritten = fprintf(outputFile, "%c", '\n');
    }

    // at this point, we are done and can exit with a success code
    return EXIT_NO_ERRORS;
}
