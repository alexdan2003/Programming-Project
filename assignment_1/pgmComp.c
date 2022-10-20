//Included for file I/O operations and String handling operations.
#include <stdio.h>
#include <stdlib.h>

//Files necessary for the program to run correctly.
#include "readFile.h"
#include "compareFile.h"
#include "errorHandling.h"
#include "fileStructure.h"
#include "definitions.h"

//Main routine
//
//CLI paramaters:
//argv[0]: executable name
//argv[1]: fileOne
//argv[2]: fileTwo

int main(int argc, char **argv){
	//Error check to ensure the correct amount of args are passed in.
	//If it is incorrect it prints an error message and returns the error.
	if (argc == 1){
		printf("Usage: ./pgmComp inputImage.pgm inputImage.pgm");
		return(EXIT_NO_ERRORS);
		}
	else if (argc != 3){
		errorHandling(EXIT_WRONG_ARG_COUNT, " ");
		return(EXIT_WRONG_ARG_COUNT);
		}

	//Creates two pgm structs so that it can later compare the two.	
	pgmFile *pgmOne = (pgmFile *) malloc(sizeof(pgmFile));
	pgmFile *pgmTwo = (pgmFile *) malloc(sizeof(pgmFile));

	//Runs readFile from readFile.c on the first pgm struct to get the information needed.
	//Checks for error code and returns it if there is one.
	int errorCode = readFile(pgmOne, argv[1]);
	if (errorCode != EXIT_NO_ERRORS){
		return(errorCode);
		}

	//Runs readFile from readFile.c on the second pgm struct to get the information needed.
	//Checks for error code and returns it if there is one.
	errorCode = readFile(pgmTwo, argv[2]);
	if (errorCode != EXIT_NO_ERRORS){
		return(errorCode);
		}

	//Compares the two pgm structures to see if they are logically equivalent.
	//Checks for error code and returns it if there is one.
	errorCode = compareFile(pgmOne, pgmTwo);
	if (errorCode != EXIT_NO_ERRORS){
		return(errorCode);
		}

	//Frees both pgms and returns an exit with no errors.
	free(pgmOne->commentLine);
	free(pgmTwo->commentLine);
	int height = 0;
	for (height=0; height < pgmOne->height; height++){
		free(pgmOne->imageData[height]);
		}
	for (height=0; height < pgmTwo->height; height++){
		free(pgmTwo->imageData[height]);
		}
	free(pgmOne->imageData);
	free(pgmTwo->imageData);
	free(pgmOne);
	free(pgmTwo);
	return(EXIT_NO_ERRORS);
	}
