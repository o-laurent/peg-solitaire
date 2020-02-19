#ifndef STRUCTURES_H_
#define STRUCTURES_H_

typedef enum direction {north, south, east, west} direction;
typedef enum state {ball, empty, out} state;
typedef struct sorted_children sorted_children;
typedef struct node node;
typedef struct movement movement;
typedef struct movementList movementList;

struct sorted_children {
    //List of nodes sorted by increasing costs
    node *child;
    sorted_children *next;
};

struct node {
    //model of a node
    float cost;
    state** board;
    node* child;
    node* next;
    node* parent;
    sorted_children* lineage;
};

struct movement {
    //optimized model of a movement
    char posix;
    char posiy;
    direction dir;
};

struct movementList {
    movement move;
    movementList* next;
};

movementList* consML (movement* move, movementList* moveList);
//void buildLineage(node* currentNode, sorted_children *lineage);
void sortNodes(node** phead);
node* sortedMerge(node* a, node* b);
void nodeSplit(node* source, node** frontRef, node** backRef);
#endif