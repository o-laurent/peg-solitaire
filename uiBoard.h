#include "structures.h"

//main.h
void initBoard(state **board);

//Printing functions
void printBoardV(state **board, char lineNb, char colNb);
void printTrajectory(trajectory* trajOrigin);

//Saving functions 
void rmTrajectory();
void saveTrajectory(trajectory* trajOrigin);

//Reading functions
state** readBoard (char* fileName, char* lineNb, char* colNb);