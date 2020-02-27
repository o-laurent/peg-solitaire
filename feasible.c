#include "feasible.h"


int ruleOftheThree(state** board) {
    

    return 1;
}


int** board2Square3(state** board) {
    int x=4;
    int y=4;

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
        for(intj=0;j<3;j++){
            square[i][j]=boardNum[i+2][j+2];
        }
    }
    return(square);

}
/*
int** useEquiv(int square2[2][2]) {
    // tu appliques d'abord les les 2 dernières règles 
    Puis ensuite les premières dans les 6 directions (3verticales, 3 horizontales) avec des if 

}

int** square32Square2(int square3[3][3]) {
    // Juste des sommes (regarde  sur le site)

}

int squareEqual(int square1[2][2], int square2[2][2]) {
    //returns 1 if all coeffs are the same
}
*/