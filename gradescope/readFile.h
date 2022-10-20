#ifndef readFile_h
#define readFile_h

//Ensures that the header understands what a pgmFile is.
#include "fileStructure.h"

//Defines all of the functions within the file.
int readFile(pgmFile *pgm, char* fileName);

int readMagicNumber(pgmFile *pgm, FILE *inputFile);

int readCommentLine(pgmFile *pgm, FILE *inputFile);

int readImageData(pgmFile *pgm, FILE *inputFile);

#endif
