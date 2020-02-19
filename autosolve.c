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

/*stop = 0;
trajectory* autosolve(trajectory* pTrajectory) {
    if (stop) {
        return pTrajectory;
    }
    else {
        movement move;
        for (int i=0 ; i<7 ; i++) {
            for (int j=0 ; j<7 ; j++) {
                if (pTrajectory->node->board[i][j]==ball) {
                    move.posix = i;
                    move.posiy = j;
                    for (k=0 ; k<4 ; k++) {
                        move.dir = k;
                        node* nodeV = copy(pTrajectory->node->child);
                        if (correctMove(pTrajectory->board, &move)) {
                            doMove(move, nodeV->board);
                            nodeV->cost = cost_f(nodeV->board);
                            pTrajectory->node->childNb++;
                        }
                    }
                }
            }
        }
        sortNodes(pTrajectory->node->child);
        child1 = pTrajectory->node->child;
        pTrajectory = consT(pTrajectory, child1);
        autosolve(pTrajectory);
        child2 = pTrajectory->node->child->next;
        pTrajectory = consT(pTrajectory, child2);
        autosolve(pTrajectory);
        //Il faut que les 2 trajectoires soient différentes : peut-être un problème de mémoire ici 
    }
}*/