//Included for I/O operations and String handling operations.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Files necessary for the program to run correctly.
#include "fileStructure.h"
#include "errorHandling.h"
#include "definitions.h"

//Main function that outputs all of the necessary data from the pgm struct into the output file.
int writeFile(pgmFile *pgm, char* fileName){
	//Error check to ensure that the file is a pgm file.
	//If it isn't prints an error message and returns the error.
	if ((fileName[strlen(fileName)-2] != 'g') || (fileName[strlen(fileName)-1] != 'm')){
                errorHandling(EXIT_BAD_FILE_NAME, fileName);
                return(EXIT_BAD_FILE_NAME);
                }

	//Opens file given to it by fileName.
	FILE *outputFile = fopen(fileName, "w");

	//Error check to ensure that the fileName is valid.
	//If it isn't cleans up, prints an error message and returns the error.
	if (outputFile == NULL){
		errorHandling(EXIT_BAD_FILE_NAME, fileName);
		return(EXIT_BAD_FILE_NAME);
		}	

	//Prints the width, height and maxGray to the file and holds the size of this in nBytesWritten.
	size_t nBytesWritten = fprintf(outputFile, "P%c\n%d %d	\n%d\n", pgm->magic_number[1], pgm->width, pgm->height, pgm->maxGray);
	
	//Error check to ensure that the values above have been written to the file.
	//If it hasn't cleans up, prints an error message and returns the error.
        if (nBytesWritten < 0){
                free(pgm->commentLine);
                free(pgm->imageData);
		
		errorHandling(EXIT_BAD_FILE_NAME, fileName);
                return(EXIT_BAD_FILE_NAME);
                }

	if (pgm->magic_number[0] == 'P' && pgm->magic_number[1] == '2'){
		int i = 0;
		for (i=0; i < pgm->height; i++){
			int nextCol = 0;
			int j = 0;
			for (j=0; j < pgm->width; j++){
				if (j+1 == pgm->width){
					nextCol = 0;
					}
				else{
					nextCol = 1;
					}
			
				nBytesWritten = fprintf(outputFile, "%d%c", pgm->imageData[i][j], (nextCol ? ' ' : '\n'));
				}
			}
		}	
	else if (pgm->magic_number[0] == 'P' && pgm->magic_number[1] == '5'){
		unsigned char *nextGrayValue;	
		int i = 0;
		for (i=0; i < pgm->height; i++){
			int j = 0;
			for (j=0; j < pgm->width; j++){
				nextGrayValue = &pgm->imageData[i][j];	
				nBytesWritten = fwrite(nextGrayValue, 1, 1, outputFile);
				}	
			}
		}   	

	return(0);
	}
