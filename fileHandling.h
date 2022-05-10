#ifndef fileHandling
#define fileHandling

#include "definitions.h"

int initialiseStruct(pgmFile *pgm);
int argCheck(int argNum, int correctArgNum);
int checkMN(FILE *inputFile, unsigned char *magic_number, char* fileName);
int commentLine(FILE *inputFile, char* fileName, char *commentLine);
int widthHeightGray(FILE *inputFile, char* fileName, pgmFile *pgm);
int memAlloc(unsigned char *imageData, FILE *inputFile, char* fileName, unsigned int width, unsigned int height);
int effRead(unsigned char *imageData, FILE *inputFile, char* fileName, long nImageBytes);
int binaryRead(pgmFile *pgm, FILE *inputFile);

#endif
