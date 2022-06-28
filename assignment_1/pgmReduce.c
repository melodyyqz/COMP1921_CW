// library for I/O routines
#include <stdio.h>

// library for memory routines
#include <stdlib.h>

// for isdigit()
#include <ctype.h>

// definitions for error codes and maximum values
#include "definitions.h"
#include "pgmReadWrite.h"
#include "fileHandling.h"

int reduceFile(int factor, pgmFile *bigPgm, pgmFile *reducedPgm)
{
    // goes through row and column
    for (int height = 0, row = 0; height<bigPgm->height; height+=factor, row++){
        for (int width = 0, col = 0; width<bigPgm->width; width+=factor, col++){
            // sets image data of the new pgm equal to the relevant data of the old pgm
            reducedPgm->imageData[row][col] = bigPgm->imageData[height][width];   
        }
    }
    return EXIT_NO_ERRORS;
}

int main(int argc, char **argv)
{
    // checks number of arguments
    (argCheck(argc, 4));
    if (argc == 1)
    {
        // outputs usage error message when no files are entered
        printf("Usage: ./pgmReduce inputImage.pgm reduction_factor outputImage.pgm\n");
        exit(0);
    }
    // checks factor entered is a positive integer
    int factor = atoi(argv[2]);
    if (factor == 0) {
        printf("ERROR: Miscellaneous (non-numeric scaling factor)\n");
        exit(EXIT_MISC);
    } else if (factor < 0) {
        printf("ERROR: Miscellaneous (negative scaling factor)\n");
        exit(EXIT_MISC);
    }
    // creates pgm struct for the input file and output file
    pgmFile *firstPgm = (pgmFile *)malloc(sizeof(pgmFile));
    initialiseStruct(firstPgm);
    
    // reads input file and output file
    fileRead(argv[1], firstPgm);
    
    // calculates what the height and width of the reduced file should be
    int reducedWidth = (firstPgm->width +factor-1) / factor;
    int reducedHeight = (firstPgm->height +factor-1) / factor;
    
    // allocates, initialises and sets correct values for the second pgm structure
    pgmFile *secondPgm = (pgmFile *)malloc(sizeof(pgmFile));
    initialiseStruct(secondPgm);
    secondPgm->height = reducedHeight;
    secondPgm->width = reducedWidth;
    secondPgm->gray = firstPgm->gray;
    secondPgm->magic_number[0] = firstPgm->magic_number[0];
    secondPgm->magic_number[1] = firstPgm->magic_number[1];

    // allocates memory dynamically for 2d array image data
    secondPgm->imageData = (unsigned char **)malloc(secondPgm->height * sizeof(*secondPgm->imageData));
    for (int height = 0; height < secondPgm->height; height++){
        secondPgm->imageData[height] = (unsigned char *)malloc(secondPgm->width * sizeof(unsigned char));    
    }
    // calls function to reduce the pgm structure
    reduceFile(factor, firstPgm, secondPgm);
    // opens file for writing
    FILE *outputFile = fopen(argv[3], "w");
    // writes the data stored in secondPgm to file
    // write method depends on whether the file is binary or ascii
    if (firstPgm->magic_number[1]=='5')
        fileWrite(argv[3], secondPgm,2);
    if (firstPgm->magic_number[1]=='2')
        fileWrite(argv[3], secondPgm,2);  
    printf("REDUCED\n");
    // frees memory from both pgm structs
    freeMemory(firstPgm);
    freeMemory(secondPgm);
    return EXIT_NO_ERRORS;
}