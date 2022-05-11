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

int imageData2D(int m, int n, unsigned char **newImageData, pgmFile *pgm){
    int i,j, count;
    count=0;
    for (i = 0; i<pgm->height; i++){
        for (j = 0; j<pgm->width; j++){
            newImageData[i][j] = pgm->imageData[count];
            count++;
        }
    }
    return 0;
}

int reduceFile(int factor, pgmFile *pgm, int m, int n, unsigned char *originalArray[m][n])
{
    int reducedWidth, reducedHeight, i, j, k;
    
    unsigned char **reducedArray = (unsigned char**)malloc(reducedWidth * sizeof(unsigned char*));
    for (k = 0; i<reducedWidth; k++){
        reducedArray[k] = (unsigned char*)malloc(reducedHeight * sizeof(unsigned char));
    }
    for (i = 0; i < pgm->width; i+=factor ){
        for (j = 0; j < pgm->height; j+=factor){
            reducedArray[i][j] = *originalArray[i][j];
        }
    }
    return EXIT_NO_ERRORS;
}f 

int main(char **argv, int argc)
{
    // check arguments
    if (argCheck(argc, 4) != 0)
    {
        exit(0);
    }
    // check if arguments is 0 when argCheck returns 0
    if (argc == 0)
    {
        exit(0);
    }
    // define arguments for readability
    char *inputFileName = argv[0];
    int factor = (int) *argv[1];
    char *outputFileName = argv[2];

    // creates pgm struct for the input file and output file
    pgmFile *firstPgm = (pgmFile *)malloc(sizeof(pgmFile));
    initialiseStruct(firstPgm);
    // reads input file and output file
    fileRead(inputFileName, firstPgm);
    // calculates what the height and width of the reduced file should be
    int reducedWidth = (pgm->width +factor-1) / factor;
    int reducedHeight = (pgm->height +factor-1) / factor;

    pgmFile *secondPgm = (pgmFile *)malloc(sizeof(reducedHeight*reducedWidth));
    initialiseStruct(secondPgm);
    unsigned char **newImageData = (unsigned char **)malloc(firstPgm->height * sizeof(unsigned char*));
    for (int i = 0; i < firstPgm->height; i++){
        newImageData[i] = (unsigned char *)malloc(firstPgm->width * sizeof(unsigned char));
    }
    imageData2D(firstPgm->width, firstPgm->height, newImageData, firstPgm);
    // writes reduced file
    FILE *outputFile = fopen(outputFileName, "w");
    if (firstPgm->magic_number[1]=='5')
        fileWrite(outputFileName, secondPgm,5);
    if (firstPgm->magic_number[1]=='2')
        fileWrite(outputFileName, secondPgm,2);    
    size_t nBytesWritten = fprintf(outputFile, "P%i\n%d %d\n%d\n", (int)firstPgm->magic_number[1], firstPgm->width, firstPgm->height, firstPgm->gray);
}