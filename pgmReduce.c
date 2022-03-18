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


int saveReduced(int factor, pgmFile *pgm, int reducedWidth, int reducedHeight, FILE *outputFile, size_t nBytesWritten){
    int count = 0, i;
    unsigned char *nextGrayValue;
    for (i = 0; i <= reducedWidth * reducedHeight; i++) {
        if (count == 0 || count % factor == 0){
            nBytesWritten = fwrite(nextGrayValue, 1, 1, outputFile); // check where address, todo: look for smth related to writing to width and height        
        }
        if (count == reducedWidth){
            count=0;
        }
        count++;
        nextGrayValue++;
    }
    return 0;
}

int main(char** argv, int argc){
    printf("here\n");
    // check arguments
    if (argCheck(argc, 4, argv[0])!=0){
        printf("%i", argc);
        exit(0);
    }
    printf("huh");
    // check if arguments is 0 when argCheck returns 0
    if (argc==0){
        exit(0);
    }
    printf("here1\n");
    // define arguments for readability
    char* inputFileName = argv[0];
    int factor = (int) argv[1];
    char* outputFileName = argv[2];

    // creates pgm struct for the input file and output file
    pgmFile *firstPgm = (pgmFile *)malloc(sizeof(pgmFile));
    initialiseStruct(firstPgm);
    pgmFile *secondPgm = (pgmFile *)malloc(sizeof(pgmFile));
    initialiseStruct(secondPgm);
    printf("here2\n");
    // reads input file and output file
    fileRead(inputFileName, firstPgm);
    fileRead(outputFileName, secondPgm);
    printf("here3\n");
    // calculates what the height of the reduced file should be
    int reducedHeight = firstPgm->height / factor;

    // calculates what the width of the reduced file should be
    int reducedWidth = firstPgm->width / factor;
    printf("here4\n");
    // writes reduced file
    FILE *outputFile = fopen(outputFileName, "w");
    printf("here5\n");
    size_t nBytesWritten = fprintf(outputFile, "P%i\n%d %d\n%d\n", (int) firstPgm->magic_number[1], firstPgm->width, firstPgm->height, firstPgm->gray);
    saveReduced(factor, firstPgm, reducedWidth, reducedHeight, outputFile, nBytesWritten);

}