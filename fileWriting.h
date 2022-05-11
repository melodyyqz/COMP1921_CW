#ifndef fileWriting
#define fileWriting
#include "definitions.h"

int checkFileOpen(FILE *outputFile, pgmFile *pgm, char* outputFileName);
int checkDimensionalWrite(size_t nBytesWritten, pgmFile *pgm, char* outputFileName);
int effWriteCode(pgmFile *pgm, size_t nBytesWritten, FILE *outputFile, char* outputFileName, unsigned char targetMagicNum);

#endif