#define EXIT_NO_ERRORS 0
#define EXIT_WRONG_ARG_COUNT 1
#define EXIT_BAD_FILENAME 2
#define EXIT_BAD_MAGIC_NUM 3
#define EXIT_BAD_COMMENT 4
#define EXIT_BAD_DIMENSIONS 5
#define EXIT_BAD_MAX_GRAY 6
#define EXIT_IMAGE_MALLOC_FAIL 7
#define EXIT_BAD_DATA 8
#define EXIT_OUTPUT_FAILED 9
#define EXIT_BAD_LAYOUT 10
#define EXIT_MISC 100

#define MAGIC_NUMBER_RAW_PGM 0x3550
#define MAGIC_NUMBER_ASCII_PGM 0x3250
#define MIN_IMAGE_DIMENSION 1
#define MAX_IMAGE_DIMENSION 65536
#define MAX_COMMENT_LINE_LENGTH 128

// defines struct for pgm files with the characteristics
typedef struct _pgmFile {
    unsigned int width, height, gray;
    unsigned char *imageData;
    unsigned char magic_number[2];
    unsigned short *magic_Number;
    char *commentLine;
    long nImageBytes;
} pgmFile;

// allows functions to be accessible in other C files
extern int FileHandling(char *fileName, pgmFile *pgm);
extern int FileWrite(char *outputFileName, pgmFile *pgm);
