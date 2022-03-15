#ifndef fileHandling
#define fileHandling

int argCheck(int argNum, int correctArgNum, char* fileName);
int checkMN(FILE *inputFile, unsigned char *magic_number, char* fileName);
int commentLine(FILE *inputFile, char* fileName, char *commentLine);
int widthHeightGray(FILE *inputFile, char* fileName, unsigned int width, unsigned int height, unsigned int maxGray);
int memalloc(unsigned char *imageData, FILE *inputFile, char* fileName, unsigned int width, unsigned int height);
int effread(unsigned char *imageData, FILE *inputFile, char* fileName, long nImageBytes);
int fileHandling(char **argv, pgmFile *pgm);

#endif
