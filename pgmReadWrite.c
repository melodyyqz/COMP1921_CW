// library for I/O routines
#include <stdio.h>

// library for memory routines
#include <stdlib.h>

// definitions for error codes and maximum values
#include "definitions.h"
#include "fileHandling.h"


int fileRead(char *fileName, pgmFile *thePgm)
{
    // char* fileName = argv[argNum];
    FILE *inputFile = fopen(fileName, "r");
	// if it fails, return error code
	if (inputFile == NULL)
		return EXIT_BAD_FILENAME;
    // checks the magic numbers
	if ((checkMN(inputFile, thePgm->magic_number, fileName)!=0) ||
    // reads comment line
        (commentLine(inputFile, fileName, thePgm->commentLine)!=0) ||
    // gets width, height, and gray value
        (widthHeightGray(inputFile, fileName, thePgm)!=0))
        {
            exit(0);
        }
    // assigns memory for image data
    thePgm->nImageBytes = thePgm->width * thePgm->height * sizeof(unsigned char);
	thePgm->imageData = (unsigned char *)malloc(thePgm->nImageBytes);
    // allocates memory for image
    if ((memAlloc(thePgm->imageData, inputFile, fileName, thePgm->width, thePgm->height)!=0) ||
    // reads image data into struct
        (effRead(thePgm->imageData, inputFile, fileName, thePgm->nImageBytes)!=0))
        {
            exit(0);
        }
    return 0;
}

// aOrB allows passing in 2 or 5 for ASCII vs binary
int fileWrite(char* outputFileName, pgmFile *pgm, int aOrB)
{
    // open a file for writing
    FILE *outputFile = fopen(outputFileName, "w");
    if (checkFileOpen(outputFile, pgm->commentLine, pgm->imageData, outputFileName)!=0){
        exit(0);
    }
    size_t nBytesWritten = fprintf(outputFile, "P%i\n%d %d\n%d\n", aOrB, pgm->width, pgm->height, pgm->gray);
    
    if (checkDimensionalWrite(nBytesWritten, pgm->commentLine, pgm->imageData, outputFileName)!=0 ||
        effWriteCode(pgm->imageData, pgm->nImageBytes, pgm->width, nBytesWritten, outputFile, pgm->commentLine, outputFileName, aOrB)!=0){
            exit(0);
        }
    return 0;
}