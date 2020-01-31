#include <stdio.h>
#include <stdlib.h>
#include "structures.h"

enum states{ball, empty, out};

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

void PrintPlat(enum states plat[7][7]) {
    printf("\n");
    for (int i=0; i<7; i++) {
        for (int j=0; j<7; j++) {
            if (plat[i][j]==ball) {
                printf("O");
            }
            else if (plat[i][j]==empty) {
                printf("X");
            }
            else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

void game(int x) {
    //define 7x7 platform
    enum states plat[7][7];
    for (int i=0; i<7; i++) {
        for (int j=0; j<7; j++) {
            if ( (i%6==0 && j%6==0) || (i%6==0 && j==1) || (i==1 && j%6==0) || (i%6==0 && j==5) || (i==5 && j%6==0) ) {
                plat[i][j] = out;
            }
            else if ( i==j && i==3 ) {
                plat[i][j] = empty;
            }
            else {
                plat[i][j] = ball;
            }
        }
    }

    //user game
    if (x==1) {
        PrintPlat(plat);
    }

    //auto resolution
    else {

    }
}

int main(){ 
    int x;

    //intro
    printf("WELCOME TO SOLITAIRE VERSION 1.0\n");
    printf("\n");

    //choice of mode
    printf("PRESS 1 TO PLAY OR 2 FOR SELF RESOLUTION\n");
    scanf("%d",&x);

    //checking for input error
    while (x!=1 && x!=2) {
        printf("INPUT ERROR !!\n");
        printf("\n");
        printf("PRESS 1 TO PLAY OR 2 FOR SELF RESOLUTION\n");
        scanf("%d",&x);
    }

    //actual game
    game(x);

    //bye bye
    printf("\n");
    printf("GOOD BYE ^~^\n");

    return 0;
}