#include "structures.h"

//main.h
void initBoard(state **board);

//Printing functions
void printBoardV(state **board, char lineNb, char colNb);
void printTrajectory(trajectory* trajOrigin);
void printTrajectoryN(trajectoryNode* trajOrigin);

//Saving functions 
void rmTrajectory();
void saveTrajectory(trajectory* trajOrigin);
void saveTrajectoryN(trajectoryNode* trajOrigin, long int time, int boardNumber);

//Reading function
state** readBoard (char* fileName, char* lineNb, char* colNb);