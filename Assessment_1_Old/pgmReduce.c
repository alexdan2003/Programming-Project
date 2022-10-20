//Included for file I/O operations and String handling operations.
#include <stdio.h>
#include <stdlib.h>

//Files necessary for the program to run correctly.
#include "readFile.h"
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
		printf("./pgmReduce inputFile.pgm integer n outputFile.pgm\n");
		return(EXIT_WRONG_ARG_COUNT);
		}
	else if (argc != 4){
		errorHandling(EXIT_WRONG_ARG_COUNT, " ");
		return(EXIT_WRONG_ARG_COUNT);
		}

	//Creates a pgmFile structure to hold all relevant image data.
	pgmFile *pgm = (pgmFile *) malloc(sizeof(pgmFile));

	//Runs readFile from readFile.c to get information into the pgm struct.
	//Checks for error code and returns it if there is one.
	int errorCode = readFile(pgm, argv[1]);
	if (errorCode != EXIT_NO_ERRORS){
		return(errorCode);
		}
	
	//Gets the reduceFactor number from the char arguments and converts it to double.
	double reduceFactor = atoi(argv[2]);
	if (reduceFactor < 0){
		errorHandling(EXIT_MISCELLANEOUS, "Not a valid reduce factor.\n");
		return(EXIT_MISCELLANEOUS);
		}
	
	char *fileName = argv[3];  
	if ((fileName[strlen(fileName)-2] != 'g') || (fileName[strlen(fileName)-1] != 'm')){
                errorHandling(EXIT_BAD_FILE_NAME, argv[3]);
                return(EXIT_BAD_FILE_NAME);
                }


	//Opens the output file to write to.
	FILE *outputFile = fopen(argv[3], "w");

	//Runs the reduceFile from reduceFile.c to reduce the size of the file.
	//Checks for error code and returns it if there is one.
	errorCode = reduceFile(pgm, outputFile, reduceFactor);
	if (errorCode != EXIT_NO_ERRORS){
		errorHandling(errorCode, argv[3]);
		return(errorCode);
		}
	//If everythimg goes correctly it prints REDUCED.
	printf("REDUCED\n");
	return(EXIT_NO_ERRORS);
	}
