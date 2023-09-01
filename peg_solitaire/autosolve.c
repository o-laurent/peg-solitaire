/*Recherche dans l'arbre par faisceau*/
#ifndef AUTOSOLVE_C_
#define AUTOSOLVE_C_
#include "autosolve.h"
#include <stdio.h>
#include <stdlib.h>
#endif

int cost_f(state** board, char lineNb, char colNb){
    //L'heuristique de notre arbre : distance au carré entre toutes les billes 
    //On suppose que plus les billes sont proches plus la chance de gagner est élévée... pas sûr
    int cost = 0;
    for(int i=0; i<lineNb;i++){
        for(int j=0; j<colNb;j++){
            if(board[i][j]==ball){
                for(int k=i;k<lineNb;k++){
                    for(int q=j; q<colNb; q++){
                        if (board[k][q]==ball) {
                            cost += (k-i)*(k-i)+(q-j)*(q-j); //distance au carré 
                        }
                    }
                } 
            }
        }
    }
    return cost;
}

/*
Second possibility : seems maybe a little better, but not always positive...
int cost_f(state** board, char lineNb, char colNb){
    printBoardV(board, lineNb, colNb);
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
    return somme1 - somme2*somme2 - somme3*somme3;
}*/

void rmSNodes(node** pNode, int beamWidth, int* nodeFree, int* boardFree, char lineNb, char colNb) {
    //remove same following nodes 
    //This function doesn't do what it is supposed to do, but it helps freeing the memory, so we have kept it...
    int number = 0;
    node* cNode = *pNode;
    if (cNode->next != NULL) {
        node* tmpNode = cNode->next;
        node* tmpNode2 = tmpNode;
        int cCost = cNode->cost;
        while (cNode->next != NULL) {
            while (tmpNode->next != NULL && tmpNode->cost==cCost) {
                //same cost : probably the same movement (including symetries)
                tmpNode = tmpNode->next;
                for (int i=0; i<lineNb; i++) {
                        free(tmpNode2->board[i]);
                    }
                free(tmpNode2->board);
                (*boardFree)++;
                tmpNode2->board = NULL;
                free(tmpNode2);
                (*nodeFree)++;
                tmpNode2 = tmpNode;
            }
            number++;
            cNode->next = tmpNode;
            cNode = cNode->next;
            tmpNode = cNode->next;
            tmpNode2 = tmpNode;
            if (tmpNode!=NULL){
                cCost = tmpNode->cost;
            }
        }
        
    }
}

void freePartTrajectoryN(trajectoryNode* pTrajectory, int* nodeFree, int* boardFree, int threshold, char lineNb, char colNb) {
    //At each node we generate all the children. This functions deletes the ones that are note the "threshold"-best
    node* tmpNode = pTrajectory->cNode->child;
    node* tmpNode2 = tmpNode;
    if (tmpNode->next!=NULL) {
        int count = 1;
        int counter = 0;
        //Go as far as permitted
        while (count<threshold && tmpNode->next!=NULL) {
            tmpNode2 = tmpNode;
            tmpNode = tmpNode->next;
            //printf("pointer : %p ", tmpNode);
            count++;
        } 
        //printf("node->next : %p \n", tmpNode->next);
        //separate and clean the second part
        if (tmpNode->next!=NULL){
            //Check that we leave the while because of "count<threshold"
            tmpNode2 = tmpNode->next;
            tmpNode->next = NULL;
            //Deletion starting with tmpNode2
            tmpNode = tmpNode2;
            //printf("tmpNode2 : %p \n", tmpNode2);
            if (tmpNode->next==NULL) {
                //printf("ONNE");
                //Only one more node
                for (int i=0; i<lineNb; i++) {
                    free(tmpNode->board[i]);
                }
                free(tmpNode->board);
                (*boardFree)++;
                tmpNode->board = NULL;
                free(tmpNode);
                (*nodeFree)++;
                counter++;
            }
            else {
                //more than one node
                tmpNode2 = tmpNode->next;
                while (tmpNode!=NULL) {
                    for (int i=0; i<lineNb; i++) {
                        free(tmpNode->board[i]);
                    }
                    free(tmpNode->board);
                    (*boardFree)++;
                    tmpNode->board = NULL;
                    free(tmpNode);
                    (*nodeFree)++;
                    tmpNode = tmpNode2;
                    if (tmpNode!=NULL){
                        tmpNode2 = tmpNode->next;
                    }
                    counter++;
                }
            }
        }
       // printf("count : %d counter : %d\n", count, counter);
    }
}

node* copyNode(node* sibling, char lineNb, char colNb) {
    //Builds a node which is like sibling except for the children
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
    nodeOut->board = newBoard;
    nodeOut->child = NULL;
    nodeOut->childNb = 0;
    nodeOut->cost = -1;
    nodeOut->next = sibling->child;
    nodeOut->parent = sibling;
    return nodeOut;
}

trajectoryNode* autosolve(trajectoryNode* pTrajectory, int* boardNb, int* stop, int beamWidth, int* nodeAlloc, int* nodeFree, int* boardAlloc, int* boardFree, int* trajectoryAlloc, int* trajectoryFree, char lineNb, char colNb) {
    //Main function
    //printBoardV(pTrajectory->cNode->board, lineNb, colNb);
    if (*stop!=0 || ballNb(pTrajectory->cNode->board, lineNb, colNb)<=1) {
        (*stop)++;
        return pTrajectory;
    }

    else if (moveNb(pTrajectory->cNode->board, lineNb, colNb)==0) {
       return rmtTN(pTrajectory, nodeFree, boardFree, trajectoryFree, lineNb);
    }
    else {
        //allocating the movement
        movement* pmove = malloc(sizeof(movement));
        pTrajectory->cNode->child = NULL;
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
        //Removing the same nodes
        rmSNodes(&(pTrajectory->cNode->child), beamWidth, nodeFree, boardFree, lineNb, colNb);
        //Removing the unnecessary children
        freePartTrajectoryN(pTrajectory, nodeFree, boardFree, beamWidth, lineNb, colNb);

        int preCost = -1; //-1 is impossible to get beacause cost_f(.)>=0
        node* cChild = pTrajectory->cNode->child;
        int i = 0;
        do {
            pTrajectory->cNode->child = cChild;
            if (cChild->cost != preCost) {
                preCost = cChild->cost; //update the cost
                pTrajectory = autosolve(consTN(cChild, pTrajectory, trajectoryAlloc), boardNb, stop, beamWidth, nodeAlloc, nodeFree, boardAlloc, boardFree, trajectoryAlloc, trajectoryFree, lineNb, colNb);
            }

            if (!(*stop)) {
                //If it is not finished, go to the next node
                cChild = pTrajectory->cNode->child;
                cChild = cChild->next;
            }
            i++;
        }
        //If a solution hasn't been found yet, try the other movements.
        while (!(*stop) && cChild!=NULL && i<beamWidth); 

        if (*stop) {
            return pTrajectory;
        }
        else {
            return rmtTN(pTrajectory, nodeFree, boardFree, trajectoryFree, lineNb);
        }
    }
}