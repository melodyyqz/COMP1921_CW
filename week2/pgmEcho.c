/***********************************/
/* COMP 1921M Programming Project  */
/* 2021-22 Spring Semester         */
/*                                 */
/* Hamish Carr                     */
/***********************************/

/***********************************/
/* A first iteration to take a pgm */
/* file in binary and convert to   */
/* ASCII or vice versa             */
/***********************************/

/***********************************/
/* Main Routine                    */
/***********************************/

/* library for I/O routines        */
#include <stdio.h>

/* library for memory routines     */
#include <stdlib.h>

// definitions for error codes and maximum values
#include "definitions.h"

void initialiseStruct(pgmFile *pgm){
    pgm->width = 0;
    pgm->height = 0;
    pgm->gray = 0;
    pgm->*imageData = NULL;
    pgm->*commentLine = NULL;
    pgm
}




/***********************************/
/* main routine                    */
/*                                 */
/* CLI parameters:                 */
/* argv[0]: executable name        */
/* argv[1]: input file name        */
/* argv[2]: output file name       */
/* returns 0 on success            */
/* non-zero error code on fail     */
/***********************************/
int main(int argc, char **argv)
    { /* main() */
    // initialising
    pgmFile thePgm = (pgmFile *)malloc(sizeof(pgmFile));
    // the logical width & height; note: cannot be negative
    unsigned int width = 0, height = 0;

    // maximum gray value (assumed); make it an integer for ease
    unsigned int maxGray = 255;

    // pointer to raw image data
    unsigned char *imageData = NULL;

    // the magic number stored as two bytes to avoid problems with endianness
    // Raw:    0x5035 or P5    
    // ASCII:  0x5032 or P2    
    unsigned char magic_number[2] = {'0','0'};
    unsigned short *magic_Number = (unsigned short *) magic_number;

    // we will store ONE comment
    char *commentLine = NULL;

    // now start reading in the data in ASCII mode b/c the header is text
    argCheck(argc, 3, argv);
    mainFileHandling(argv, magic_number, width, height, maxGray, imageData, nImageBytes);


    } /* main() */