#include "definitions.h"

// int fileRead(char **argv, int argNum, pgmFile *thePgm);
int fileRead(char *fileName, pgmFile *thePgm);
int fileWrite(char* outputFileName, pgmFile *pgm, int aOrB);