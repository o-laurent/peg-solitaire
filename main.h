#include "structures.h"
typedef enum state{ball, empty, out} state;

int makePossibleMoves(state board[7][7], movementList* moveList);
int moveNb(state board[7][7]);
void initBoard(state board[7][7]);
int ballNb(state board[7][7]);
int correctMove(state board[7][7], movement* move);
int possibleMove(state board[7][7]);
void doMove(state board[7][7], movement* move);
void userMove(state board[7][7]);
void printBoard(state board[7][7]);
int userGame();

typedef struct trajectory trajectory;
struct trajectory {
    //Remembers the different steps
    state board[7][7]; //DOESNT WORK
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
