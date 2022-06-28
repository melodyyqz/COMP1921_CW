#ifndef fileHandling
#define fileHandling

#include "definitions.h"

int initialiseStruct(pgmFile *pgm);
int argCheck(int argNum, int correctArgNum);
int checkMN(FILE *inputFile, unsigned char *magic_number, char* fileName);
int commentLine(FILE *inputFile, char* fileName, char *commentLine);
int widthHeightGray(FILE *inputFile, char* fileName, pgmFile *pgm);
int memAlloc(FILE *inputFile, char* fileName, pgmFile *pgm);
void freeMemory (pgmFile *pgm);
int effRead(FILE *inputFile, char* fileName, pgmFile *pgm);
int binaryRead(pgmFile *pgm, FILE *inputFile, char* fileName);

#endif
