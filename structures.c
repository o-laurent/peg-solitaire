#include <stdio.h>
#include <stdlib.h>
#include "structures.h"

void buildLineage(node* currentNode, sorted_children *lineage){
    node *child = currentNode;
    unsigned int children_nb = 0;
    while(child != NULL){
        children_nb ++;
    }

    float cost_list[children_nb];
    node *children_array[children_nb];
    int i=0;
    for(i=0; i<children_nb; i++){
        children_array[i] = child;
        cost_list[i] = cost_f(child);
        child = child->brother;
    }

    sort_lists(children_nb, cost_list, children_array);        
}

float cost_f(node *child){
    return child->data;
}

void sort_lists(int children_nb, float *cost_list, node **children_array){

}

int main(){
    
}