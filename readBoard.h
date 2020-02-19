typedef enum state {ball, empty, out} state;

void printBoardV(state **board, char lineNb, char colNb);
state** readBoard (char* fileName, char* lineNb, char* colNb);