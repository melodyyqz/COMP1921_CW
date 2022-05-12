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

int checkFactor(char **argv){
    // int num = atoi(argv[2]);
    // if (num == 0) {
    //     printf("ERROR: Miscellaneous (non-numeric scaling factor)\n");
    //     exit(EXIT_MISC);
    // } else if (num < 0) {
    //     printf("ERROR: Miscellaneous (negative scaling factor)\n");
    //     exit(EXIT_MISC);
    // }
    // return EXIT_NO_ERRORS;
}

int reduceFile(int factor, pgmFile *bigPgm, pgmFile *reducedPgm)
{
    for (int height = 0, row = 0; height<bigPgm->height; height+=factor, row++){
        for (int width = 0, col = 0; width<bigPgm->width; width+=factor, col++){
            reducedPgm->imageData[row][col] = bigPgm->imageData[height][width];   
            printf("%d", bigPgm->imageData[height][width]);
        }
    }
    return EXIT_NO_ERRORS;
}

int main(int argc, char **argv)
{
    // outputs usage error message when no files are entered
    
    printf("%i", argc);
    
    if (argCheck(argc, 4) != 0)
    {
        printf("Fail");
        exit(1);
    }
    if (argc == 1)
    {
        printf("Usage: ./pgmReduce inputImage.pgm reduction_factor outputImage.pgm\n");
        exit(0);
    }
    // check correct number of arguments are entered
    
    // {
    //     exit(1);
    // }
    // // check if arguments is 0 when argCheck returns 0
    // if (argc == 0)
    // {
    //     exit(0);
    // }
    // int factor = checkFactor(argv);

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
    
    pgmFile *secondPgm = (pgmFile *)malloc(sizeof(pgmFile));
    initialiseStruct(secondPgm);
    secondPgm->height = reducedHeight;
    secondPgm->width = reducedWidth;
    secondPgm->gray = firstPgm->gray;
    secondPgm->magic_number[0] = firstPgm->magic_number[0];
    secondPgm->magic_number[1] = firstPgm->magic_number[1];

    secondPgm->imageData = (unsigned char **)malloc(secondPgm->height * sizeof(*secondPgm->imageData));
    for (int i = 0; i < secondPgm->height; i++){
        secondPgm->imageData[i] = (unsigned char *)malloc(secondPgm->width * sizeof(unsigned char));    
    }
    // writes reduced file
    reduceFile(factor, firstPgm, secondPgm);

    FILE *outputFile = fopen(argv[3], "w");

    if (firstPgm->magic_number[1]=='5')
        fileWrite(argv[3], secondPgm,2);
    if (firstPgm->magic_number[1]=='2')
        fileWrite(argv[3], secondPgm,2);  
    // size_t nBytesWritten = fprintf(outputFile, "P%i\n%d %d\n%d\n", (int)firstPgm->magic_number[1], firstPgm->width, firstPgm->height, firstPgm->gray);
    printf("REDUCED\n");
    return EXIT_NO_ERRORS;
}