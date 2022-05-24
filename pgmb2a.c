// library for I/O routines
#include <stdio.h>

// library for memory routines
#include <stdlib.h>

// definitions for error codes and maximum values
#include "definitions.h"
#include "fileHandling.h"
#include "pgmReadWrite.h"

int main(int argc, char **argv)
{
    // check arguments
    if (argCheck(argc, 3) != 0)
    {
        exit(0);
    }
    // check if arguments is 0 when argCheck returns 0
    if (argc == 1)
    {
        printf("Usage: ./pgmb2a inputImage.pgm outputImage.pgm");
        exit(0);
    }

    // initialising the first pgm file and initialise the first pgm's struct
    pgmFile *firstPgm = (pgmFile *)malloc(sizeof(pgmFile));
    initialiseStruct(firstPgm);

    // read files and checks it read correctly
    if (fileRead(argv[1], firstPgm) != 0)
    {
        exit(0);
    }
    // checks if the input file is already an ascii file
    if (firstPgm->magic_number[1] != '5')
    {
        printf("ERROR: Bad Magic Number (%s)\n", argv[1]);
        exit(EXIT_BAD_MAGIC_NUM);
    }
    // converts input file to ASCII file
    if (fileWrite(argv[2], firstPgm, 2) == 0)
    {
        printf("CONVERTED\n");
    }
    freeMemory(firstPgm);
    return EXIT_NO_ERRORS;
}