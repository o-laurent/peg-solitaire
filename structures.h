#include <stdio.h>
#include <stdlib.h>


typedef struct sorted_children sorted_children;
typedef struct node node;
struct sorted_children {
    node *child;
    sorted_children *next;
} ;

struct node {
    float  data;
    node *child;
    node *brother;
    node *parent;
    sorted_children *lineage;
};

float cost_f(node *child);
void buildLineage(node* currentNode, sorted_children *lineage);
void sort_lists(int children_nb, float *cost_list, node **children_array);
