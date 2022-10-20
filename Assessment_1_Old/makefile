CC=gcc
CCFLAGS = -g -std=c99

all: pgmEcho pgmComp pgma2b pgmb2a pgmReduce

clean:
	rm pgmEcho.o pgmComp.o pgma2b.o pgmb2a.o pgmReduce.o readFile.o writeFile.o compareFile.o reduceFile.o errorHandling.o

pgmEcho:      pgmEcho.o	readFile.o writeFile.o errorHandling.o 
	${CC} ${CCFLAGS} -o pgmEcho pgmEcho.o readFile.o writeFile.o errorHandling.o

pgmComp:	pgmComp.o	readFile.o compareFile.o errorHandling.o
	${CC} ${CCFLAGS} -o pgmComp pgmComp.o readFile.o compareFile.o errorHandling.o

pgma2b: 	pgma2b.o	readFile.o writeFile.o errorHandling.o
	${CC} ${CCFLAGS} -o pgma2b pgma2b.o readFile.o writeFile.o errorHandling.o

pgmb2a:		pgmb2a.o	readFile.o writeFile.o errorHandling.o
	${CC} ${CCFLAGS} -o pgmb2a pgmb2a.o readFile.o writeFile.o errorHandling.o

pgmReduce:	pgmReduce.o	readFile.o reduceFile.o errorHandling.o
	${CC} ${CCFLAGS} -o pgmReduce pgmReduce.o readFile.o reduceFile.o errorHandling.o
