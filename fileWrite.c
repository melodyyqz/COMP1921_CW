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
        printf("ERROR: Bad File Name %s\n", outputFileName);
        return EXIT_BAD_FILENAME;
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
        printf("ERROR: Bad Dimensions %s\n", outputFileName);
        return EXIT_BAD_DIMENSIONS;
    }
    return EXIT_NO_ERRORS;
}

int effWriteCode(unsigned char *imageData, long nImageBytes, unsigned int width, size_t nBytesWritten, FILE *outputFile, 
                char *commentLine, char* outputFileName, int targetMagicNum)
{
    // pointer for efficient write code
    printf("here");
    unsigned char *nextGrayValue;
    for (nextGrayValue = imageData; nextGrayValue < imageData + nImageBytes; nextGrayValue++)
    { // per gray value get next char's column
        int nextCol = (nextGrayValue - imageData + 1) % width;
        // write the entry & whitespace
        if (targetMagicNum == 2){
            nBytesWritten = fprintf(outputFile, "%d%c", *nextGrayValue, (nextCol ? ' ' : '\n'));
        }
        if (targetMagicNum == 5){
            nBytesWritten = fwrite(nextGrayValue, 1, 1, outputFile);
        }
        
 
        // sanity check on write
        if (nBytesWritten < 0)
        { // data write failed then free memory
            free(commentLine);
            free(imageData);

            // print error message and return error code
            printf("ERROR: Bad Data %s\n", outputFileName);
            return EXIT_BAD_DATA;
        }
    }     // per gray value

    // at this point, we are done and can exit with a success code
    return EXIT_NO_ERRORS;
}

