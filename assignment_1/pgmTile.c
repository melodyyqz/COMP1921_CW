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

    // creates pgm struct for the input file
    pgmFile *firstPgm = (pgmFile *)malloc(sizeof(pgmFile));
    initialiseStruct(firstPgm);
    
    // reads input file
    fileRead(argv[1], firstPgm);

    // allocates memory dynamically for 2d array image data
    secondPgm->imageData = (unsigned char **)malloc(secondPgm->height * sizeof(*secondPgm->imageData));
    for (int height = 0; height < secondPgm->height; height++){
        secondPgm->imageData[height] = (unsigned char *)malloc(secondPgm->width * sizeof(unsigned char));    
    }
    // allocates and initialises correct values for the second pgm structure
    pgmFile *secondPgm = (pgmFile *)malloc(sizeof(pgmFile));
    initialiseStruct(secondPgm);
    // opens file for writing
    FILE *outputFile = fopen(argv[3], "w");
    // writes the data stored in secondPgm to file
    // write method depends on whether the file is binary or ascii
    if (firstPgm->magic_number[1]=='5')
        fileWrite(argv[3], secondPgm,2);
    if (firstPgm->magic_number[1]=='2')
        fileWrite(argv[3], secondPgm,2);  

    // frees memory for pgm structs
    freeMemory(firstPgm);
    freeMemory(secondPgm);
    return EXIT_NO_ERRORS;
}