//Included for file I/O operations and String handling operations.
#include <stdio.h>
#include <stdlib.h>

//Files necessary for the program to run correctly.
#include "readFile.h"
#include "errorHandling.h"
#include "fileStructure.h"
#include "definitions.h"

//Main routine
//
//CLI parameters:
//argv[0]: executable name
//argv[1]: input file name
//argv[2]: output file name

int main(int argc, char **argv){
	//Error check to ensure the correct amount of args are passed in. 
	//If it is incorrect it prints an error message and returns the error.
	if (argc == 1){
		printf("./pgma2b inputFile.pgm outputFile.pgm");
		return(EXIT_WRONG_ARG_COUNT);
		}	
	else if (argc != 3){
		errorHandling(EXIT_WRONG_ARG_COUNT, " ");
		return(EXIT_WRONG_ARG_COUNT);
		} 

	//Creates a pgmFile structure to hold all relevant image data.
	pgmFile *pgmAscii = (pgmFile *) malloc(sizeof(pgmFile));

	//Runs readFile from readFile.c to get information into the pgm struct.
	//Checks for error code and returns it if there is one.
	int errorCode = readFile(pgmAscii, argv[1]);
	if (errorCode != 0){
		return(errorCode);
		}
	//Checks to see if the file is an ASCII file.
	//If so it prints out an error message and returns an error.
	if (pgmAscii->magic_number[1] != '2'){
		errorHandling(EXIT_MISCELLANEOUS, "Incorrect File Type");
		return(EXIT_MISCELLANEOUS);
		}

	//Converts the magic number to that of the other file type.
	pgmAscii->magic_number[1] = '5';
	//Runs writeFile from writeFile.c to put all information into the file in the other form.
	//Checks for error code and returns it if there is one.
	errorCode = writeFile(pgmAscii, argv[2]);
	if (errorCode != 0){
		return(errorCode);
		}
	//If everything is successful prints CONVERTED.
	printf("CONVERTED\n");
	return(0);
	}
