#ifndef fileWrite
#define fileWrite
#include "definitions.h"

int checkFileOpen(FILE *outputFile, char *commentLine, unsigned char *imageData, char* outputFileName);
int checkDimensionalWrite(size_t nBytesWritten, char *commentLine, unsigned char *imageData, char* outputFileName);
int effWriteCode(unsigned char *imageData, long nImageBytes, unsigned int width, size_t nBytesWritten, FILE *outputFile, char *commentLine, char* outputFileName);

#endif