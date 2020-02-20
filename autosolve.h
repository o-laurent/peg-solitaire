#ifndef AUTOSOLVE_H_
#define AUTOSOLVE_H_
#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#endif

//main.c
int correctMove(state **board, movement* move);
void doMove(state **board, movement* move);

//current file
float cost_f(state** board);