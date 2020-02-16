#ifndef _AUTOSOLVE_C_
#define _AUTOSOLVE_C_
#include <stdio.h>
#include <stdlib.h>

#include "autosolve.h"

#endif

float cost_f(node* child);

float cost_f(node* child){
    state** board = child->board;
    float cost = 0;
    for(int i=0; i<7;i++){
        for(int j=0; j<7;j++){
            if(board[i][j]==ball){
                for(int k=i;k<7;k++){
                    for(int q=j; q<7; q++){
                        if (board[k][q]==ball) {
                            cost = cost + (k-i)*(k-i) + (q-j)*(q-j);
                        }
                    }
                } 
            }
        }
    }
    return cost;
}

int main(){

}