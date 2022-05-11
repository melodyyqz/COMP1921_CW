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
    // pointer for efficient write code
    // unsigned char *nextGrayValue;
    // for (nextGrayValue = *pgm->imageData; nextGrayValue < *pgm->imageData + pgm->nImageBytes; nextGrayValue++)
    // { // per gray value get next char's column
    //     int nextCol = (nextGrayValue - *pgm->imageData + 1) % pgm->width;
    //     // write the entry & whitespace
    //     if (targetMagicNum == 2)
    //     {
    //         nBytesWritten = fprintf(outputFile, "%d%c", *nextGrayValue, (nextCol ? ' ' : '\n'));
    //     }
    //     if (targetMagicNum == 5)
    //     {
    //         nBytesWritten = fwrite(nextGrayValue, 1, 1, outputFile);
    //     }

    //     // sanity check on write
    //     if (nBytesWritten < 0)
    //     { // data write failed then free memory
    //         free(pgm->commentLine);
    //         free(*pgm->imageData);

    //         // print error message and return error code
    //         printf("write");
    //         printf("ERROR: Bad Data (%s)\n", outputFileName);
    //         return EXIT_BAD_DATA;
    //     }
    // } // per gray value

    for (i=0; i<pgm->height; i++){
        for (j=0; j<pgm->width; j++){
            if (targetMagicNum == 2)
                {
                    nBytesWritten = fprintf(outputFile, "%d%c", pgm->imageData[i][j], (nextCol ? ' ' : '\n'));
                }
            if (targetMagicNum == 5)
                {
                    nBytesWritten = fwrite(nextGrayValue, 1, 1, outputFile);
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
    }

    // at this point, we are done and can exit with a success code
    return EXIT_NO_ERRORS;
}
