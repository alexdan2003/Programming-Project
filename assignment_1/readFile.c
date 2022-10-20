//Included for file I/O operations and String handling operations.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Files necessary for the program to run correctly.
#include "errorHandling.h"
#include "fileStructure.h"
#include "definitions.h"

//Function to read the magic number from the file into the pgm struct. 
int readMagicNumber(pgmFile *pgm, FILE *inputFile){
	//Initialises two variables to get both forms of the magic number.
	unsigned char magic_number[2] = {'0', '0'};
	unsigned short *magic_Number = (unsigned short *) magic_number;
	//Grabs the magic number from the file placing it into the char variable.
	magic_number[0] = getc(inputFile);
	magic_number[1] = getc(inputFile);

	//Checks if the magic number is a valid magic number in ASCII or binary.
	//Cleans up and errors out otherwise.
	if ((*magic_Number != MAGIC_NUMBER_ASCII_PGM) && (*magic_Number != MAGIC_NUMBER_RAW_PGM)){
		free(pgm);
		fclose(inputFile);
		return(EXIT_BAD_MAGIC_NUMBER);
		}

	//Places the variables into the actual pgm struct.
	pgm->magic_number[0] = magic_number[0];
	pgm->magic_number[1] = magic_number[1];
	pgm->magic_Number = magic_Number;
	return(EXIT_NO_ERRORS);
	}

//Function to read the comment line from the file into the pgm struct.
int readCommentLine(pgmFile *pgm, FILE *inputFile){
	//Allocates the memory in the pgm struct for the commentLine character string.	
	pgm->commentLine = (char *) malloc(MAX_COMMENT_LINE_LENGTH + 1);
	//Grabs the commentLine from the file placing it into the pgm and into the comment string char.
	char *commentString = fgets(pgm->commentLine, MAX_COMMENT_LINE_LENGTH + 1, inputFile);

	//Checks the commentString to ensure that the commentLine is valid. 
	//Cleans up and errors out otherwise.
	if ((commentString == NULL) || (strlen(commentString) >= MAX_COMMENT_LINE_LENGTH)){
		free(pgm->commentLine);
		free(pgm);
		fclose(inputFile);
		return(EXIT_BAD_COMMENT_LINE);
		}	
	
	return(EXIT_NO_ERRORS);
	}

//Function to read the height, width, maxGray and imageData from the file.
int readImageData(pgmFile *pgm, FILE *inputFile){
	//Defines basic values for the file data.
	unsigned int width = 0, height = 0;
	unsigned int maxGray = 255;
	
	//Reads in the width, height and maxGray from the file, placing them in the variables above.
	int scanCount = fscanf(inputFile, " "); 
	
	scanCount = fscanf(inputFile, " %u %u %u", &(width), &(height), &(maxGray));

	//Error checking to ensure that there is a value for all three and valid dimensions for width and height.
	//If there are it cleans up and returns an error.
	if ((scanCount != 3) ||
	    (width <= MIN_IMAGE_DIMENSION) ||
	    (width >= MAX_IMAGE_DIMENSION) ||
	    (height <= MIN_IMAGE_DIMENSION) ||
	    (height >= MAX_IMAGE_DIMENSION)){
		free(pgm->commentLine);
		free(pgm);
		fclose(inputFile);
		return(EXIT_BAD_DIMENSIONS);
		}

	//Checks that the maxGray is valid.
	//If it isn't then it cleans up and returns an error.
	if ((maxGray < 0) || (maxGray > 255)){
		free(pgm->commentLine);
		free(pgm);
		fclose(inputFile);
		return(EXIT_BAD_GRAY_VALUE);
		}

	//Sets the width, height and maxGray in the pgm structure.
	pgm->width = width;
	pgm->height = height;
	pgm->maxGray = maxGray;

	//Mallocs the imageData two dimensional array, doing it by columns and rows.
	pgm->imageData = (unsigned char**) malloc(pgm->height * sizeof(unsigned char*));
	int loopHeight = 0;
	for (loopHeight=0; loopHeight < pgm->height; loopHeight++){
		pgm->imageData[loopHeight] = (unsigned char*) malloc(pgm->width * sizeof(unsigned char));
		//Checks each row to see if the Malloc has been successful erroring out if it isn't.
		if (pgm->imageData[loopHeight] == NULL){
			free (pgm->commentLine);
			fclose(inputFile);
			return(EXIT_IMAGE_MALLOC_FAILED);
			}
		}

	//Checks the entire imageData array to ensure that it has been successful overall.
	if (pgm->imageData == NULL){
		free(pgm->commentLine);
		free(pgm);
		fclose(inputFile);
		return(EXIT_IMAGE_MALLOC_FAILED);
		}

	//Checks the magic number to see whether the file is Ascii, if it is it then runs the code below
	//which reads the data from the file into the imageData struct.
	if (pgm->magic_number[0] == 'P' && pgm->magic_number[1] == '2'){
		//Runs through the height and width of the pgm, splitting it up into columns and rows.
		for (loopHeight=0; loopHeight < pgm->height; loopHeight++){
			int width = 0;
			for (width=0; width < pgm->width; width++){
				//Sets the grayValue and then reads the grayValue from the file into it.
				int grayValue = -1;
				int scanCount = fscanf(inputFile, " %u", &grayValue);				
				
				//Error checking to ensure the grayValue is valid or that something has been written into it.
				if ((scanCount != 1) || (grayValue < 0) || (grayValue > 255)){
					free(pgm->commentLine);
					for (loopHeight=0; loopHeight < pgm->height; loopHeight++){
						free(pgm->imageData[loopHeight]);
						}
					free(pgm->imageData);
					free(pgm);
					fclose(inputFile);			
					return(EXIT_BAD_DATA);
					}
				
				//Sets the grayValue to its corresponding location inside of the 2d array.
				pgm->imageData[loopHeight][width] = grayValue;
				}
			}
		//Error checking to ensure that the file does not have too much data within it. 
		int grayValue = -1;
		int scanCount = fscanf(inputFile, " %u", &grayValue);
		if (scanCount != -1){
			free(pgm->commentLine);
			for (loopHeight=0; loopHeight < pgm->height; loopHeight++){
				free(pgm->imageData[loopHeight]);
				}
			free(pgm->imageData);
			free(pgm);
			fclose(inputFile);
			return(EXIT_BAD_DATA);
			}
		}
	//Checks the magic number to see whether the file is Binary, if it is then runs the code below
	//which reads the data from the file into the imageData struct.
	else if (pgm->magic_number[0] == 'P' && pgm->magic_number[1] == '5'){
		//Works out the expected number of bytes in the image and stores it in the variable.
		int nImageBytes = pgm->height * pgm->width;
		//Creates a string the size of the image bytes, which it stores the data within during the fread.
		unsigned char* imageDataString = NULL;
		imageDataString = (unsigned char*) malloc(nImageBytes);
		int sizeOfImage = fread(imageDataString, 1, nImageBytes, inputFile);
		//Checks that the size of fread matches up with the size of the image bytes to ensure that the 
		//correct amount of data has been read. If not it errors out.
		if (sizeOfImage != nImageBytes){
			free(pgm->commentLine);
			for (height=0; height < pgm->height; height++){
				free(pgm->imageData[height]);
				}
			free(pgm->imageData);
			free(pgm);
			free(imageDataString);
			fclose(inputFile);
			return(EXIT_BAD_DATA);
			}

		//Runs through the entirety of the imageDataString placing the data within into the two dimensional array
		//at its corresponding location.
		int count = 0; 
		for (height=0; height < pgm->height; height++){
			int width = 0;
			for (width=0; width < pgm->width; width++){
				pgm->imageData[height][width] = imageDataString[count];
				count++;			
				}
			}

		//Checks that the bit after all of the data has been read is empty, to ensure that there is not
		//too much data. If there is it errors out.
		int grayValue = -1;
		int scanCount = fscanf(inputFile, " %u", &grayValue);
		if (scanCount == 1){
			free(pgm->commentLine);
			for (height=0; height < pgm->height; height++){
				free(pgm->imageData[height]);
				}
			free(pgm->imageData);
			free(pgm);
			fclose(inputFile);
			return(EXIT_BAD_DATA);
			}
		}

	return(EXIT_NO_ERRORS);
	}

//Main function of the program, runs all functions within the file,
//filling up the handed in pgm struct with all the data it needs.
int readFile(pgmFile *pgm, char* fileName){
	//Error check to ensure that the file is a pgm file.
	//If it isn't prints an error message and returns the error.
	if ((fileName[strlen(fileName)-2] != 'g') || (fileName[strlen(fileName)-1] != 'm')){
		errorHandling(EXIT_BAD_FILE_NAME, fileName);
		return(EXIT_BAD_FILE_NAME);
		}
	
	//Opens file given to it in fileName.
        FILE *inputFile = fopen(fileName, "r");

	//Error check to ensure that the fileName is valid.
        if (inputFile == NULL){
		errorHandling(EXIT_BAD_FILE_NAME, fileName);
                 return(EXIT_BAD_FILE_NAME);
	        }

	//Runs function to find the magic number inside of the file and place in struct.
	//Checks for error code, if found prints out error message and returns the code.
	int errorCode = readMagicNumber(pgm, inputFile);
        if (errorCode != EXIT_NO_ERRORS){
		errorHandling(errorCode, fileName);
		return(errorCode); 	
		}

	//Grabs the next character from the file.
	int scanCount = fscanf(inputFile, " ");
        char nextChar = fgetc(inputFile);
	//Checks if the next character belongs to a comment and runs commentLine function if it is. 
        if (nextChar == '#'){
		//Checks for error code, if found prints out error message and returns the code.
		errorCode = readCommentLine(pgm, inputFile); 
                if (errorCode != EXIT_NO_ERRORS){
			errorHandling(errorCode, fileName);
			return(errorCode);
			}
                }
	//If no comment symbol is fine it returns the character back into the file.
        else{
                ungetc(nextChar, inputFile);
                }
	
	//Runs function to find the size, width and imageData of the file.
	//Checks for error code, if found prints out error message and returns the code.
	errorCode = readImageData(pgm, inputFile);
	if (errorCode != EXIT_NO_ERRORS){
		errorHandling(errorCode, fileName);
		return(errorCode);
		}
	//Closes file to ensure good cleanup.
	fclose(inputFile);
	return(EXIT_NO_ERRORS);
        }
