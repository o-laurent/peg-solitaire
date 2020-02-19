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
    node* brother;
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

void buildLineage(node* currentNode, sorted_children *lineage);
void sort_lists(int children_nb, float *cost_list, node **children_array);

/* Important functions */
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
#endif