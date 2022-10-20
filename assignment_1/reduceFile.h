#ifndef reduceFile_h
#define reduceFile_h

int reduceFile(pgmFile *pgm, pgmFile *pgmReduced, double reduceFactor);

int setupPGM(pgmFile *pgm, pgmFile *pgmReduced, int reducedWidth, int reducedHeight);

#endif
