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

	//Sets up the nextGrayValue variable and the size of the imageData in bytes.
	unsigned char *nextGrayValue;
	long nImageBytes = pgm->width * pgm->height * sizeof(unsigned char);	

	//Runs a for loop for the imageData so that each value is written to the file.
        for (nextGrayValue = pgm->imageData; nextGrayValue < pgm->imageData + nImageBytes; nextGrayValue++){
                int nextCol = (nextGrayValue - pgm->imageData + 1) % pgm->width;

		//Checks whether the file is an ASCII file or a binary file. 
		if (pgm->magic_Number == MAGIC_NUMBER_RAW_PGM){
			//Writes out the imageData using fwrite so that it works in binary.
			nBytesWritten = fwrite(nextGrayValue, 1, 1, outputFile);
			}
		else if (pgm->magic_Number == MAGIC_NUMBER_ASCII_PGM){
			//Writes out the imageData using fprintf so that it works in ASCII.
			nBytesWritten = fprintf(outputFile, "%d%c", *nextGrayValue, (nextCol ? ' ' : '\n') );
			}

		//Error check to ensure that some data has been written out.
		//If it hasn't cleans up, prints an error message and returns the error.
                if (nBytesWritten == 0){
                        free(pgm->commentLine);
                        free(pgm->imageData);
			
			errorHandling(EXIT_BAD_FILE_NAME, fileName);
                        return(EXIT_BAD_FILE_NAME);
                        }
                }       	
	return(0);
	}
