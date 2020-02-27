#ifndef STRUCTURES_C_
#define STRUCTURES_C_
#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#endif

/*void buildLineage(node* currentNode, sorted_children *lineage){
    node *child = currentNode;
    unsigned int children_nb = 0;
    while(child != NULL){
        children_nb ++;
        child = child->next;
    }

    int cost_list[children_nb];
    node *children_array[children_nb];
    int i=0;
    for(i=0; i<children_nb; i++){
        children_array[i] = child;
        cost_list[i] = cost_f(child);
        child = child->brother;
    }

    sortNodes(children_nb, cost_list, children_array);        
}*/

//Utility
void printSizes() {
    printf("----- Affichage des tailles des objets utilisés -----\n");
    printf("Taille de state : %ld\n", sizeof(state));
    printf("Taille de trajectory : %ld\n", sizeof(trajectory));
    printf("Taille de direction : %ld\n", sizeof(direction));
    printf("Taille de movement : %ld\n", sizeof(movement));
    printf("Taille de movementList : %ld\n", sizeof(movementList));
    printf("Taille de node : %ld\n", sizeof(node));
    printf("Taille de trajectoryNode : %ld\n", sizeof(trajectoryNode));
}

//Node functions
void sortNodes(node** phead){
    node* head = *phead;
    if((phead==NULL) || ((*phead)->next==NULL)) {
        return;
    }
    else{
        node* a;
        node* b;
        nodeSplit(head, &a, &b); //divide the linked list into two halves
        sortNodes(&a);
        sortNodes(&b);
        *phead = sortedMerge(a, b);
    }

}

node* sortedMerge(node* a, node* b) {
    node* result = NULL; 
    if (a==NULL) {
        return (b); 
    }
    else if (b==NULL) { 
        return (a); 
    }
    if (a->cost <= b->cost) { 
        result = a; 
        result->next = sortedMerge(a->next, b); 
    } 
    else { 
        result = b; 
        result->next = sortedMerge(a, b->next); 
    } 
    return (result); 
}

//source https://www.geeksforgeeks.org (C'est génial comme idée !)
void nodeSplit(node* source, node** frontRef, node** backRef) {
    node* fast; 
    node* slow; 
    slow = source; 
    fast = source->next; 
    /* Advance 'fast' two nodes, and advance 'slow' one node */
    while (fast != NULL) { 
        fast = fast->next; 
        if (fast != NULL) { 
            slow = slow->next; 
            fast = fast->next; 
        } 
    } 
    /*'slow' is before the midpoint in the list, so split it in two 
    at that point. */
    *frontRef = source; 
    *backRef = slow->next; 
    slow->next = NULL; 
}

movementList* consML (movement* move, movementList* moveList){
    movementList* tmp = malloc(sizeof(movementList)) ;
    if (tmp == NULL) {
        printf("ERREUR");
        return NULL;
    }
    tmp->move = *move;
    tmp->next = moveList;
    return tmp;
}


//Trajectory basic functions
trajectory* consT(state** board, trajectory* pTrajectory) {
    //Add a board on the top of the list
    trajectory* tmp = malloc(sizeof(trajectory));
    if (tmp == NULL) { //Insufficent space
        printf("ERREUR");
        return NULL;
    }
    pTrajectory->next = tmp; //Next Step
    tmp->board = board;
    tmp->previous = pTrajectory; //Previous Step

    return tmp;
}

trajectory* rmtT(trajectory* pTrajectory) {
    //removes the top of the list
    return pTrajectory->previous;
}

void freeT_P(trajectory* pTrajectory) {
    //upper-way-recursive free
    if (pTrajectory->previous!=NULL) {
        freeT_P(pTrajectory->previous);
    }
    free(pTrajectory);
}


//TrajectoryNode basic functions
trajectoryNode* consTN(node* child, trajectoryNode* pTrajectory) {
    //Add a node on the top of the list
    trajectoryNode* tmp = malloc(sizeof(trajectoryNode));
    if (tmp == NULL) { //Insufficent space
        printf("ERREUR");
        return NULL;
    }
    pTrajectory->next = tmp; //Next Step
    tmp->cNode = child;
    tmp->previous = pTrajectory; //Previous Step

    return tmp;
}

void freeNode(node* cNode, int* nodeFree, int* boardFree) {
    if (cNode!=NULL) {
        while (cNode->child != NULL) {
            for (int i=0; i<7; i++) {
                free(cNode->child->board[i]);
            }
            free(cNode->child->board);
            cNode->child->board=NULL;
            (*boardFree)++;

            cNode->child = cNode->child->next;
        }
        free(cNode->child);
        (*nodeFree)++;
    }
}

trajectoryNode* rmtTN(trajectoryNode* pTrajectory, int* nodeFree, int* boardFree) {
    //removes the top of the list and free the children
    trajectoryNode* tmpPointer;
    if (pTrajectory->previous==NULL) {
        //Impossible to do : this should not happend
        printf("ERREUR pas d'antécédent\n");
        tmpPointer = pTrajectory;
    }
    else {
        tmpPointer = pTrajectory->previous;
        if (pTrajectory->cNode!=NULL){
            //freeNode(pTrajectory->cNode, nodeFree, boardFree);
            for (int i=0; i<7; i++) {
                free(pTrajectory->cNode->board[i]);
            }
            free(pTrajectory->cNode->board);
            (*boardFree)++;
            pTrajectory->cNode->board=NULL;
            free(pTrajectory->cNode);
            (*nodeFree)++;
            pTrajectory->cNode=NULL;
        }
        free(pTrajectory);
    }
    return tmpPointer;
}

trajectoryNode* rmtTN_Node(trajectoryNode* pTrajectory, int* nodeFree, int* boardFree) {
    //removes the element when on a leaf
    trajectoryNode* tmpPointer;
    if (pTrajectory->previous==NULL) {
        //Impossible to do : this should not happend
        printf("ERREUR pas d'antécédent\n");
        tmpPointer = pTrajectory;
    }
    else {
        tmpPointer = pTrajectory->previous;
        if (pTrajectory->cNode!=NULL){
            for (int i=0; i<7; i++) {
                free(pTrajectory->cNode->board[i]);
            }
            free(pTrajectory->cNode->board);
            (*boardFree)++;
            //pTrajectory->cNode->board=NULL;
            free(pTrajectory->cNode);
            (*nodeFree)++;
            pTrajectory->cNode=NULL;
        }
        free(pTrajectory);
    }
    return tmpPointer;
}

void freeTN_P(trajectoryNode* pTrajectory) {
    //lower-recursive free
    if (pTrajectory->previous!=NULL) {
        freeTN_P(pTrajectory->previous);
    }
    free(pTrajectory->cNode);
    free(pTrajectory);
}


/*lineage* consC(lineage* Lineage, node* nodeV) {
    //Add a node on the top of the list
    lineage* tmp = malloc(sizeof(node*));
    if (tmp == NULL) { //Insufficent space
        printf("ERREUR");
        return NULL;
    }
    Lineage->next = tmp; //Next Step
    tmp->pNode = nodeV;
    tmp->previous = Lineage; //Previous Step

    return tmp;
}*/