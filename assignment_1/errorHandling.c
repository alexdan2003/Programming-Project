//Included for file I/O operations and String handling operations.
#include <stdio.h>
#include <stdlib.h>

//Function to handle all error messages.
//Takes in an error code and a piece of text and outputs an appropiate response.
void errorHandling(int errorCode, char* text){
	if (errorCode == 1){
		printf("ERROR: Bad Argument Count\n");
		}
	
	if (errorCode == 2){
		printf("ERROR: Bad File Name (%s)\n", text);
		}	

	if (errorCode == 3){
		printf("ERROR: Bad Magic Number (%s)\n", text);
		}

	if (errorCode == 4){
		printf("ERROR: Bad Comment Line (%s)\n", text);
		}

	if (errorCode == 5){
		printf("ERROR: Bad Dimensions (%s)\n", text);
		}

	if (errorCode == 6){
		printf("ERROR: Bad Max Gray Value (%s)\n", text);
		}

	if (errorCode == 7){
		printf("ERROR: Image Malloc Failed\n");
		}

	if (errorCode == 8){
		printf("ERROR: Bad Data (%s)\n", text);
		}

	if (errorCode == 9){
		printf("ERROR: Output Failed (%s)\n", text);
		}
		
	if (errorCode == 10){
		printf("ERROR: Bad Layout\n");
		}
	
	if (errorCode == 100){
		printf("ERROR: Miscellaneous %s\n", text);
		}
	}
