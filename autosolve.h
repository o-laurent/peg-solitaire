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

//current file
float cost_f(state** board);