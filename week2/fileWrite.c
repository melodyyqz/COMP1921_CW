// library for I/O routines
#include <stdio.h>

// library for memory routines
#include <stdlib.h>

// definitions for error codes and maximum values
#include "definitions.h"

int checkFileOpen(char* outputFile, char *commentLine, unsigned char* imageData){
     // NULL output file
    if (outputFile == NULL){
		// free memory
		free(commentLine);
		free(imageData);

		// print an error message and return error code
		printf("Error: Failed to write pgm image to file %s\n", argv[2]);	
		return EXIT_BAD_OUTPUT_FILE;
	}   
return EXIT_NO_ERRORS; 
}

int mainFileWrite(){
   // open a file for writing
	FILE *outputFile = fopen(argv[2], "w"); 
    checkFileOpen();
}
