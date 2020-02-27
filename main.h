#ifndef _MAIN_H_
#define _MAIN_H_
#include "structures.h"

//main.c
int makePossibleMoves(state **board, movementList* moveList, char lineNb, char colNb);
int moveNb(state **board, char lineNb, char colNb);
void initBoard(state **board);
int ballNb(state **board, char lineNb, char colNb);
int correctMove(state **board, movement* move);
int possibleMove(state **board, char lineNb, char colNb);
void doMove(state **board, movement* move);
void userMove(state **board, int* pquit, char lineNb, char colNb);
void printBoard(state **board);
int userGame(int* pquit, trajectory** pTrajectory, state** board, int* turn, char lineNb, char colNb);

//data.c
void saveGame (state** board, int turn, double time);
void rmSavedGame();
void loadGame (state** board, long long int returned[2]);
int isThereASavedGame();
int readNumberOfGames();
double totalPlayedTime();
void implementStats(double time);

//uiBoard.c
void printBoardV(state **board, char lineNb, char colNb);
void printTrajectory(trajectory* trajOrigin);
void printTrajectoryN(trajectoryNode* trajOrigin);
void rmTrajectory();
void saveTrajectory(trajectory* trajOrigin);
void saveTrajectoryN(trajectoryNode* trajOrigin, long int time, int boardNumber);
state** readBoard(char* fileName, char* lineNb, char* colNb);

//rules.c
void printRules();

//autosolve.c
trajectoryNode* autosolve(trajectoryNode* pTrajectory, int* boardNb, int* stop, int beamWidth, int* nodeAlloc, int* nodeFree, int* boardAlloc, int* boardFree);


typedef struct node node;
movementList* consML(movement* move, movementList* moveList);

void copyBoard(state** boardI, state** boardO, char length, char width) {
    for(int i=0; i<length; i++){
        for(int j=0; j<width; j++){
            boardO[i][j] = boardI[i][j];
        }
    }
}
#endif