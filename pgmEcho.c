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
#include "fileHandling.h"


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

int fileRead(char **argv, pgmFile *thePgm)
{
    char* fileName = argv[1];
    FILE *inputFile = fopen(fileName, "r");
	// if it fails, return error code
	if (inputFile == NULL)
		return EXIT_BAD_FILENAME;
	checkMN(inputFile, thePgm->magic_number, fileName);
    commentLine(inputFile, fileName, thePgm->commentLine);
    widthHeightGray(inputFile, fileName, thePgm->width, thePgm->height, thePgm->gray);
    thePgm->nImageBytes = thePgm->width * thePgm->height * sizeof(unsigned char);
	thePgm->imageData = (unsigned char *)malloc(thePgm->nImageBytes);
    memalloc(thePgm->imageData, inputFile, fileName, thePgm->width, thePgm->height);
    printf("%c", thePgm->imageData);
    effread(thePgm->imageData, inputFile, fileName, thePgm->nImageBytes);
    return 0;
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
    {
    // initialising pgm file
    pgmFile *thePgm = (pgmFile *)malloc(sizeof(pgmFile));
    initialiseStruct(thePgm);
    // check arguments
    argCheck(argc, 3, argv[0]);
    // check if arguments is 0 when argCheck returns 0
    if (argc==0){
        exit(0);
    }
    fileRead(argv, thePgm);
    }