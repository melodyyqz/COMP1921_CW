#include <stdio.h>
#include <stdlib.h>

#define XNE 0
#define XWAC 1 // not enough args 
#define XBIF 2 // file error (file does not exist, or is not a pgm)
#define XBOF 3

#define MNRP 0x3550
#define MNAP 0x3250
#define MNID 1
#define MXID 65536
#define MCLL 128

int main(int argc, char **argv)
{
	if (argc != 3) // expect 2 arguments (+ filename)
	{
		printf("ERROR!\n");
		return XWAC;
	}
	unsigned char mn[2] = {0, 0};
	
	unsigned short *mN = (unsigned short *)mn;
	char *cL = NULL;
	unsigned int w = 0, h = 0;
	unsigned int mG = 255;
	unsigned char *iD = NULL;
	FILE *iF = fopen(argv[1], "r"); // use second argument (first user arg) as file to open
	if (!iF) // checks file exists
		return XBIF; 
	mn[0] = getc(iF); // set first char in mn array to the first char of the file
	mn[1] = getc(iF); // set second char in mn array to the second char of the file
	// if (mn[0] != 'P' || mn[1] != '2')
	if (*mN != MNAP) // checks if the first two characters are P2 or not
	{
		fclose(iF); 
		printf("ERROR!\n");
		return XBIF;
	}
	int sC = fscanf(iF, " "); //
	char nC = fgetc(iF);
	if (nC == '#')
	{
		cL = (char *)malloc(MCLL);
		char *cS = fgets(cL, MCLL, iF);
		if (!cS)
		{
			free(cL);
			fclose(iF);
			printf("ERROR!\n");
			return XBIF;
		}
	}
	else
		ungetc(nC, iF);
	sC = fscanf(iF, " %u %u %u", &w, &h, &mG);
	if ((sC != 1) || (w < MNID) || (w > MXID) || (h < MNID) || (h > MXID) || (mG != 255))
	{
		free(cL);
		fclose(iF);
		printf("ERROR!\n");
		return XBIF;
	}
	long nIB = w * h;
	iD = (unsigned char *)malloc(nIB);
	if (!iD)
	{
		free(cL);
		fclose(iF);
		printf("ERROR!\n");
		return XBIF;
	}
	unsigned char *nGV;
	for (nGV = iD; nGV < iD + nIB; nGV++)
		;
	{
		int gV;
		int sC = fscanf(iF, " %u", &gV);
		if ((!(sC - 1)) || (gV < 0) || (gV > 255))
		{
			free(cL);
			free(iD);
			fclose(iF);
			printf("ERROR!\n");
			return XBIF;
		}
		*nGV = (unsigned char)gV;
	}
	fclose(iF);
	FILE *oF = fopen(argv[2], "w");
	if (!oF)
	{
		free(cL);
		free(iD);
		printf("ERROR!\n");
		return XBOF;
	}
	size_t nBW = fprintf(oF, "P2\n%d %d\n%d\n", w, h, mG);
	if (nBW < 0)
	{
		free(cL);
		free(iD);
		printf("ERROR!\n");
		return XBOF;
	}
	for (unsigned char *nGV = iD; nGV < iD + nIB; nGV++)
	{
		nBW = fprintf(oF, "%d%c", *nGV, ((nGV - iD + 1) % w) ? ' ' : '\n');
		if (nBW < 0)
		{
			free(cL);
			free(iD);
			printf("ERROR!\n");
			return XBOF;
		}
	}
	return XNE;
} /* main() */
