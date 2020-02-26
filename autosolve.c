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
    if (*stop!=0 || ballNb(pTrajectory->cNode->board)<=1) {
        //printf("stop : %d, ballNb %d\n")
        printf("VICTOIRE\n");
        (*stop)++;
        return pTrajectory;
    }

    else if (moveNb(pTrajectory->cNode->board)==0) {
        //free this node only : We are on a leaf
        return rmtTN_Node(pTrajectory, nodeFree, boardFree);
    }
    else {
        //allocating the movement
        movement* pmove = malloc(sizeof(movement));
        if (pmove==NULL) {
            printf("Erreur 1 : plus de place disponible en RAM\n");
            exit(1);
        } 
        //Finding all the possible boards that become the children of the current node
        for (int i=0; i<7; i++) {
            for (int j=0; j<7; j++) {
                if (pTrajectory->cNode->board[i][j]==ball) {
                    pmove->posix = i;
                    pmove->posiy = j;
                    for (int k=0; k<4; k++) {
                        pmove->dir = k;
                        if (correctMove(pTrajectory->cNode->board, pmove)) {
                    /*The tmpNode is the exact copy of its parent Yet, it has no child, 
                    its next is the previous child, and the parent is the parent...*/
                            node* tmpNode = copyNode(pTrajectory->cNode); 
                            (*nodeAlloc)++;
                            (*boardAlloc)++;
                            //Makes the move and modify the child's board
                            doMove(tmpNode->board, pmove);
                            tmpNode->cost = cost_f(tmpNode->board);
                            //Save it as the previous child
                            pTrajectory->cNode->child = tmpNode;
                            pTrajectory->cNode->childNb++;
                            (*boardNb)++; //Remembering the number of boards tested
                        }
                    }
                }
            }
        }
        
        //Freeing the movement
        free(pmove);
        
        //Sorting the node by increasing costs
        sortNodes(&(pTrajectory->cNode->child));
        int preCost = -1; //Impossible to get : always different
        node* cChild = pTrajectory->cNode->child;

        do {
            pTrajectory->cNode->child = cChild;

            if (cChild->cost != preCost) {
                preCost = cChild->cost;
                pTrajectory = autosolve(consTN(cChild, pTrajectory), boardNb, stop, nodeAlloc, nodeFree, boardAlloc, boardFree);
            }

            if (!(*stop)) {
                cChild = pTrajectory->cNode->child;
                cChild = cChild->next;
            }
        }
        while (!(*stop) && cChild!=NULL); //If a solution hasn't been found yet, try the other movements.
        if (*stop) {
            return pTrajectory;
        }
        else {
            return rmtTN(pTrajectory, nodeFree, boardFree);
        }
        
    }
}