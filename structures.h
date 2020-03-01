#ifndef STRUCTURES_H_
#define STRUCTURES_H_

typedef enum direction {north, south, east, west} direction;
typedef enum state {ball, empty, out} state;
typedef struct sorted_children sorted_children;
typedef struct node node;
typedef struct movement movement;
typedef struct movementList movementList;

typedef struct trajectory trajectory;
struct trajectory {
    //Double linked list which remembers the different steps
    state** board;
    trajectory* next;
    trajectory* previous;
};

typedef struct trajectoryNode trajectoryNode;
struct trajectoryNode {
    //Double linked list which remembers the different steps in the tree of possibilities
    node* cNode; //Tree
    trajectoryNode* next;
    trajectoryNode* previous;
};

struct node {
    //model of a node
    int cost;
    int childNb;
    state** board;
    node* child;
    node* next;
    node* parent;
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

void printSizes();

movementList* consML (movement* move, movementList* moveList);

//trajectory functions
trajectory* consT(state** board, trajectory* pTrajectory);
void freeT_P(trajectory* pTrajectory);

//trajectoryNode functions
trajectoryNode* consTN(node* board, trajectoryNode* pTrajectory, int* trajectoryFree);
trajectoryNode* rmtTN(trajectoryNode* pTrajectory, int* nodeFree, int* boardFree, int* trajectoryFree, int lineNb);
void freeNode(node* cNode, int* nodeFree, int* boardFree);
void freeTN_P(trajectoryNode* pTrajectory, int lineNb);

//void buildLineage(node* currentNode, sorted_children *lineage);
void sortNodes(node** phead);
node* sortedMerge(node* a, node* b);
void nodeSplit(node* source, node** frontRef, node** backRef);
void printBoardV(state** board, char lineNb, char colNb);
#endif