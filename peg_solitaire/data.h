typedef enum state
{
    ball,
    empty,
    out
} state;

void saveGame(state **board, int turn, double time);
void rmSavedGame();
void loadGame(state **board, long long int returned[2]);
int isThereASavedGame();
int readNumberOfGames();
double totalPlayedTime();
void implementStats(double time);