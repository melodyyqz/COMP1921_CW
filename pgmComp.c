// library for I/O routines
#include <stdio.h>

// library for memory routines
#include <stdlib.h>

// definitions for error codes and maximum values
#include "definitions.h"
#include "pgmReadWrite.h"

int main(int argc, char **argv){
    // check arguments
    argCheck(argc, 3, argv[0]);
    // check if arguments is 0 when argCheck returns 0
    if (argc==0){
        exit(0);
    }

    // initialising the first pgm file
    pgmFile *firstPgm = (pgmFile *)malloc(sizeof(pgmFile));
    initialiseStruct(firstPgm);

    // initialising the second pgm file
    pgmFile *secondPgm = (pgmFile *)malloc(sizeof(pgmFile));
    initialiseStruct(secondPgm);

    // read first file
    fileRead(argv[1], firstPgm);
    printf("struct width: %i\n height: %i\n gray %i\n imageData %c\n magic number %c%c\n"
            , firstPgm->width, firstPgm->height, firstPgm->gray, firstPgm->imageData, firstPgm->magic_number[0], firstPgm->magic_number[1]);

    // read second file
    fileRead(argv[2], secondPgm);
    printf("struct width: %i\n height: %i\n gray %i\n imageData %c\n magic number %c%c\n"
            , secondPgm->width, secondPgm->height, secondPgm->gray, secondPgm->imageData, secondPgm->magic_number[0], secondPgm->magic_number[1]);

    // compare struct characteristics of the two files
}
