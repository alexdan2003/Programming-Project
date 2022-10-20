//Included for file I/O operations and String handling operations.
#include <stdio.h>
#include <stdlib.h>

//Files necessary for the program to run correctly.
#include "errorHandling.h"
#include "fileStructure.h"
#include "definitions.h"

//Function to set up the reduced pgm with all required information and memory.
int setupPGM(pgmFile *pgm, pgmFile *pgmReduced, int reducedWidth, int reducedHeight){
	//Copies over the magic number from one pgm to the new one.
	pgmReduced->magic_Number = pgm->magic_Number;
	pgmReduced->magic_number[0] = pgm->magic_number[0];
	pgmReduced->magic_number[1] = pgm->magic_number[1];
	
	//Sets commentLine to NULL as it is not required in the reduced pgm.
	pgmReduced->commentLine = NULL;

	//Takes the reducedWidth and reducedHeight and places them within the pgm, also copies over the maxGray.
	pgmReduced->width = reducedWidth;
	pgmReduced->height = reducedHeight;
	pgmReduced->maxGray = pgm->maxGray;

	//Mallocs for the reduced pgms imageData.
	pgmReduced->imageData = (unsigned char**) malloc(reducedHeight * sizeof(unsigned char*));
	int height = 0;
	for (height=0; height < reducedHeight; height++){
		pgmReduced->imageData[height] = (unsigned char*) malloc(reducedWidth * sizeof(unsigned char)); 
		}	

	return(EXIT_NO_ERRORS);
	}

//Function to reduce the size of the file based off of a user inputted factor number.
int reduceFile(pgmFile *pgm, pgmFile *pgmReduced, double reduceFactor){
	//works out the height and width of the reduced file according to the reduceFactor.
	int reducedWidth = ((pgm->width) + reduceFactor - 1) / reduceFactor;
	int reducedHeight = ((pgm->height) + reduceFactor - 1) / reduceFactor;			

	//Sets up the reduced pgm using the reducedWidth and reducedHeight along with the old pgm.
	setupPGM(pgm, pgmReduced, reducedWidth, reducedHeight);
	
	//Runs through the original pgms height and width and takes specific pixels out of it and places
	//them in the reduced pgm file. This is done using the reducedWidth and reducedHeight to manipulate the
	//height and width variable allowing it to move throughout the original pgms imageData grabbing the pixels it needs.
	int height = 0;
	int reducedPgmHeight = 0; 
	for (height=0; height < pgm->height; height++){
		int width = 0;
		int reducedPgmWidth = 0;
		for (width=0; width < pgm->width; width++){ 
			pgmReduced->imageData[reducedPgmHeight][reducedPgmWidth] = pgm->imageData[height][width];
			reducedPgmWidth = reducedPgmWidth + 1;
			width = width + (reduceFactor - 1);
			}
		reducedPgmHeight = reducedPgmHeight + 1;
		height = height + (reduceFactor - 1);
		}

	return(EXIT_NO_ERRORS);
	}
