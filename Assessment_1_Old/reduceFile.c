//Included for file I/O operations and String handling operations.
#include <stdio.h>
#include <stdlib.h>

//Files necessary for the program to run correctly.
#include "errorHandling.h"
#include "fileStructure.h"
#include "definitions.h"

//Function to reduce the size of the file based off of a user inputted factor number.
int reduceFile(pgmFile *pgm, FILE *outputFile, double reduceFactor){
	//works out the height and width of the reduced file according to the reduceFactor.
	int reducedWidth = ((pgm->width) + reduceFactor - 1) / reduceFactor;
	int reducedHeight = ((pgm->height) + reduceFactor - 1) / reduceFactor;		

	//Prints the magic number, reduced height and width and the gray value to the output file.
	//Checks to see that something has been printed and if it hasn't returns an error message.
	size_t nBytesWritten = fprintf(outputFile, "P%c\n%d %d	\n%d\n", pgm->magic_number[1], reducedWidth, reducedHeight, pgm->maxGray);
	if (nBytesWritten == 0){
                return(EXIT_BAD_FILE_NAME);
                }
	
	//Creates a new array of characters that will hold the reducedImage bytes of data.
	long reducedImageBytes = reducedHeight * reducedWidth * sizeof(unsigned char);
	unsigned char *reducedImage = (unsigned char *) malloc(reducedImageBytes);

	//Two counts, one to keep track of the reduced bytes and one to keep track of the original pgm bytes.
	int reducedCount = 0;
	int pgmCount = 0;

	//Runs through the reducedWidth of the file.
	int w;
	for (w = 0; w < reducedWidth; w++){
		//Sets the pgmCount equal to the location of the byte needed by the reduced file. 
		pgmCount = pgm->width * reduceFactor * w;
		//Runs through the reducedHeight of the file.
		int h;
		for (h = 0; h < reducedHeight; h++){
			//Sets the correct byte of the pgm data to that of the reduced data.
			reducedImage[reducedCount] = pgm->imageData[pgmCount];

			//Increments the counts, with pgmCount incrementing by the reduce factor ensuring it jumps the correct amount of bytes.
			reducedCount += 1;
			pgmCount += reduceFactor;
			}
		}
	
	//Runs through the reducedImage bytes of data, printing them to the output file.
	unsigned char *nextGrayValue;
	for (nextGrayValue = reducedImage; nextGrayValue < reducedImage + reducedImageBytes; nextGrayValue++){
		int nextCol = (nextGrayValue - reducedImage + 1) % reducedWidth;
		//Prints the images bytes to the file properly.
		nBytesWritten = fprintf(outputFile, "%d%c", *nextGrayValue, (nextCol ? ' ' : '\n') );

		//Checks to ensure that images bytes have been printed out.
		//If they haven't it returns an error message.
		if (nBytesWritten == 0){
			return(EXIT_BAD_FILE_NAME); 
			} 
		}
	
	return(0);
	}
