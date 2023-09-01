typedef enum state { ball, empty, out } state;

// uiBoard.c
state **readBoard(char *fileName, char *lineNb, char *colNb);

// curent
int ruleOftheThree(state **board);