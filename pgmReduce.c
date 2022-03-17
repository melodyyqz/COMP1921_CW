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

int reducedHeight(int factor, ){
    
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