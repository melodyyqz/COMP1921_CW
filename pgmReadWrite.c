// library for I/O routines
#include <stdio.h>

// library for memory routines
#include <stdlib.h>

// definitions for error codes and maximum values
#include "definitions.h"
#include "fileWriting.h"
#include "fileHandling.h"

int fileRead(char *fileName, pgmFile *thePgm)
{
    // char* fileName = argv[argNum];
    FILE *inputFile = fopen(fileName, "r");
    // if it fails, return error code
    if (inputFile == NULL)
    {
        printf("ERROR: Bad File Name (%s)", fileName);
        exit(EXIT_BAD_FILENAME);
    }
    // checks the magic numbers
    if ((checkMN(inputFile, thePgm->magic_number, fileName) != 0) ||
        // reads comment line
        (commentLine(inputFile, fileName, thePgm->commentLine) != 0) ||
        // gets width, height, and gray value
        (widthHeightGray(inputFile, fileName, thePgm) != 0))
    {
        exit(0);
    }
    // assigns memory for image data
    thePgm->imageData = (unsigned char **)malloc(thePgm->height * sizeof(unsigned char*));
    for (int i = 0; i < thePgm->height; i++){
        thePgm->imageData[i] = (unsigned char *)malloc(thePgm->width * sizeof(unsigned char));
    }
    // allocates memory for image
    if (memAlloc(*thePgm->imageData, inputFile, fileName, thePgm) != 0)
        // reads image data into struct
        exit(0);
    if (thePgm->magic_number[1] == '5')
    {
        if (binaryRead(thePgm, inputFile) != 0)
        {
            exit(0);
        }
    }
    else if (thePgm->magic_number[1] == '2')
    {
        if (effRead(inputFile, fileName, thePgm) != 0)
        {
            exit(0);
        }
    }
    return EXIT_NO_ERRORS;
}

// aOrB allows passing in 2 or 5 for ASCII vs binary
int fileWrite(char *outputFileName, pgmFile *pgm, int aOrB) 
{
    // open a file for writing
    FILE *outputFile = fopen(outputFileName, "w");
    // checks file is writeable
    if (outputFile == NULL)
    {
        printf("ERROR: Bad File Name (%s)", outputFileName);
        exit(EXIT_OUTPUT_FAILED);
    }
    if (checkFileOpen(outputFile, pgm, outputFileName) != 0)
    {
        exit(0);
    }
    size_t nBytesWritten = fprintf(outputFile, "P%i\n%d %d\n%d\n", aOrB, pgm->width, pgm->height, pgm->gray);

    // checks dimensions and writes to file
    if (checkDimensionalWrite(nBytesWritten, pgm, outputFileName) != 0 ||
        effWriteCode(pgm, nBytesWritten, outputFile, outputFileName, aOrB) != 0)
    {
        exit(0);
    }
    return EXIT_NO_ERRORS;
}