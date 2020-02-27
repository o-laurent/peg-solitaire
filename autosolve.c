#ifndef AUTOSOLVE_C_
#define AUTOSOLVE_C_
#include <stdio.h>
#include <stdlib.h>
#include "autosolve.h"
#endif

/*int cost_f(state** board){
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
}*/

int cost_f(state** board, char lineNb, char colNb){
    int somme1 = 0;
    int somme2 = 0;
    int somme3 = 0;
    for(int i=0; i<lineNb; i++){
        for(int j=0; j<colNb; j++){
            if(board[i][j]==ball){
                somme1 += i*i+j*j;
                somme2 += i;
                somme3 += j;
            }
        }
    }
    return somme1 - somme2*somme2 -somme3*somme3;
}

void freePartTrajectoryN(trajectoryNode* pTrajectory, int* nodeFree, int* boardFree, int threshold, char lineNb, char colNb) {
    node* tmpNode = pTrajectory->cNode;
    int count = 0;
    //Go as far as permitted
    while (count < threshold && tmpNode->next!=NULL) {
        tmpNode = tmpNode->next;
        count++;
    } 
    //separate and clean the second part
    node* tmpNode2 = tmpNode->next;
    tmpNode->next = NULL;
    //Deletion starting with tmpNode2
    tmpNode = tmpNode2;
    if (tmpNode->next==NULL) {
         for (int i=0; i<lineNb; i++) {
                free(tmpNode->board[i]);
            }
        free(tmpNode->board);
        (*boardFree)++;
        tmpNode->board = NULL;
        free(tmpNode);
        (*nodeFree)++;
    }
    else {
        tmpNode2 = tmpNode->next;
        while (tmpNode2!=NULL) {
        for (int i=0; i<lineNb; i++) {
                free(pTrajectory->cNode->board[i]);
            }
        free(pTrajectory->cNode->board);
        (*boardFree)++;
        tmpNode->board = NULL;
        free(tmpNode);
        (*nodeFree)++;
        tmpNode = tmpNode2;
        tmpNode2 = tmpNode->next;
    }
    }
    
}

node* copyNode(node* sibling, char lineNb, char colNb) {
    node* nodeOut = malloc(sizeof(node));
    state** newBoard = malloc(sizeof(*newBoard) * lineNb);
    if (newBoard==NULL) {
        printf("Erreur 1 : plus de place disponible en RAM\n");
        exit(1);
    } 
    for (int i=0; i<lineNb; i++) {
        newBoard[i] = malloc(sizeof(**newBoard) * colNb);
        if (newBoard[i]==NULL) {
            printf("Erreur 1 : plus de place disponible en RAM\n");
            exit(1);
        } 
    }
    copyBoard(sibling->board, newBoard, lineNb, colNb); //Makes the boards independent
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

trajectoryNode* autosolve(trajectoryNode* pTrajectory, int* boardNb, int* stop, int beamWidth, int* nodeAlloc, int* nodeFree, int* boardAlloc, int* boardFree, char lineNb, char colNb) {
    printf("%d %d", lineNb, colNb);
    printf("\n %d\n", moveNb(pTrajectory->cNode->board, lineNb, colNb)==0);
    if (*stop!=0 || ballNb(pTrajectory->cNode->board, lineNb, colNb)<=1) {
        //exit(1);
        //printf("stop : %d, ballNb %d\n")
        printf("VICTOIRE\n");
        (*stop)++;
        return pTrajectory;
    }

    else if (moveNb(pTrajectory->cNode->board, lineNb, colNb)==0) {
        printf("ELSEIF");
        //free this node only : We are on a leaf
        return rmtTN(pTrajectory, nodeFree, boardFree, lineNb);
    }
    else {
        printf("ELSE");
        //allocating the movement
        movement* pmove = malloc(sizeof(movement));
        if (pmove==NULL) {
            printf("Erreur 1 : plus de place disponible en RAM\n");
            exit(1);
        } 
        //Finding all the possible boards that become the children of the current node
        for (int i=0; i<lineNb; i++) {
            for (int j=0; j<colNb; j++) {
                if (pTrajectory->cNode->board[i][j]==ball) {
                    pmove->posix = i;
                    pmove->posiy = j;
                    for (int k=0; k<4; k++) {
                        pmove->dir = k;
                        if (correctMove(pTrajectory->cNode->board, pmove, lineNb, colNb)) {
                    /*The tmpNode is the exact copy of its parent Yet, it has no child, 
                    its next is the previous child, and the parent is the parent...*/
                            node* tmpNode = copyNode(pTrajectory->cNode, lineNb, colNb); 
                            (*nodeAlloc)++;
                            (*boardAlloc)++;
                            //Makes the move and modify the child's board
                            doMove(tmpNode->board, pmove);
                            tmpNode->cost = cost_f(tmpNode->board, lineNb, colNb);
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
        //printBoardV(pTrajectory->cNode->child->board, 6, 7);
        //freePartTrajectoryN(pTrajectory, nodeFree, boardFree, beamWidth, lineNb, colNb);

        int preCost = -1; //Impossible to get : always different
        node* cChild = pTrajectory->cNode->child;
        int i = 0;
        do {
            pTrajectory->cNode->child = cChild;
            //printBoardV(pTrajectory->cNode->child->board, 6, 7);
            if (cChild->cost != preCost) {
                preCost = cChild->cost; //update the cost
                pTrajectory = autosolve(consTN(cChild, pTrajectory), boardNb, stop, beamWidth, nodeAlloc, nodeFree, boardAlloc, boardFree, lineNb, colNb);
                i++;
                printf("%d", i);
            }

            if (!(*stop)) {
                //If it is not finished, go to the next node
                cChild = pTrajectory->cNode->child;
                cChild = cChild->next;
            }
        }
        //If a solution hasn't been found yet, try the other movements.
        while (!(*stop) && cChild!=NULL && i<beamWidth); 

        if (*stop) {
            return pTrajectory;
        }
        else {
            return rmtTN(pTrajectory, nodeFree, boardFree, lineNb);
        }
    }
}