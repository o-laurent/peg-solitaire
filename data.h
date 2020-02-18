void saveGame (state** board, int turn, time_t time);
void loadGame (state** board, long long int returned[2]);
int isThereASavedGame();
int readNumberOfGames();
double totalPlayingTime();
void implementStats(double time);