#include "structures.h"
typedef enum state{ball, empty, out} state;

int makePossibleMoves(state **board, movementList* moveList);
int moveNb(state **board);
void initBoard(state **board);
int ballNb(state **board);
int correctMove(state **board, movement* move);
int possibleMove(state **board);
void doMove(state **board, movement* move);
void userMove(state **board, int* pquit);
void printBoard(state **board);

void saveGame (state** board, int turn, time_t time);
void loadGame (state** board, long long int returned[2]);

typedef struct trajectory trajectory;
struct trajectory {
    //Remembers the different steps
    state **board; //DOESNT WORK
    trajectory* next;
};

int userGame(int* pquit, trajectory** pTrajectory, state** board, int* turn);

trajectory* consT (state** board, trajectory* pTrajectory) {
    //Add a board on the top of the list
    trajectory* tmp = malloc(sizeof(trajectory));
    if (tmp == NULL) {
        printf("ERREUR");
        return NULL;
    }
    tmp->board = board;
    tmp->next = pTrajectory;

    return tmp;
}

void copyBoard (state** boardI, state** boardO) {
    for(int i=0;i<7;i++){
        for(int j=0;j<7;j++){
            boardO[i][j] = boardI[i][j];
        }
    }
}