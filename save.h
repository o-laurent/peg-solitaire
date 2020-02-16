typedef enum state{ball, empty, out} state;
void saveGame (state** board, int turn, time_t time);
long int* loadGame (state** board);