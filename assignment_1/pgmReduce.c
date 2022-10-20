//Included for file I/O operations and String handling operations.
#include <stdio.h>
#include <stdlib.h>

//Files necessary for the program to run correctly.
#include "readFile.h"
#include "writeFile.h"
#include "reduceFile.h"
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
		printf("Usage: ./pgmReduce inputImage.pgm reduction_factor outputImage.pgm\n");
		return(EXIT_NO_ERRORS);
		}
	else if (argc != 4){
		errorHandling(EXIT_WRONG_ARG_COUNT, " ");
		return(EXIT_WRONG_ARG_COUNT);
		}

	//Creates a pgmFile structure to hold all relevant image data.
	pgmFile *pgm = (pgmFile *) malloc(sizeof(pgmFile));
	pgmFile *pgmReduced = (pgmFile *) malloc(sizeof(pgmFile));

	//Runs readFile from readFile.c to get information into the pgm struct.
	//Checks for error code and returns it if there is one.
	int errorCode = readFile(pgm, argv[1]);
	if (errorCode != EXIT_NO_ERRORS){
		return(errorCode);
		}
	
	//Gets the reduceFactor number from the char arguments and converts it to double.
	double reduceFactor = atoi(argv[2]);
	if (reduceFactor <= 0){
		errorHandling(EXIT_MISCELLANEOUS, "Not a valid reduce factor.\n");
		return(EXIT_MISCELLANEOUS);
		}
	
	//Runs the reduceFile from reduceFile.c to reduce the size of the file.
	//Checks for error code and returns it if there is one.
	errorCode = reduceFile(pgm, pgmReduced, reduceFactor);
	if (errorCode != EXIT_NO_ERRORS){
		return(errorCode);
		}

	//Runs writeFile from writeFile.c to output the newly reduced pgm to the output file.
	//Checks for error code and returns it if there is one.
	errorCode = writeFile(pgmReduced, argv[3]);
	if (errorCode != EXIT_NO_ERRORS){
		errorHandling(errorCode, argv[3]);
		return(errorCode);
		}
 
	//If everything goes correctly it prints REDUCED and frees the pgms.
	free(pgm->commentLine);
	free(pgmReduced->commentLine);
	int height = 0;
	for (height=0; height < pgm->height; height++){
		free(pgm->imageData[height]);
		}
	for (height=0; height < pgmReduced->height; height++){
		free(pgmReduced->imageData[height]);
		}
	free(pgm->imageData);
	free(pgmReduced->imageData);
	free(pgm);
	free(pgmReduced);
	printf("REDUCED\n");
	return(EXIT_NO_ERRORS);
	}
