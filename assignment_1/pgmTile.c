//Included for file I/O operations and String handling operations.
#include <stdio.h>
#include <stdlib.h>

//Files necessary for the program to run correctly.
#include "readFile.h"
#include "writeFile.h"
#include "errorHandling.h"
#include "fileStructure.h"
#include "definitions.h"

//Main routine
//
//CLI parameters:
//argv[0]: executable name
//argv[1]: input file
//argv[2]: integer factor n
//argv[3]: output file


int main(int argc, char **argv){
	//Error check to ensure the correct amount of args are passed in.
	//If it is incorrect it prints an error message and returns the error.
	if (argc == 1){
		printf("Usage: ./pgmTile inputImage.pgm integer_n outputImage.pgm");
		return(EXIT_WRONG_ARG_COUNT);
		}
	else if (argc != 4){
		errorHandling(EXIT_WRONG_ARG_COUNT, " ");
		return(EXIT_WRONG_ARG_COUNT);
		}

	//Creates a pgmFile structure to hold all relevant image data.
	pgmFile *pgm = (pgmFile *) malloc(sizeof(pgmFile));

	int errorCode = readFile(pgm, argv[1]);
	if (errorCode != EXIT_NO_ERRORS){
		return(errorCode);
		}
	
	free(pgm->commentLine);
	int height = 0;
	for (height=0; height < pgm->height; height++){
		free(pgm->imageData[height]);
		}
	free(pgm->imageData);
	free(pgm);
	return(EXIT_NO_ERRORS);
	}
