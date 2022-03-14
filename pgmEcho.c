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


int initialiseStruct(pgmFile *pgm){
    pgm->width = 0;
    pgm->height = 0;
    pgm->gray = 255;
    pgm->imageData = NULL;
    pgm->commentLine = NULL;
    pgm->magic_number[0] = '0';
	pgm->magic_number[1] = '0';
	pgm->magic_Number = NULL;
    return EXIT_NO_ERRORS;
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
    pgmFile *thePgm = (pgmFile *)malloc(sizeof(pgmFile));
    initialiseStruct(thePgm);

    // now start reading in the data in ASCII mode b/c the header is text
    argCheck(argc, 3, argv);

	FileHandling(argv, thePgm);
	FileWrite(argv, thePgm);


    } /* main() */