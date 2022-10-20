CC = gcc
CCFLAGS = -g -std=c99 -Wall
MODULES = readFile.o writeFile.o compareFile.o reduceFile.o errorHandling.o
MAINS = pgmEcho.o pgmComp.o pgma2b.o pgmb2a.o pgmReduce.o pgmTile.o
TARGETS = pgmEcho pgmComp pgma2b pgmb2a pgmReduce pgmTile


all: ${TARGETS}

clean:
	rm ${MODULES} ${MAINS} ${TARGETS}

pgmEcho:	pgmEcho.o 	${MODULES}
	${CC} ${CCFLAGS} -o pgmEcho pgmEcho.o ${MODULES}

pgmComp:	pgmComp.o 	${MODULES}
	${CC} ${CCFLAGS} -o pgmComp pgmComp.o ${MODULES}

pgma2b:		pgma2b.o 	${MODULES}
	${CC} ${CCFLAGS} -o pgma2b pgma2b.o ${MODULES}

pgmb2a:		pgmb2a.o	${MODULES}
	${CC} ${CCFLAGS} -o pgmb2a pgmb2a.o ${MODULES}

pgmReduce: 	pgmReduce.o	${MODULES}
	${CC} ${CCFLAGS} -o pgmReduce pgmReduce.o ${MODULES}

pgmTile:	pgmTile.o	${MODULES}
	${CC} ${CCFLAGS} -o pgmTile pgmTile.o ${MODULES}

pgmEcho.o:	pgmEcho.c	readFile.h writeFile.h fileStructure.h definitions.h errorHandling.h
	${CC}	-c ${CCFLAGS}	-o pgmEcho.o pgmEcho.c

pgmComp.o:	pgmComp.c	readFile.h compareFile.h fileStructure.h definitions.h errorHandling.h
	${CC}	-c $(CCFLAGS)	-o pgmComp.o pgmComp.c

pgma2b.o:	pgma2b.c	readFile.h writeFile.h fileStructure.h definitions.h errorHandling.h
	${CC}	-c ${CCFLAGS}	-o pgma2b.o pgma2b.c

pgmb2a.o:	pgmb2a.c	readFile.h writeFile.h fileStructure.h definitions.h errorHandling.h
	${CC}	-c ${CCFLAGS}	-o pgmb2a.o pgmb2a.c

pgmReduce.o:	pgmReduce.c	readFile.h writeFile.h reduceFile.h fileStructure.h definitions.h errorHandling.h
	${CC}	-c ${CCFLAGS}	-o pgmReduce.o pgmReduce.c

pgmTile.o:	pgmTile.c	readFile.h writeFile.h fileStructure.h definitions.h errorHandling.h
	${CC}	-c ${CCFLAGS}	-o pgmTile.o pgmTile.c
