#ifndef AUTOSOLVE_C_
#define AUTOSOLVE_C_
#include <stdio.h>
#include <stdlib.h>
#include "autosolve.h"
#endif

int cost_f(state** board, char lineNb, char colNb){
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
    //remove same nodes 
    int number = 0;
    node* cNode = *pNode;
    
    if (cNode->next != NULL) {
        node* tmpNode = cNode->next;
        node* tmpNode2 = tmpNode;
        int cCost = cNode->cost;
        while (cNode->next != NULL) {
            while (tmpNode->next != NULL && tmpNode->cost==cCost) {
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
            //printf("tmpNode pointer : %p\n", cNode);
            tmpNode2 = tmpNode;
            if (tmpNode!=NULL){
                cCost = tmpNode->cost;
                //printf("if pointer = %p\n", cNode);
            }
        }
        //printBoardV(cNode->board, lineNb, colNb);
    }
    //printf("FIN");
}

void freePartTrajectoryN(trajectoryNode* pTrajectory, int* nodeFree, int* boardFree, int threshold, char lineNb, char colNb) {
    node* tmpNode = pTrajectory->cNode->child;
    node* tmpNode2 = tmpNode;
    //printf("root %p ", tmpNode);
    if (tmpNode->next!=NULL) {
        //printf("root next %p\n", tmpNode->next);
        int count = 0;
        int counter = 0;
        //Go as far as permitted
        while (count<threshold && tmpNode->next!=NULL) {
            //printf("node %d pointer %p ", count, tmpNode);
            //printf("node %d next pointer %p\n", count, tmpNode->next);
            tmpNode2 = tmpNode;
            tmpNode = tmpNode->next;
            count++;
        } 
        //printf("Taille 1 : %d ", count);
        //separate and clean the second part
        if (tmpNode!=NULL){
            //Check that we leave the while because of "count<threshold"
            tmpNode = tmpNode2;
            tmpNode2 = tmpNode->next;
            tmpNode->next = NULL;
            //Deletion starting with tmpNode2
            tmpNode = tmpNode2;
            //printf("tmpNode2 : %p ", tmpNode2);
            if (tmpNode->next==NULL) {
                counter++;
                //Only one more node
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
                //more than one node
                tmpNode2 = tmpNode->next;
                while (tmpNode!=NULL) {
                    counter++;
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
                }
            }
        }
        else {
            //printf("ZERO");
        }
        int totalSize = counter+count;
        //printf("removed : %d \n", counter);
        if (totalSize!= pTrajectory->cNode->childNb) {
            //printf("erreur : %d/%d \n", totalSize, pTrajectory->cNode->childNb);
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

trajectoryNode* autosolve(trajectoryNode* pTrajectory, int* boardNb, int* stop, int beamWidth, int* nodeAlloc, int* nodeFree, int* boardAlloc, int* boardFree, int* trajectoryAlloc, int* trajectoryFree, char lineNb, char colNb) {
    //printf("%d %d", lineNb, colNb);
    //printf("\n %d %d\n", moveNb(pTrajectory->cNode->board, lineNb, colNb), ballNb(pTrajectory->cNode->board, lineNb, colNb));
    if (*stop!=0 || ballNb(pTrajectory->cNode->board, lineNb, colNb)<=1) {
        //exit(1);
        //printf("stop : %d, ballNb %d\n")
        //printf("VICTOIRE\n");
        (*stop)++;
        return pTrajectory;
    }

    else if (moveNb(pTrajectory->cNode->board, lineNb, colNb)==0) {
        //printf("%d %d", lineNb, colNb);printBoardV(pTrajectory->cNode->board, lineNb, colNb);
        //free this node only : We are on a leaf
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
        //printf("Child nb = %d ", pTrajectory->cNode->childNb);
        freePartTrajectoryN(pTrajectory, nodeFree, boardFree, beamWidth, lineNb, colNb);

        int preCost = -1; //-1 is impossible to get beacause cost_f(.)>=0
        node* cChild = pTrajectory->cNode->child;
        int i = 0;
        do {
            pTrajectory->cNode->child = cChild;
            //printBoardV(pTrajectory->cNode->child->board, lineNb, colNb);
            if (cChild->cost != preCost) {
                preCost = cChild->cost; //update the cost
                pTrajectory = autosolve(consTN(cChild, pTrajectory, trajectoryAlloc), boardNb, stop, beamWidth, nodeAlloc, nodeFree, boardAlloc, boardFree, trajectoryAlloc, trajectoryFree, lineNb, colNb);
                i++;
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
            return rmtTN(pTrajectory, nodeFree, boardFree, trajectoryFree, lineNb);
        }
    }
}