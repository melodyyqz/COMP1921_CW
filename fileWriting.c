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
    for (int height=0; height<pgm->height; height++){
        // loop through width
        for (int width=0; width<pgm->width; width++){
            // check if ASCII
            if (targetMagicNum == 2)
                nBytesWritten = fprintf(outputFile, "%d%c", pgm->imageData[height][width], ' ');
            // check if binary
            if (targetMagicNum == 5)
                nBytesWritten = fwrite(&pgm->imageData[height][width], sizeof(unsigned char), 1, outputFile);
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
        if (targetMagicNum == 2)
            nBytesWritten = fprintf(outputFile, "%c", '\n');
    }

    // at this point, we are done and can exit with a success code
    return EXIT_NO_ERRORS;
}
