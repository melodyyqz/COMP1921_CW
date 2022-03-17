// library for I/O routines
#include <stdio.h>

// library for memory routines
#include <stdlib.h>

// definitions for error codes and maximum values
#include "definitions.h"
#include "pgmReadWrite.h"

int a2b(pgmFile *firstPgm, char* inputFileName, char* outputFileName){
    // makes the second pgm struct identical to the first pgm struct
    pgmFile *secondPgm = firstPgm;

    // reads in the first file and writes it as binary to the second file
    if (fileRead(inputFileName, firstPgm)==0 && fileWrite(outputFileName, secondPgm, 5)==0){
        printf("CONVERTED\n");
        return 0;
}
}

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
    a2b(firstPgm, argv[1], argv[2]);

}