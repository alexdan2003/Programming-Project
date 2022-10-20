//Included for I/O operations and String handling operations.
#include <stdio.h>
#include <stdlib.h>

//Files necessary for the program to run correctly.
#include "fileStructure.h"
#include "definitions.h"

//Function to compare the magic number between the two pgm files. 
//Returns 1 if they are different otherwise returns 0.
int compareMagicNumber(pgmFile *pgmOne, pgmFile *pgmTwo){
	//Simple compare between the two files magic number.
	if (pgmOne->magic_Number != pgmTwo->magic_Number){
		return(1);
		}
	return(EXIT_NO_ERRORS);
	}

//Function to compare the file and image data between the two pgm files.
//Returns 1 if they are different otherwise returns 0.
int compareImageData(pgmFile *pgmOne, pgmFile *pgmTwo){
	//Checks the two to see if their height, width and maxGray match.
	if (pgmOne->width != pgmTwo->width ||
 	    pgmOne->height != pgmTwo->height ||
	    pgmOne->maxGray != pgmTwo->maxGray){
		return(1);
		}

	//Compares the two images image data in ASCII using memcmp to see if they are logically equivalent.
	long fileSize = pgmOne->width * pgmOne->height * sizeof(unsigned char);
	int compareImageData = memcmp(pgmOne->imageData, pgmTwo->imageData, fileSize);
	
	//Checks the memcmp variable to see whether it returned equivalent or different.
	if (compareImageData != 0){
		return(1);
		} 
	return(EXIT_NO_ERRORS);
	}

//Main function of the program, runs all functions within the file,
//comparing the two structs and returining if they are equivalent or not.
int compareFile(pgmFile *pgmOne, pgmFile *pgmTwo){
	//Compares the magic number of the two pgm files, to see if they are equal.
	//If it returns anything other than 0 then it returns DIFFERENT as they are not the same.
	int errorCode = compareMagicNumber(pgmOne, pgmTwo);
	if (errorCode != EXIT_NO_ERRORS){
		printf("DIFFERENT\n");
		return(EXIT_NO_ERRORS);
		}

	//Compares the file and image data of the two pgm files, to see if they are equal.
	//If it returns anything other than 0 then it returns DIFFERENT as they are not the same.
	errorCode = compareImageData(pgmOne, pgmTwo);
	if (errorCode != EXIT_NO_ERRORS){
		printf("DIFFERENT\n");
		return(EXIT_NO_ERRORS);
		}
	//If it passes both of the other function tests then it returns IDENTICAl. 
	printf("IDENTICAL\n");
	return(EXIT_NO_ERRORS);
	}
