#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "save.h"

void saveGame (state** board, int turn, time_t time) {
    FILE *out;
    out = fopen ("save.txt", "wb");
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

//we have to initialise an empty board before calling the function
//the function will change the value of this board
long int* loadGame (state** board) {
    FILE *in;
    int x;
    int turn;
    long int time;
    in = fopen ("save.txt", "rb");
    if (in == NULL) {
        printf("Le chargement de la partie précédente a échoué...\n");
    }
    long int* returned = malloc(sizeof(long long int)*2);

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
            }
        }
    }
    fscanf (in, "%d",&turn);
    fscanf (in, "%ld",&time);

    returned[0] = turn;
    returned[1] = time;

    fclose(in);

    return returned;
}

int main () {
    //define board
    state **board = malloc(sizeof(*board) * 7);
    for (int i=0;i<7;i++) {
        board[i] = malloc(sizeof(**board)*7);
    }

    //initialise board
    for (int i=0; i<7; i++) {
            for (int j=0; j<7; j++) {
                if ((i%6==0 && j%6==0) || (i%6==0 && j==1) || (i==1 && j%6==0) || (i%6==0 && j==5) || (i==5 && j%6==0)) {
                    board[i][j] = out;
                }
                else if (i==j && i==3) {
                    board[i][j] = empty; 
                }
                else {
                    board[i][j] = ball;
                }
            }
        }

    //save game
    saveGame(board, 3, 5000);

    //define new board
    state **newBoard = malloc(sizeof(*newBoard) * 7);
    for (int i=0;i<7;i++) {
        newBoard[i] = malloc(sizeof(**newBoard)*7);
    }

    //initialise new board
    for (int i=0; i<7; i++) {
            for (int j=0; j<7; j++) {
                newBoard[i][j]=out;
            }
        }

    //load game
    long int* returned = loadGame(newBoard);
    int turn = returned[0];
    long int time = returned[1];

    //print new board
    printf("\n");
    for (int i=0 ; i<8 ; i++) {
        if (i==0 || i==7) {
            printf("  ");
            printf("\033[0;31m"); //Red
            for (int j=0 ; j<7 ; j++) {
                printf("%d ", j);
            }
            printf("\033[0m");
            printf("\n");
        }
        for (int j=0 ; j<8 ; j++) {
            if ((j==0 || j==7) && i!=7) {
                printf("\033[0;34m"); //Blue
                printf("%d ", i);
                printf("\033[0m");
            }
            if (i<7 && j<7 && newBoard[i][j]==ball) {
                printf("\033[1m");
                printf("o ");
                printf("\033[0m");
            }
            else if (i<7 && j<7 && newBoard[i][j]==empty) {
                printf("\033[37;2m"); //Grey 
                printf("X ");
                printf("\033[0m");
            }
            else {
                printf("  ");
            }
        }
        printf("\n");
    }
    printf("\n");

    printf("%d \n",turn);
    printf("%ld \n",time);


    return 0;
}