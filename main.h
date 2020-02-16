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
int userGame(int* pquit);

typedef struct trajectory trajectory;
struct trajectory {
    //Remembers the different steps
    state **board; //DOESNT WORK
    trajectory* next;
};

void innerConst(state* boardTmp[7][7], state* board[7][7]) {

}

/*trajectory* consT (state* board[7][7], trajectory* uTrajectory) {
    trajectory* tmp = malloc(sizeof(trajectory));
    if (tmp == NULL) {
        printf("ERREUR");
        return NULL;
    }
    innerConsT(tmp->board, board);
    tmp->next = uTrajectory;
    return tmp;
}
*/
