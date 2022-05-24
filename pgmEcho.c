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
#include "pgmReadWrite.h"

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
    argCheck(argc, 3);
    // check if arguments is 0 when argCheck returns 0
    if (argc == 1)
    {
        printf("Usage: ./pgmEcho inputImage.pgm outputImage.pgm");
        exit(0);
    }
    // reads the input file and if it didn't read correctly, exit the program
    if (fileRead(argv[1], thePgm) != 0)
    {
        exit(0);
    }
    // echoes ASCII files
    if (thePgm->magic_number[1] == '2')
    {
        if (fileWrite(argv[2], thePgm, 2) == 0)
        {
            printf("ECHOED\n");
            // frees the memory
            freeMemory(thePgm);
            return EXIT_NO_ERRORS;
        }
    }
    // echoes binary files
    if (thePgm->magic_number[1] == '5')
    {
        if (fileWrite(argv[2], thePgm, 5) == 0)
        {
            printf("ECHOED\n");
            // frees the memory
            freeMemory(thePgm);
            return EXIT_NO_ERRORS;
        }
    }

}
