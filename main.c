#include <stdio.h>
#include <stdlib.h>

#include "structures.h"
#include "main.h"



void initBoard(state board[7][7]) {
    //Initialise the board to an English solitaire
    for (int i=0; i<7; i++) {
        for (int j=0; j<7; j++) {
            if ( (i%6==0 && j%6==0) || (i%6==0 && j==1) || (i==1 && j%6==0) || (i%6==0 && j==5) || (i==5 && j%6==0) ) {
                board[i][j] = out;
            }
            else if ( i==j && i==3 ) {
                board[i][j] = empty;
            }
            else {
                board[i][j] = ball;
            }
        }
    }
}

int ballNb(state board[7][7]) {
    //Counts the number of balls on the board
    int count =0;
    for (int i=0; i<7; i++) {
        for (int j=0 ; j<7 ; j++) {
            if (board[i][j]==ball) {
                count++;
            }
        }
    }
    return count;
}

int correctMove(state board[7][7], movement* move) {
    int ok;
    //Check if the position is ball and if the next positions are empty
    int x = move->posix;
    int y = move->posiy;
    direction dir = move->dir;
    if (board[x][y]==ball){
        if ((dir==north) && (board[y+1][x]==ball) && (board[y+2][x]==empty)){
            ok = 1;
        }
        else if ((dir==south) && (board[y-1][x]==ball) && (board[y-2][x]==empty)){
            ok = 1;
        }
        else if ((dir==east) && (board[y][x+1]==ball) && (board[y][x+2]==empty)){
            ok = 1;
        }
        else if ((dir==west) && (board[y][x-1]==ball) && (board[y][x-2]==empty)){
            ok = 1;
        }
        else {
            ok = 0;
        }
    }
    else {
        ok = 0;
        printf("NOT A BALL");
    }
    return ok;
}

int possibleMove(state board[7][7]) {
    //Returns 1 if one move can still be done
    int doable;
    if (ballNb(board) >= 2){
        //If there is only one ball, one can not play anymore
        doable = 1;
        //NOT FINISHED
    }
    else {
        doable = 0;
    }
    return doable;
}   

void doMove(state board[7][7], movement* move) {
    //Makes the move
    //You must check that the move is correct before calling this function !
    int x = move->posix;
    int y = move->posiy;
    if (move->dir==north) {
        board[x][y] = empty;
        board[x][y+1] = empty;
        board[x][y+2] = ball;
    }
    else if (move->dir==south) {
        board[x][y] = empty;
        board[x][y-1] = empty;
        board[x][y-2] = ball;
    }
    else if (move->dir==east) {
        board[x][y] = empty;
        board[x+1][y] = empty;
        board[x+2][y] = ball;
    }
    else if (move->dir==west) {
        board[x][y] = empty;
        board[x-1][y] = empty;
        board[x-2][y] = ball;
    }
    else {
        printf("UNEXPECTED ERROR");
    }
}

void userMove(state board[7][7]) {
    //Allows the user to chose the movement he desires
    char dir;
    movement move;
    int status = 0; //Will be true if a correct movement is recorded
    while (!status) {
        printf("Entrez la coordonnée verticale de la balle à déplacer\n");
        scanf("%hhd", &(move.posiy));

        printf("Entrez la coordonnée horizontale de la balle à déplacer\n");
        scanf("%hhd", &(move.posix));

        int ok = 0;
        while(!ok) {
            printf("Entrez la direction du mouvement (n,s,e,o) : \n");
            scanf("%c", &dir);
            if (dir=='n') {
                ok++;
                move.dir = north;
            }
            else if (dir=='s') {
                ok++;
                move.dir = south;
            }
            else if (dir=='e') {
                ok++;
                move.dir = east;
            }
            else if (dir=='o') {
                ok++;
                move.dir = west;
            }
            else {
                ok =0;
                printf("Erreur lors de l'entrée \n");
            }
        }
        status = correctMove(board, &move);
        if (status==0){
            printf("Ce mouvement n'est pas possible. Veuillez en proposer un autre :\n");
        } 
    }
    doMove(board, &move);
    
}

void printBoard(state board[7][7]) {
    printf("\n");
    for (int i=0 ; i<7 ; i++) {
        for (int j=0 ; j<7 ; j++) {
            if (board[j][i]==ball) {
                printf("O ");
            }
            else if (board[j][i]==empty) {
                printf("X ");
            }
            else {
                printf("  ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

void userGame() {
    //Define 7x7 board and a counter
    state board[7][7];
    int turn = 0;

    //Initialise the board
    initBoard(board);

    while (possibleMove(board)){
        printf("----------   Début du tour %d ----------\n", turn);
        //Print the board
        printBoard(board);
        userMove(board);
    }
}

int main(){ 
    unsigned char status;

    //intro
    printf("Bienvenue dans le Solitaire v0.1\n");
    printf("\n");

    //mode choice
    printf("Appuyez sur '1' pour jouer ou '2' pour une résolution automatique :\n");
    scanf("%hhd", &status);

    //checking for input errors
    while (status!=1 && status!=2) {
        printf("Erreur lors de l'entrée. Veuillez réessayer;\n");
        printf("Appuyez sur '1' pour jouer ou '2' pour une résolution automatique :\n");
        scanf("%hhd", &status);
    }

    //actual game
    userGame();

    //bye bye
    printf("\n");
    printf("Au revoir ^~^\n");
    return 0;
}