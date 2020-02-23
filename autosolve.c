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
    state** newBoard = malloc(sizeof(*newBoard) * 7);
    for (int i=0;i<7;i++) {
        newBoard[i] = malloc(sizeof(**newBoard)*7);
    }
    copyBoard(sibling->board, newBoard); //Makes the boards independent
    /*printBoardV(sibling->board, 7, 7);
    printBoardV(newBoard,7 , 7);*/
    nodeOut->board = newBoard;
    nodeOut->child = NULL;
    nodeOut->childNb = 0;
    nodeOut->cost = -1;
    nodeOut->lineage = NULL;
    if (sibling->child!=NULL){
        nodeOut->next = sibling->child->next;
    }
    else {
        nodeOut->next = sibling->child;
    }
    nodeOut->parent = sibling;
    return nodeOut;
}

trajectoryNode* autosolve(trajectoryNode* pTrajectory, int* boardNb) {
    int stop = 0;
    if (ballNb(pTrajectory->cNode->board)==1) {
            stop++;
            return pTrajectory;
    }
    if (stop) {
        //If a solution has been found, keep the trajectory
        return pTrajectory;
    }
    else if (moveNb(pTrajectory->cNode->board)==0) {
        pTrajectory->cNode = pTrajectory->cNode->parent;
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
                        /*printf("(i,j) : (%d,%d)\n",i,j);
                        printf("board(i,j) : %d\n", pTrajectory->cNode->board[i][j]);
                        printf("copyboard(i,j) : %d\n", nodeV->board[i][j]);*/
                        if (correctMove(pTrajectory->cNode->board, pmove)) {
                            node* tmpNode = copyNode(pTrajectory->cNode); //tmpNode
                            //printf("tmpNode next child: %p", tmpNode->next);
                            doMove(tmpNode->board, pmove);
                            tmpNode->cost = cost_f(tmpNode->board);
                            pTrajectory->cNode->child = tmpNode;
                            //printf("next child: %p", pTrajectory->cNode->child->next);
                            node* childN = malloc(sizeof(node)); //Adding NextNode
                            childN->next = pTrajectory->cNode->child;
                            //printf("next child: %p", childN->next);
                            //printf("next child: %p", childN->next->next);
                            childN->cost = -1;
                            //printf("Previous Child board: %p", pTrajectory->cNode->child->board);
                            pTrajectory->cNode->child = childN;
                            //printf(" Next Child board: %p\n", pTrajectory->cNode->child->board);
                            //printf("Next Child previous board: %p\n", pTrajectory->cNode->child->next->board);
                            pTrajectory->cNode->childNb++;
                            (*boardNb)++;
                        }
                    }
                    //DELETE FIRST
                }
            }
        }
        node* tmpPointer = pTrajectory->cNode->child;
        pTrajectory->cNode->child = pTrajectory->cNode->child->next;
        free(tmpPointer);
        printf("AFTERFOR\n");
        /*sortNodes(&(pTrajectory->cNode->child));
        node* child1 = pTrajectory->cNode->child;
        pTrajectory = consTN(child1, pTrajectory);
        autosolve(pTrajectory, boardNb);
        if (!stop) { //If a solution hasn't been found yet, try the other movement.
            node* child2 = pTrajectory->cNode->child->next; //A CHANGER DOIT ETRE LE SUIVANT AVEC UNE VALEUR DIFFERENTE POUR GARANTIR UN MOUV DIFFERENT
            pTrajectory = consTN(child2, pTrajectory); 
            autosolve(pTrajectory, boardNb);
        }*/
        sortNodes(&(pTrajectory->cNode->child));
        node* child1 = pTrajectory->cNode->child;
        pTrajectory = consTN(child1, pTrajectory);
        autosolve(pTrajectory, boardNb);
        /*do {
            printBoardV(pTrajectory->cNode->child->board, 7, 7);
            pTrajectory->cNode->child = pTrajectory->cNode->child->next;
        }
        while (pTrajectory->cNode->child!=NULL);*/
        

    }
    return pTrajectory;
}