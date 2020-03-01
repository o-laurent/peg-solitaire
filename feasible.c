#include "feasible.h"
#include <stdlib.h>
#include <stdio.h>


int ruleOftheThree(state** board) {
    

    return 1;
}


int** board2Square3(state** board) {

    int **boardNum;
    boardNum = malloc(sizeof(*boardNum) * 7);
    for (int i=0;i<7;i++) {
       boardNum[i] = malloc(sizeof(**boardNum)*7);
    }

    for(int i=0;i<7;i++){
        for(int j=0;j<7;j++){
            if (board[i][j]==out) boardNum[i][j]=-100000;
            else if (board[i][j]==empty) boardNum[i][j]=0;
            else if (board[i][j]==ball) boardNum[i][j]=1;
        }
    }

    for(int i=0;i<2;i++){
        for(int j=0;j<7;j++){
            if (boardNum[i][j]!=0 && boardNum[i][j]!=-100000){
                int val=boardNum[i][j];
                if (val>0){
                boardNum[i][j]=0;
                boardNum[i+1][j]=boardNum[i+1][j]-val;
                boardNum[i+2][j]=boardNum[i+2][j]+val;
                }
                if (val<0){
                boardNum[i][j]=0;
                boardNum[i+1][j]=boardNum[i+1][j]-val;
                boardNum[i+2][j]=boardNum[i+2][j]-val;
                }
            }
        }
    }

    for(int i=6;i>4;i--){
        for(int j=0;j<7;j++){
            if (boardNum[i][j]!=0 && boardNum[i][j]!=-100000){
                int val=boardNum[i][j];
                if (val>0){
                boardNum[i][j]=0;
                boardNum[i-1][j]=boardNum[i-1][j]-val;
                boardNum[i-2][j]=boardNum[i-2][j]+val;
                }
                if (val<0){
                boardNum[i][j]=0;
                boardNum[i-1][j]=boardNum[i-1][j]-val;
                boardNum[i-2][j]=boardNum[i-2][j]-val;
                }
            }
        }
    }

    for(int i=2;i<5;i++){
        for(int j=0;j<2;j++){
            if (boardNum[i][j]!=0 && boardNum[i][j]!=-100000){
                int val=boardNum[i][j];
                if (val>0){
                boardNum[i][j]=0;
                boardNum[i][j+1]=boardNum[i][j+1]-val;
                boardNum[i][j+2]=boardNum[i][j+2]+val;
                }
                if (val<0){
                boardNum[i][j]=0;
                boardNum[i][j+1]=boardNum[i][j+1]-val;
                boardNum[i][j+2]=boardNum[i][j+2]-val;
                }
            }
        }
    }

    for(int i=2;i<5;i++){
        for(int j=6;j>4;j--){
            if (boardNum[i][j]!=0 && boardNum[i][j]!=-100000){
                int val=boardNum[i][j];
                if (val>0){
                boardNum[i][j]=0;
                boardNum[i][j-1]=boardNum[i][j-1]-val;
                boardNum[i][j-2]=boardNum[i][j-2]+val;
                }
                if (val<0){
                boardNum[i][j]=0;
                boardNum[i][j-1]=boardNum[i][j-1]-val;
                boardNum[i][j-2]=boardNum[i][j-2]-val;
                }
            }
        }
    }

    int **square=malloc(sizeof(*square) * 3);
    for (int i=0;i<3;i++) {
       square[i] = malloc(sizeof(**square)*3);
    }

    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            square[i][j]=boardNum[i+2][j+2];
        }
    }
    return(square);

}

int** useEquiv(int square2[2][2]) {
    int **square_mod=malloc(sizeof(*square_mod) * 2);
    for (int i=0;i<2;i++) {
       square_mod[i] = malloc(sizeof(**square_mod)*2);
    }
    for (int i=0; i<2; i++) {
        for  (int j=0; j<2; j++) {
            square_mod[i][j]=square_mod[i][j]%2;
        }
    }
    return square_mod;
}

int** square32Square2(int square3[3][3]) {
    int **square=malloc(sizeof(*square) * 2);
    for (int i=0;i<2;i++) {
       square[i] = malloc(sizeof(**square)*2);
    }
    square[0][0]=square3[0][0]+square3[0][2]+square3[1][0]+square3[1][2];
    square[0][1]=square3[0][1]+square3[1][1]+square3[0][2]+square3[1][2];
    square[1][0]=square3[0][0]+square3[1][0]+square3[0][2]+square3[2][2];
    square[1][1]=square3[1][1]+square3[0][2]+square3[0][1]+square3[1][2];

    return square;
}

int squareEqual(int square1[2][2], int square2[2][2]) {
    if (square1[0][0]==square2[0][0] && square1[1][0]==square2[1][0] && square1[0][1]==square2[0][1] &&square1[1][1]==square2[1][1]) {
        return 1;
    }
    else return 0;
}
