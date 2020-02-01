#include <stdio.h>
#include <stdlib.h>

typedef enum direction {north, south, east, west} direction;
typedef struct sorted_children sorted_children;
typedef struct node node;
typedef struct movement movement;

struct sorted_children {
    //List of nodes sorted by increasing costs
    node *child;
    sorted_children *next;
};

struct node {
    //model of a node
    float  cost;
    node *child;
    node *brother;
    node *parent;
    sorted_children *lineage;
};

struct movement {
    //optimized model of a movement
    unsigned char posix;
    unsigned char posiy;
    direction dir;
};

float cost_f(node *child);
void buildLineage(node* currentNode, sorted_children *lineage);
void sort_lists(int children_nb, float *cost_list, node **children_array);

typedef trajectory trajectory;
struct trajectory {
    //Remembers the different steps
    state board[7][7];
    trajectory next;
}