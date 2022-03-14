#define EXIT_NO_ERRORS 0
#define EXIT_WRONG_ARG_COUNT 1
#define EXIT_BAD_FILENAME 2
#define EXIT_BAD_MN 3
#define EXIT_BAD_COMMENT 4
#define EXIT_BAD_DIMENSIONS 5

#define MAGIC_NUMBER_RAW_PGM 0x3550
#define MAGIC_NUMBER_ASCII_PGM 0x3250
#define MIN_IMAGE_DIMENSION 1
#define MAX_IMAGE_DIMENSION 65536
#define MAX_COMMENT_LINE_LENGTH 128

typedef struct _pgmFile {
    unsigned int width;
    unsigned int height;
    unsigned int gray;
    unsigned char *imageData;
    unsigned char magic_number[2];
    unsigned short *magic_Number;
    char *commentLine;
    long nImageBytes;
} pgmFile;


extern int FileHandling(char *fileName, pgmFile *pgm);
extern int FileWrite(char *outputFileName, pgmFile *pgm);
