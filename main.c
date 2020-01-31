#include <stdio.h>
#include <stdlib.h>
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

int ball_nb(state board[7][7]) {
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

//int check_move
int possible_move(state board[7][7]) {
    //Returns 1 if one move can still be done
    int doable;
    if (ball_nb(board) >= 2){
        //If there is only one ball, one can not play anymore
        doable = 1;
    }
    else {
        doable = 0;
    }
    return doable;
}   

void user_move(state board[7][7]) {
    printf("Entrez les coordonnées du point que vous souhaitez bouger :\n");

    printf("Entrez la direction du mouvement :\n");

    printf("Ce mouvement n'est pas possible. Veuillez en proposer un autre :\n");
}

void printBoard(state board[7][7]) {
    printf("\n");
    for (int i=0 ; i<7 ; i++) {
        for (int j=0 ; j<7 ; j++) {
            if (board[i][j]==ball) {
                printf("O");
            }
            else if (board[i][j]==empty) {
                printf("X");
            }
            else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

void user_game() {
    //Define 7x7 board and a counter
    state board[7][7];
    int turn = 0;

    //Initialise the board
    initBoard(board);

    while (possible_move(board)){
        printf("----------   Début du tour %d ----------\n", turn);
        //Print the board
        printBoard(board);
        //user_move();
    }
}

int main(){ 
    unsigned char status;

    //intro
    printf("WELCOME TO SOLITAIRE VERSION 1.0\n");
    printf("\n");

    //mode choice
    printf("PRESS 1 TO PLAY OR 2 FOR SELF RESOLUTION\n");
    scanf("%hhd", &status);

    //checking for input errors
    while (status!=1 && status!=2) {
        printf("INPUT ERROR !!\n");
        printf("\n");
        printf("PRESS 1 TO PLAY OR 2 FOR SELF RESOLUTION\n");
        scanf("%hhd", &status);
    }

    //actual game
    user_game();

    //bye bye
    printf("\n");
    printf("GOOD BYE ^~^\n");
    return 0;
}