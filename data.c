#include <stdio.h>
#include <stdlib.h>
#include "data.h"

void saveGame (state** board, int turn, double time) {
    FILE *out;
    out = fopen ("data/save.txt", "wb");
    if (out == NULL) {
        printf("La sauvegarde a échoué...\n");
    }
    for (int i=0; i<7; i++) {
        for (int j=0; j<7; j++) {
            fprintf(out, "%d \n", board[i][j]);
        }
    }
    fprintf(out, "%d \n", turn);
    fprintf(out, "%lf \n", time);
    fclose(out);
}

void rmSavedGame() {
    remove("data/save.txt");
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

//nb of games (first line of stats)
//gives back 0 if there is nthg saved, otherwise it gives us the saved number
int readNumberOfGames() {
    FILE *in;
    int x;
    in = fopen ("data/stats.txt", "rb");
    if (in == NULL) {
        return 0;
    }
    else if (feof (in)) {
        return 0;
    }
    else {
        fscanf (in, "%d",&x);
        return x;
    }
    fclose(in);
}

//total time (second line of stats)
//gives back 0 if there is nthg saved, otherwise it gives us the saved number
double totalPlayedTime() {
    FILE *in;
    int x;
    double y;
    in = fopen ("data/stats.txt", "rb");
    if (in == NULL) {
        return 0;
    }
    else if (feof(in)) {
        return 0;
    }
    else {
        fscanf (in, "%d",&x);
        fscanf (in, "%f",&y);
        return y;
    }
    fclose(in);
}

void implementStats(double time) {
    int x;
    double y;
    x=readNumberOfGames();
    y=totalPlayedTime();
    x++;
    y=y+time;
    
    FILE *out;
    out = fopen ("data/stats.txt", "wb");
    fprintf(out, "%d\n",x);
    fprintf(out, "%lf\n",y);
}