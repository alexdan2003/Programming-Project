//Included for file I/O operations and String handling operations.
#include <stdio.h>
#include <stdlib.h>

//Files necessary for the program to run correctly.
#include "errorHandling.h"
#include "fileStructure.h"
#include "definitions.h"

//Function to set up the reduced pgm with all required information and memory.
int setupPGM(pgmFile *pgm, pgmFile *pgmReduced, int reducedWidth, int reducedHeight){
	pgmReduced->magic_Number = pgm->magic_Number;
	pgmReduced->magic_number[0] = pgm->magic_number[0];
	pgmReduced->magic_number[1] = pgm->magic_number[1];
	
	pgmReduced->commentLine = (char *) malloc(MAX_COMMENT_LINE_LENGTH + 1);
	pgmReduced->commentLine = pgm->commentLine;

	pgmReduced->width = reducedWidth;
	//pgmReduced->height = reducedHeight;
	//printf("%i", pgmReduced->height);
	//pgmReduced->maxGray = pgm->maxGray;

	//pgmReduced->imageData = (unsigned char**) malloc(reducedHeight * sizeof(unsigned char*));
	//int i = 0;
	//for (i=0; i < reducedHeight; i++){
		//pgmReduced->imageData[i] = (unsigned char*) malloc(reducedWidth * sizeof(unsigned char)); 
		//}	

	return(EXIT_NO_ERRORS);
	}

//Function to reduce the size of the file based off of a user inputted factor number.
int reduceFile(pgmFile *pgm, pgmFile *pgmReduced, double reduceFactor){
	//works out the height and width of the reduced file according to the reduceFactor.
	int reducedWidth = ((pgm->width) + reduceFactor - 1) / reduceFactor;
	int reducedHeight = ((pgm->height) + reduceFactor - 1) / reduceFactor;			

	setupPGM(pgm, pgmReduced, reducedWidth, reducedHeight);

	return(EXIT_NO_ERRORS);
	}
