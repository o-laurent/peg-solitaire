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

trajectoryNode* autosolve(trajectoryNode* pTrajectory, int* boardNb, int* stop) {
    
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
        return rmtTN(pTrajectory);
    }
    else {
        //printf("ELSE\n");
        movement* pmove = malloc(sizeof(movement));
        //printf("BEFOREFOR");
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
                            //printf("%d\n", pTrajectory->cNode->childNb);
                        }
                    }
                }
            }
        }
        free(pmove);
        node* tmpPointer = pTrajectory->cNode->child;
        pTrajectory->cNode->child = pTrajectory->cNode->child->next;
        free(tmpPointer);
        sortNodes(&(pTrajectory->cNode->child));
        //ERREUR ICI : On récupère toujours le premier fils
        node* child1 = pTrajectory->cNode->child;
        pTrajectory = autosolve(consTN(child1, pTrajectory), boardNb, stop);
        ////printf("1");
        while ((!(*stop))&&(pTrajectory->cNode->child->next!=NULL)) { //If a solution hasn't been found yet, try the other movements.
            //printf("2");
            node* child2 = pTrajectory->cNode->child->next; //A CHANGER DOIT ETRE LE SUIVANT AVEC UNE VALEUR DIFFERENTE POUR GARANTIR UN MOUV DIFFERENT
            /*printf("CHILD2\n");
            printBoardV(child2->board, 7, 7);*/
            pTrajectory->cNode->child = child2;
            pTrajectory = autosolve(consTN(child2, pTrajectory), boardNb, stop);
            //printf("3");
        }
    
        return rmtTN(pTrajectory);
    }

}