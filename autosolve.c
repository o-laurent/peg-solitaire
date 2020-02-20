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

node* copyNode(node* sibling) {
    -1;
}

trajectoryNode* autosolve(trajectoryNode* pTrajectory) {
    int stop = 0;
    if (stop) {
        return pTrajectory;
    }
    else {
        movement* pmove = malloc(sizeof(movement));
        for (int i=0; i<7; i++) {
            for (int j=0; j<7; j++) {
                if (pTrajectory->cNode->board[i][j]==ball) {
                    pmove->posix = i;
                    pmove->posiy = j;
                    for (int k=0; k<4; k++) {
                        pmove->dir = k;
                        node* nodeV = copyNode(pTrajectory->cNode->child);
                        if (correctMove(pTrajectory->cNode->board, pmove)) {
                            doMove(nodeV->board, pmove);
                            nodeV->cost = cost_f(nodeV->board);
                            pTrajectory->cNode->childNb++;
                        }
                    }
                }
            }
        }
        sortNodes(pTrajectory->cNode->lineage);
        node* child1 = pTrajectory->cNode->child;
        pTrajectory = consTN(child1, pTrajectory);
        autosolve(pTrajectory);
        node* child2 = pTrajectory->cNode->child->next;
        pTrajectory = consTN(child2, pTrajectory);
        autosolve(pTrajectory);
        //Il faut que les 2 trajectoires soient différentes : peut-être un problème de mémoire ici 
    }
    return pTrajectory;
}