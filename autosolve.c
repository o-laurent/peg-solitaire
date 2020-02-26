#ifndef AUTOSOLVE_C_
#define AUTOSOLVE_C_
#include <stdio.h>
#include <stdlib.h>
#include "autosolve.h"
#endif

int cost_f(state** board){
    float cost = 0;
    for(int i=0; i<7;i++){
        for(int j=0; j<7;j++){
            if(board[i][j]==ball){
                for(int k=i;k<7;k++){
                    for(int q=j; q<7; q++){
                        if (board[k][q]==ball) {
                            cost = cost+(k-i)*(k-i)+(q-j)*(q-j); //distance au carré
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
    if (newBoard==NULL) {
        printf("Erreur 1 : plus de place disponible en RAM\n");
        exit(1);
    } 
    for (int i=0;i<7;i++) {
        newBoard[i] = malloc(sizeof(**newBoard)*7);
        if (newBoard[i]==NULL) {
            printf("Erreur 1 : plus de place disponible en RAM\n");
            exit(1);
        } 
    }
    copyBoard(sibling->board, newBoard); //Makes the boards independent
    /*printBoardV(sibling->board, 7, 7);
    printBoardV(newBoard,7 , 7);*/
    nodeOut->board = newBoard;
    nodeOut->child = NULL;
    nodeOut->childNb = 0;
    nodeOut->cost = -1;
    nodeOut->next = sibling->child;
    nodeOut->parent = sibling;
    return nodeOut;
}

trajectoryNode* autosolve(trajectoryNode* pTrajectory, int* boardNb, int* stop, int* nodeAlloc, int* nodeFree, int* boardAlloc, int* boardFree) {
    //printBoardV(pTrajectory->cNode->board,7,7);
    //printf("2");
    if (*stop!=0 || ballNb(pTrajectory->cNode->board)<=1) {
        //printf("stop : %d, ballNb %d\n")
        printf("VICTOIRE\n");
        (*stop)++;
        return pTrajectory;
    }
    /*if (*stop) {
        //If a solution has been found, keep the trajectory
        //printf("SOLUTION FOUND");
        return pTrajectory;
    }*/
    else if (moveNb(pTrajectory->cNode->board)==0) {
        /*printf("ECHEC\n");
        printBoardV(pTrajectory->cNode->board,7,7);
        printBoardV(pTrajectory->previous->cNode->board,7,7);
        printBoardV(pTrajectory->previous->previous->cNode->board,7,7);
        printBoardV(pTrajectory->previous->previous->previous->cNode->board,7,7);*/
        /*printf("Pointeur vers ptrajectory->cNode %p \n", pTrajectory->cNode);
        printf("Pointeur vers ptrajectory->cNode->child %p \n", pTrajectory->cNode->child);*/
        /*while (pTrajectory->cNode->child!=NULL) {
            printf("Pointeur vers ptrajectory->cNode %p \n", pTrajectory->cNode);
            pTrajectory->cNode = pTrajectory->cNode->child;
        }*/
        /*if (pTrajectory->cNode!=NULL){
            if (pTrajectory->cNode->child!=NULL) {
                free(pTrajectory->cNode->child);
            }
            free(pTrajectory->cNode);
        }*/
        //pTrajectory = rmtTN(pTrajectory);
        //printf("AFTER\n");
        //printf("Pointeur vers ptrajectory->cNode->child %p \n", pTrajectory->cNode->child);
        //printf("SUPPRESSION\n");
        //pTrajectory->cNode = pTrajectory->cNode->parent;
        //*stop = 1;
        return rmtTN(pTrajectory, nodeFree, boardFree);
    }
    else {
        //printf("ELSE\n");
        movement* pmove = malloc(sizeof(movement));
        if (pmove==NULL) {
            printf("Erreur 1 : plus de place disponible en RAM\n");
            exit(1);
        } 
        //printf("BEFOREFOR");
        for (int i=0; i<7; i++) {
            for (int j=0; j<7; j++) {
                if (pTrajectory->cNode->board[i][j]==ball) {
                    pmove->posix = i;
                    pmove->posiy = j;
                    for (int k=0; k<4; k++) {
                        pmove->dir = k;

                        if (correctMove(pTrajectory->cNode->board, pmove)) {
                            node* tmpNode = copyNode(pTrajectory->cNode); //tmpNode
                            (*nodeAlloc)++;
                            (*boardAlloc)++;
                            doMove(tmpNode->board, pmove);
                            tmpNode->cost = cost_f(tmpNode->board);
                            pTrajectory->cNode->child = tmpNode;

                            pTrajectory->cNode->childNb++;
                            (*boardNb)++;

                        }
                    }
                }
            }
        }
        free(pmove);
        sortNodes(&(pTrajectory->cNode->child));
        //ERREUR ICI : On récupère toujours le premier fils
        
        node* child1 = pTrajectory->cNode->child;
        int preCost = child1->cost;
        pTrajectory = autosolve(consTN(child1, pTrajectory), boardNb, stop, nodeAlloc, nodeFree, boardAlloc, boardFree);
        ////printf("1");
        while ((!(*stop))&&(pTrajectory->cNode->child->next!=NULL)) { //If a solution hasn't been found yet, try the other movements.
            //printf("2")
            node* child2 = pTrajectory->cNode->child->next; //A CHANGER DOIT ETRE LE SUIVANT AVEC UNE VALEUR DIFFERENTE POUR GARANTIR UN MOUV DIFFERENT
            /*printf("CHILD2\n");
            printBoardV(child2->board, 7, 7);*/
            pTrajectory->cNode->child = child2;
            if (child2->cost != preCost) {
                preCost = child2->cost;
                pTrajectory = autosolve(consTN(child2, pTrajectory), boardNb, stop, nodeAlloc, nodeFree, boardAlloc, boardFree);
            }
            //printf("3");
        }
        if (*stop) {
            return pTrajectory;
        }
        else {
            return rmtTN(pTrajectory, nodeFree, boardFree);
        }
    }

}