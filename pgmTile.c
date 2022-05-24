// library for I/O routines
#include <stdio.h>

// library for memory routines
#include <stdlib.h>

// definitions for error codes and maximum values
#include "definitions.h"
#include "pgmReadWrite.h"
#include "fileHandling.h"

int main(int argc, char **argv){
    // checks number of arguments
    (argCheck(argc, 4));
    if (argc == 1)
    {
        // outputs usage error message when no files are entered
        printf("Usage: ./pgmTile inputImage.pgm tiling_factor outputImage_<row>_<column>.pgm\n");
        exit(0);
    }
    return EXIT_NO_ERRORS;
}