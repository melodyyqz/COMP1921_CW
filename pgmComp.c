// library for I/O routines
#include <stdio.h>

// library for memory routines
#include <stdlib.h>

// definitions for error codes and maximum values
#include "definitions.h"
#include "pgmReadWrite.h"
#include "fileHandling.h"

int main(int argc, char **argv)
{
    // check arguments
    if (argCheck(argc, 3) != 0)
    {
        exit(0);
    }
    // check if arguments is 0 when argCheck returns 0
    if (argc == 1)
    {
        printf("Usage: ./pgmComp inputImage.pgm inputImage.pgm");
        exit(0);
    }

    // initialising the pgm files
    pgmFile *firstPgm = (pgmFile *)malloc(sizeof(pgmFile));
    initialiseStruct(firstPgm);
    pgmFile *secondPgm = (pgmFile *)malloc(sizeof(pgmFile));
    initialiseStruct(secondPgm);

    // reads files
    if (fileRead(argv[1], firstPgm) != 0 || fileRead(argv[2], secondPgm) != 0)
    {
        exit(0);
    }

    // assigns the pointer for each file
    unsigned char *nextFirstGrayValue = firstPgm->imageData;
    unsigned char *nextSecondGrayValue = secondPgm->imageData;

    // calculates the image bytes of the first pgm file and sets nImageBytes to it
    long nImageBytes = firstPgm->width * firstPgm->height * sizeof(unsigned char);

    // loops through checking each value of the file
    while (nextFirstGrayValue < firstPgm->imageData + nImageBytes)
    {
        // checks if the value being pointed at in the first file is equal to the value being pointed at in the second file
        if (((float)*nextSecondGrayValue) != ((float)*nextFirstGrayValue))
        {
            printf("DIFFERENT\n");
            return EXIT_NO_ERRORS;
        }
        // increments values of pointers
        nextFirstGrayValue++;
        nextSecondGrayValue++;
    }

    // successful
    printf("IDENTICAL\n");
    return EXIT_NO_ERRORS;
}
