// library for I/O routines
#include <stdio.h>

// library for memory routines
#include <stdlib.h>

// definitions for error codes and maximum values
#include "definitions.h"
#include "pgmReadWrite.h"
#include "fileHandling.h"

/*
the plan:
- identify width and height of reduced file
- read through array with a counter, if modulo factor = 0 then save to new file and counter++
- when counter = width, new line
- repeat
*/

// calculates what the height of the reduced file should be
int reducedHeight(int factor, pgmFile *pgm){
    return (pgm->height / factor);
}

// calculates what the width of the reduced file should be
int reducedWidth(int factor, pgmFile *pgm){
    return (pgm->width / factor);
}

int saveReduced(int factor, pgmFile *pgm, int reducedWidth, int reducedHeight, FILE *outputFile, size_t nBytesWritten){
    int count = 0;
    unsigned char *nextGrayValue;
    for (int i = 0; i <= reducedWidth * reducedHeight; i++) {
        if (i % factor == 0){
            nBytesWritten = fwrite(nextGrayValue, 1, 1, outputFile); // check where address, todo: look for smth related to writing to width and height        
        }
        if (count == reducedWidth){
            count=0;
        }
        nextGrayValue++;
    }
    return 0;
}

int main(char** argv, int argc){
    // check arguments
    if (argCheck(argc, 4, argv[0])!=0){
        exit(0);
    }
    // check if arguments is 0 when argCheck returns 0
    if (argc==0){
        exit(0);
    }
    // define arguments for readability
    char* inputFileName = argv[0];
    int factor = argv[1];
    char* outputFileName = argv[2];
    pgmFile *firstPgm = (pgmFile *)malloc(sizeof(pgmFile));
    initialiseStruct(firstPgm);
    fileRead(inputFileName, firstPgm);
}