#ifndef definitions_h
#define definitions_h

//File made to hold onto all needed definitons to save repeating them in each file.

//Defines all needed error codes each with their own purpose.
#define EXIT_NO_ERRORS 0
#define EXIT_WRONG_ARG_COUNT 1
#define EXIT_BAD_FILE_NAME 2 
#define EXIT_BAD_MAGIC_NUMBER 3
#define EXIT_BAD_COMMENT_LINE 4
#define EXIT_BAD_DIMENSIONS 5
#define EXIT_BAD_GRAY_VALUE 6
#define EXIT_IMAGE_MALLOC_FAILED 7
#define EXIT_BAD_DATA 8
#define EXIT_OUTPUT_FAILED 9
#define EXIT_BAD_LAYOUT_FILe 10
#define EXIT_MISCELLANEOUS 100

//Defines essential numbers here that will not change no matter on the program.
#define MAGIC_NUMBER_RAW_PGM 0x3550
#define MAGIC_NUMBER_ASCII_PGM 0x3250
#define MIN_IMAGE_DIMENSION 1
#define MAX_IMAGE_DIMENSION 65536
#define MAX_COMMENT_LINE_LENGTH 128

#endif
