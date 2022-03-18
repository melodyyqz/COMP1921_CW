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

int saveReduced(int factor, pgmFile *pgm, int reducedWidth, int reducedHeight, FILE *outputFile, size_t nBytesWritten)
{
    int count = 0, i;
    unsigned char *nextGrayValue;
    // only loops the number of times of the size of the reduced image
    for (i = 0; i <= reducedWidth * reducedHeight; i++)
    {
        // writes to file if the it is the first byte or the byte equal to 0 when there is no remainder when divided by the factor
        if (count == 0 || count % factor == 0)
        {
            nBytesWritten = fwrite(nextGrayValue, 1, 1, outputFile);
        }
        // if the count reaches the width, reset count so it starts a new line
        if (count == reducedWidth)
        {
            count = 0;
        }
        // increment values
        count++;
        nextGrayValue++;
    }
    return EXIT_NO_ERRORS;
}

int main(char **argv, int argc)
{
    // check arguments
    if (argCheck(argc, 4, argv[0]) != 0)
    {
        exit(0);
    }
    // check if arguments is 0 when argCheck returns 0
    if (argc == 0)
    {
        exit(0);
    }
    // define arguments for readability
    char *inputFileName = argv[0];
    int factor = (int)argv[1];
    char *outputFileName = argv[2];

    // creates pgm struct for the input file and output file
    pgmFile *firstPgm = (pgmFile *)malloc(sizeof(pgmFile));
    initialiseStruct(firstPgm);
    pgmFile *secondPgm = (pgmFile *)malloc(sizeof(pgmFile));
    initialiseStruct(secondPgm);
    // reads input file and output file
    fileRead(inputFileName, firstPgm);
    fileRead(outputFileName, secondPgm);
    // calculates what the height of the reduced file should be
    int reducedHeight = firstPgm->height / factor;

    // calculates what the width of the reduced file should be
    int reducedWidth = firstPgm->width / factor;
    // writes reduced file
    FILE *outputFile = fopen(outputFileName, "w");
    size_t nBytesWritten = fprintf(outputFile, "P%i\n%d %d\n%d\n", (int)firstPgm->magic_number[1], firstPgm->width, firstPgm->height, firstPgm->gray);
    saveReduced(factor, firstPgm, reducedWidth, reducedHeight, outputFile, nBytesWritten);
}