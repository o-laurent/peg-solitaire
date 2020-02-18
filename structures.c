#ifndef STRUCTURES_H_
#define STRUCTURES_H_
#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#endif


void buildLineage(node* currentNode, sorted_children *lineage){
    node *child = currentNode;
    unsigned int children_nb = 0;
    while(child != NULL){
        children_nb ++;
        child = child->next
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
}

void sortNodes(node** phead){
    node* head = *phead;
    if((phead==NULL) || (headref->next==NULL)) {
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
    struct Node* result = NULL; 
    if (a == NULL) {
        return (b); 
    }
    else if(b == NULL){ 
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