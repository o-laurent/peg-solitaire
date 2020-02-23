#ifndef AUTOSOLVE_H_
#define AUTOSOLVE_H_
#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#endif

//autosolve.c
trajectoryNode* autosolve(trajectoryNode* pTrajectory, int* boardNb);

//main.c
int correctMove(state **board, movement* move);
void doMove(state **board, movement* move);
int ballNb(state **board);
void copyBoard(state** boardI, state** boardO);
int moveNb(state **board);

//uiBoard.c
void printBoardV(state **board, char lineNb, char colNb);

//current file
float cost_f(state** board);