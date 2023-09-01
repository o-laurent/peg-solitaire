#include <stdio.h>
#include <stdlib.h>
#include "data.h"

//Cette fonction sauvegarde dans le fichier save.txt le plateau actuel, le nombre de tours ainsi que le temps de la partie
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

//Effacer le fichier de sauvegarde
void rmSavedGame() {
    remove("data/save.txt");
}

//Verifie s'il y a une partie sauvegardée
int isThereASavedGame() {
    // Retourne 1 s'il y a un partie sauvegardée 
    FILE *in;
    in = fopen ("data/save.txt", "rb");
    if (in == NULL) {
        return 0;
    }
    return 1;
}

//Il faut initialiser un plateau vide avant d'apeler cette fonction
//La fonction charge le plateau sauvegardé
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

//Renvoie 0 s'il n'y a rien de sauvegardé et le nombre de parties jouées sinon
int readNumberOfGames() {
    FILE *in;
    int x;
    in = fopen ("data/stats.txt", "rb");
    if (in == NULL) {
        fclose(in);
        return 0;
    }
    else if (feof (in)) {
        fclose(in);
        return 0;
    }
    else {
        fscanf (in, "%d",&x);
        fclose(in);
        return x;
    }
}

//Renvoie 0 s'il n'y a rien de sauvegardé et la durée de l'ensemble des parties jouées sinon
double totalPlayedTime() {
    FILE *in;
    int x;
    double y;
    in = fopen ("data/stats.txt", "rb");
    if (in == NULL) {
        fclose(in);
        return 0;
    }
    else if (feof(in)) {
        fclose(in);
        return 0;
    }
    else {
        fscanf (in, "%d",&x);
        fscanf (in, "%lf",&y);
        fclose(in);
        return y;
    }
}

//Prend en entrée la durée de la partie actuelle, l'ajoute au temps total de jeux 
//Implémente de 1 le nombre total de parties jouées
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
    fclose(out);
}