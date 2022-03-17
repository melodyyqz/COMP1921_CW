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

    // initialising the first pgm file and initialise the first pgm's struct
    pgmFile *firstPgm = (pgmFile *)malloc(sizeof(pgmFile));
    initialiseStruct(firstPgm);
    fileRead(argv[1], firstPgm);

    // makes the second pgm struct identical to the first pgm struct
    // pgmFile *secondPgm = firstPgm;

    // reads in the first file and writes it as binary to the second file
    // if (binaryRead(firstPgm, argv[1])==0 && fileWrite(argv[2], firstPgm, 2)==0){
    //     printf("CONVERTED\n");
    //     return 0;
    // }
    fileWrite(argv[2], firstPgm, 2);
    printf("CONVERTED\n");

}