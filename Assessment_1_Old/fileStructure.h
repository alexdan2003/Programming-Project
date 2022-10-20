#ifndef pgmFile_h
#define pgmFile_h

typedef struct pgmFile {
	unsigned char magic_number[2];
	unsigned short *magic_Number;
	char *commentLine;
	unsigned int width;
	unsigned int height;
	unsigned int maxGray;
	unsigned char *imageData;
}pgmFile;

#endif
