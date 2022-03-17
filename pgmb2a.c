// library for I/O routines
#include <stdio.h>

// library for memory routines
#include <stdlib.h>

// definitions for error codes and maximum values
#include "definitions.h"
#include "pgmReadWrite.h"

int main(int argc, char **argv){
    // check arguments
    if (argCheck(argc, 3, argv[0])!=0){
        exit(0);
    }
    // check if arguments is 0 when argCheck returns 0
    if (argc==0){
        exit(0);
    }

    // initialising the first pgm file and initialise the first pgm's struct
    pgmFile *firstPgm = (pgmFile *)malloc(sizeof(pgmFile));
    initialiseStruct(firstPgm);
    if (fileRead(argv[1], firstPgm)!=0){
        exit(0);
    }
    if (firstPgm->magic_number[1]!='5'){
        printf("ERROR: Invalid file type\n");
        return EXIT_MISC;
    }
    if (fileWrite(argv[2], firstPgm, 2)==0){   
        printf("CONVERTED\n");
    }

}