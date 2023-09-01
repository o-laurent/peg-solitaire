#include "structures.h"

// main.h
void initBoard(state** board);

// Printing functions
void printBoardV(state** board, char lineNb, char colNb);
void printTrajectory(trajectory* trajOrigin, char lineNb, char colNb);
void printTrajectoryN(trajectoryNode* trajOrigin, char lineNb, char colNb);

//Saving functions 
void rmTrajectory();
void saveTrajectory(trajectory* trajOrigin, char lineNb, char colNb);
void saveTrajectoryN(trajectoryNode* trajOrigin, long int time, int boardNumber, char lineNb, char colNb);

//Reading function
state** readBoard (char* fileName, char* lineNb, char* colNb);