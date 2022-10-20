//Included for I/O operations and String handling operations.
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
//argv[1]: input file name
//argv[2]: output file name
//returns 0 and ECHOED on success
//non-zero error code on fail

int main(int argc, char **argv){
	//Error check to ensure the correct amount of args are passed in.
	//If it is incorrect it prints an error message and returns the error.
	if (argc == 1){
		printf("Usage: ./pgmEcho inputImage.pgm outputImage.pgm\n");
		return(EXIT_NO_ERRORS);
		}
	else if (argc != 3){
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

	//Runs writeFile from writeFile.c using the pgm struct to write all information to output file.
        //Checks for error code and returns it if there is one.
        errorCode = writeFile(pgm, argv[2]);
        if (errorCode != EXIT_NO_ERRORS){
		return(errorCode);
                }
	
	//If both previous operations are successful it prints ECHOED, frees all necessary memory and returns 0.
	printf("ECHOED\n");
	free(pgm->commentLine);
	int height = 0;
	for (height=0; height < pgm->height; height++){
		free(pgm->imageData[height]);	
		}
	free(pgm->imageData);
	free(pgm);
	return(EXIT_NO_ERRORS);
	}
