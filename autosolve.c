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
    node* nodeOut = malloc(sizeof(node));
    nodeOut->board = sibling->board;
    nodeOut->child = sibling->child;
    nodeOut->childNb = sibling->childNb;
    nodeOut->cost = sibling->cost;
    nodeOut->lineage = sibling->lineage;
    nodeOut->next = sibling->next;
    nodeOut->parent = sibling->parent;
    return nodeOut;
}

trajectoryNode* autosolve(trajectoryNode* pTrajectory, int* boardNb) {
    int stop = 0;
    if (ballNb(pTrajectory->cNode->board)==1) {
            stop++;
    }
    if (stop) {
        //If a solution has been found, keep the trajectory
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
                            *boardNb++;
                        }
                    }
                }
            }
        }
        /*sortNodes(pTrajectory->cNode->lineage);
        node* child1 = pTrajectory->cNode->child;
        pTrajectory = consTN(child1, pTrajectory);
        autosolve(pTrajectory, boardNb);
        if (!stop) { //If a solution hasn't been found yet, try the other movement.
            node* child2 = pTrajectory->cNode->child->next; //A CHANGER DOIT ETRE LE SUIVANT AVEC UNE VALEUR DIFFERENTE POUR GARANTIR UN MOUV DIFFERENT
            pTrajectory = consTN(child2, pTrajectory); 
            autosolve(pTrajectory, boardNb);
        }*/
    }
    return pTrajectory;
}