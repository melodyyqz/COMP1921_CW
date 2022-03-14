
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