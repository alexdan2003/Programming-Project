Project Description and Status

This project is a series of modules about the creation and modification of .pgm files. This project has four main parts currently, those being pgmEcho, pgmComp, pgma2b and pgmb2a, and finally pgmReduce.
Currently all four tasks are working correctly, however for pgmReduce the binary files are not working correctly leading to it being incomplete somewhat.

For handling the files all pgm files and code files should be kept in the Assessment_1 directory to ensure that they work correctly and after this has been achieved simply run the make file to 
compile all of the different modules. You can also run individual makes on the modules if you would so desire.

How to run pgmEcho

To run pgmEcho you require three args the ./pgmEcho arg to actually call the program, the input file and the output file. To see this properly simply type ./pgmEcho into the command line 
and it will show you the correct way to run it. 

How pgmEcho works

pgmEcho works by taking the given inputFile and running it in the readFile file that I have created. From there it will gather all necessary data and place it into a structure. Afterwards it will 
take the pgmstruct it has and run writeFile in the writeFile file that I have created. This will read all the information from inside of the structure into the file echoing it as it is meant to do.

How to run pgmComp

To run pgmComp you require three args the ./pgmComp arg to actually call the program, the first file and the second file. To see this properly simply type ./pgmComp into the command line
and it will show you the correct way to run it.

How pgmComp works

pgmComp works by taking the first file and running it in the readFile file, placing all the information within the pgm structure. Then it takes the second file and runs it in the readFile file, 
placing all the information within a different pgm structure. Then it will compare them in compareFile, ensuring that the two are identical.

How to run pgma2b 

To run pgma2b you require three args the ./pgma2b arg to actually call the program, the input file and the output file. To see this properly simply type ./pgma2b into the command line
and it will show you the correct way to run it.

How pgma2b works

pgma2b works by taking the input file and running it in the readFile file, placing all the information within the pgm structure. Then it converts the magic number to the opposite file type and
runs the writeFile file to place all the information within the file into the output file in the opposite way that the original was handed in.

How to run pgmb2a

To run pgmb2a you require three args the ./pgmb2a arg to actually call the program, the input file and the output file. To see this properly simply type ./pgmb2a into the command line
and it will show you the correct way to run it.

How pgmb2a works

pgmb2a works by taking the input file and running it in the readFile file, placing all the information within the pgm structure. Then it converts the magic number to the opposite file type and
runs the writeFile file to place all the information within the file into the output file in the opposite way that the original was handed in.

How to run pgmReduce

To run pgmReduce you require four args the ./pgmReduce arg to actually call the program, the input file, the user inputted reduction and the output file. To see this properly simply type ./pgmReduce
into the command line and it will show you the correct way to run it.

How pgmReduce works

pgmReduce works by taking an input file and reading all the valid information into the pgm structure. Following this it will reduce the file by the user inputted reduction value, which it then places
into the output file giving it the reduced look to the file as it has fewer bytes within it.
