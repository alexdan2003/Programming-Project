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
		free(pgm->commentLine);
		int height = 0;
		for (height=0; height < pgm->height; height++){
			free(pgm->imageData[height]);
			}
		free(pgm->imageData);
		free(pgm);
                errorHandling(EXIT_BAD_FILE_NAME, fileName);
                return(EXIT_BAD_FILE_NAME);
                }

	//Opens file given to it by fileName.
	FILE *outputFile = fopen(fileName, "w");

	//Error check to ensure that the fileName is valid.
	//If it isn't cleans up, prints an error message and returns the error.
	if (outputFile == NULL){
		free(pgm->commentLine);
		int height = 0;
		for (height=0; height < pgm->height; height++){
			free(pgm->imageData[height]);
			}
		free(pgm->imageData);
		free(pgm);
		errorHandling(EXIT_BAD_FILE_NAME, fileName);
		return(EXIT_BAD_FILE_NAME);
		}	

	//Prints the width, height and maxGray to the file and holds the size of this in nBytesWritten.
	size_t nBytesWritten = fprintf(outputFile, "P%c\n%d %d	\n%d\n", pgm->magic_number[1], pgm->width, pgm->height, pgm->maxGray);
	
	//Error check to ensure that the values above have been written to the file.
	//If it hasn't cleans up, prints an error message and returns the error.
        if (nBytesWritten < 0){
                free(pgm->commentLine);
		int height = 0;
		for (height=0; height < pgm->height; height++){
			free(pgm->imageData[height]);
			}
                free(pgm->imageData);
		free(pgm);
		
		errorHandling(EXIT_BAD_FILE_NAME, fileName);
                return(EXIT_BAD_FILE_NAME);
                }

	//Checks if the magic number is an Ascii number, if it is runs the code below which
	//writes the data from the imageData array into the output file.
	if (pgm->magic_number[0] == 'P' && pgm->magic_number[1] == '2'){
		//Runs through the columns and rows and does math to ensure that a new row is started at the correct location.
		int height = 0;
		for (height=0; height < pgm->height; height++){
			int nextCol = 0;
			int width = 0;
			for (width=0; width < pgm->width; width++){
				//Checks whether the next pixel should be a new column, if it is then it gives it a newline character.
				if (width+1 == pgm->width){
					nextCol = 0;
					}
				else{
					nextCol = 1;
					}
				//Writes the data from the imageData array into the output file. 	
				nBytesWritten = fprintf(outputFile, "%d%c", pgm->imageData[height][width], (nextCol ? ' ' : '\n'));
				}
			}
		}
	//Checks if the magic number is a Binary number, if it is runs the code below which 
	//write the data from the imageData rray into the output file.	
	else if (pgm->magic_number[0] == 'P' && pgm->magic_number[1] == '5'){
		//Writes the code from the imagData array a bit at a time straight into the output file.
		unsigned char* nextGrayValue;	
		int height = 0;
		for (height=0; height < pgm->height; height++){
			int width = 0;
			for (width=0; width < pgm->width; width++){
				nextGrayValue = &pgm->imageData[height][width];	
				nBytesWritten = fwrite(nextGrayValue, 1, 1, outputFile);
				}	
			}
		}   	

	//Closes the file and returns an exit with no errors.
	fclose(outputFile);
	return(EXIT_NO_ERRORS);
	}
