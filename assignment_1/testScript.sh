#!/bin/sh

#Test script for all tasks

#Compiling all files
make all

echo ""

#All tests for PgmEcho
echo "Testing pgmEcho"

echo ""
echo "Testing pgmEcho with no file arguments (argc == 1)"
./pgmEcho

echo "" 
echo "Testing pgmEcho with one file argument (argc == 2)"
./pgmEcho slice0a.pgm

echo ""
echo "Testing pgmEcho with three file arguments (argc == 4)"
./pgmEcho slice0a.pgm output.pgm slice0b.pgm

echo ""
echo "Testing pgmEcho with invalid input file"
./pgmEcho invalidFile.pgm output.pgm

echo ""
echo "Testing pgmEcho with invalid output file"
./pgmEcho slice0a.pgm output.txt

echo ""
echo "Testing pgmEcho with no magic number"
./pgmEcho noMagicNumber.pgm output.pgm

echo ""
echo "Testing pgmEcho with invalid comment line length"
./pgmEcho invalidCommentLine.pgm output.pgm

echo "" 
echo "Testing pgmEcho with no height"
./pgmEcho noHeight.pgm output.pgm

echo "Testing pgmEcho with no width"
./pgmEcho noWidth.pgm output.pgm

echo ""
echo "Testing pgmEcho with invalid height"
./pgmEcho invalidHeight.pgm output.pgm

echo ""
echo "Testing pgmEcho with invalid width"
./pgmEcho invalidWidth.pgm output.pgm

echo ""
echo "Testing pgmEcho with no ASCII image data"
./pgmEcho noAsciiData.pgm output.pgm

echo "" 
echo "Testing pgmEcho with invalid ASCII image data" 
./pgmEcho invalidAsciiData.pgm output.pgm

echo ""
echo "Testing pgmEcho with no Binary image data"
./pgmEcho noBinaryData.pgm output.pgm

echo "" 
echo "Testing pgmEcho with valid ASCII files"
./pgmEcho slice0a.pgm output.pgm

echo "" 
echo "Testing pgmEcho with valid Binary files"
./pgmEcho slice0b.pgm output.pgm


echo "" 
#All tests for pgmComp

echo ""
echo "Testing pgmComp with no file arguments (argc == 1)" 
./pgmComp

echo ""
echo "" 
echo "Testing pgmComp with one file argument (argc == 2)"
./pgmComp slice0a.pgm

echo ""
echo "Testing pgmComp with three file arguments (argc == 2)"
./pgmComp slice0a.pgm output.pgm output.pgm

echo ""
echo "Testing pgmComp with one invalid file"
./pgmComp slice0a.pgm notValid.pgm

echo "" 
echo "Testing pgmComp with valid different ASCII files"
./pgmComp slice0a.pgm lenaAscii.pgm

echo "" 
echo "Testing pgmComp with valid identical ASCII files"
./pgmComp slice0a.pgm slice0a2.pgm

echo ""
echo "Testing pgmComp with valid different Binary files"
./pgmComp slice0b.pgm lena.pgm

echo "" 
echo "Testing pgmComp with valid identical Binary files"
./pgmComp slice0b.pgm slice0b2.pgm


echo "" 
#All tests for pgma2b

echo ""
echo "Testing pgma2b with no file arguments (argc == 1)"
./pgma2b

echo "" 
echo "" 
echo "Testing pgma2b with one file argument (argc == 2)"
./pgma2b slice0a.pgm

echo "" 
echo "Testing pgma2b with three file arguments (argc == 4)"
./pgma2b slice0a.pgm output.pgm output.pgm  

echo "" 
echo "Testing pgma2b with invalid input file"
./pgma2b notValid.pgm output.pgm

echo "" 
echo "Testing pgma2b with invalid output file"
./pgma2b slice0a.pgm notValid.txt

echo ""
echo "Testing pgma2b with invalid input file type"
./pgma2b slice0b.pgm output.pgm

echo "" 
echo "Testing pgma2b with valid files"
./pgma2b slice0a.pgm output.pgm


echo ""
#All tests for pgmb2a

echo ""
echo "Testing pgmb2a with no file arguments (argc == 1)"
./pgmb2a

echo "" 
echo "" 
echo "Testing pgmb2a with one file argument (argc == 2)"
./pgmb2a slice0b.pgm

echo ""
echo "Testing pgmb2a with three file arguments (argc == 4)"
./pgmb2a slice0b.pgm output.pgm output.pgm

echo "" 
echo "Testing pgmb2a with invalid input file"
./pgmb2a notValid.pgm output.pgm

echo "" 
echo "Testing pgmb2a with invalid output file"
./pgmb2a slice0b.pgm notValid.txt

echo "" 
echo "Testing pgmb2a with invalid input file type"
./pgmb2a slice0a.pgm output.pgm

echo "" 
echo "Testing pgmb2a with valid files"
./pgmb2a slice0b.pgm output.pgm

echo ""
#All tests for pgmReduce

echo ""
echo "Testing pgmReduce with no file arguments (argc == 1)"
./pgmReduce

echo ""
echo "" 
echo "Testing pgmReduce with one file arguments (argc == 2)"
./pgmReduce lena.pgm 

echo ""
echo "Testing pgmReduce with four file arguments (argc == 4)"
./pgmReduce lena.pgm 2 output.pgm output.pgm

echo "" 
echo "Testing pgmReduce with invalid input file"
./pgmReduce notValid.pgm 2 output.pgm

echo ""
echo "Testing pgmReduce with invalid output file"
./pgmReduce lena.pgm 2 output.txt 

echo "" 
echo "Testing pgmReduce with invalid reduce factor"
./pgmReduce lena.pgm -5 output.pgm

echo "" 
echo "Testing pgmReduce with valid files"
./pgmReduce lena.pgm 2 output.pgm
