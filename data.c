void saveGame (state** board, int turn, time_t time) {
    FILE *out;
    out = fopen ("data/save.txt", "wb");
    if (out == NULL) {
        printf("La sauvegarde a échoué...\n");
    }
    for (int i=0; i<7; i++) {
        for (int j=0; j<7; j++) {
            fprintf(out, "%d \n",board[i][j]);
        }
    }
    fprintf(out, "%d \n",turn);
    fprintf(out, "%ld \n",time);

    fclose(out);
}

int isThereASavedGame() {
    // Returns 1 if there is a saved game that can be resumed
    FILE *in;
    in = fopen ("data/save.txt", "rb");
    if (in == NULL) {
        return 0;
    }
    return 1;
}

//we have to initialize an empty board before calling the function
//the function will change the values of this board
void loadGame (state** board, long long int returned[2]) {
    FILE *in;
    int x;
    in = fopen ("data/save.txt", "rb");
    if (in == NULL) {
        printf("Le chargement de la partie précédente a échoué...\n");
    }
    unsigned char error = 0;
    for (int i=0; i<7; i++) {
        for (int j=0; j<7; j++) {
            fscanf (in, "%d",&x);
            if (x==0) {
                board[i][j]=ball;
            }
            else if (x==1) {
                board[i][j]=empty;
            }
            else if (x==2) {
                board[i][j]=out;
            }
            else {
                printf("Erreur lors du téléchargement des données...\n");
                error++;
            }
        }
    }
    fscanf (in, "%lld", &returned[0]);
    fscanf (in, "%lld", &returned[1]);
    if (error!=0) {
        returned[0] = -1;
        returned[1] = -1;
    }
    fclose(in);
}