#ifndef AUTOSOLVE_C_
#define AUTOSOLVE_C_
#include <stdio.h>
#include <stdlib.h>
#include "autosolve.h"
#endif

float cost_f(state** board){
    float cost = 0;
    for(int i=0; i<7;i++){
        for(int j=0; j<7;j++){
            if(board[i][j]==ball){
                for(int k=i;k<7;k++){
                    for(int q=j; q<7; q++){
                        if (board[k][q]==ball) {
                            cost = cost+(k-i)*(k-i)+(q-j)*(q-j);
                        }
                    }
                } 
            }
        }
    }
    return cost;
}

/*tant que non stop 
    on regarde si il y a des mouvements possibles 
        On construit la lignée 
            On trie la lignée 
                On choisit les deux meilleurs et on supprime les autres 
                    si stop != 0 on arrête
                    sinon on réitère le raisonnement 
*/