// library for I/O routines
#include <stdio.h>

// library for memory routines
#include <stdlib.h>

// definitions for error codes and maximum values
#include "definitions.h"
#include "pgmReadWrite.h"
#include "fileHandling.h"


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
}