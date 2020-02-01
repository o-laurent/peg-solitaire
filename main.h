typedef enum state{ball, empty, out} state;

void initBoard(state* board[7][7]);
int ballNb(state* board[7][7]);
int correctMove(state* board[7][7], movement* move);
int possibleMove(state* board[7][7]);
void doMove(state* board[7][7], movement* move);
void userMove(state* board[7][7]);
void printBoard(state board[7][7]);
void userGame();