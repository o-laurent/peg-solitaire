#ifndef AUTOSOLVE_H_
#define AUTOSOLVE_H_
#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#endif

//autosolve.c
trajectoryNode* autosolve(trajectoryNode* pTrajectory, int* boardNb, int* stop, int beamWidth, int* nodeAlloc, int* nodeFree, int* boardAlloc, int* boardFree, char lineNb, char colNb);
//trajectoryNode* rmtTN(trajectoryNode* pTrajectory, int* nodeFree, int* boardFree, int lineNb);
trajectoryNode* rmtTN_Node(trajectoryNode* pTrajectory, int* nodeFree, int* boardFree, char lineNb);
//main.c
int correctMove(state **board, movement* move, char lineNb, char colNb);
void doMove(state **board, movement* move);
int ballNb(state **board, char lineNb, char colNb);
void copyBoard(state** boardI, state** boardO, char lineNb, char colNb);
int moveNb(state **board, char lineNb, char colNb);

//uiBoard.c
void printBoardV(state **board, char lineNb, char colNb);

//current file
int cost_f(state** board, char lineNb, char colNb);