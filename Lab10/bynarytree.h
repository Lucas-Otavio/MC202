#ifndef BYNARYTREEH
#define BYNARYTREEH

//Libraries used for both files
#include <stdio.h>
#include <stdlib.h>


//Important tree and queue structures
typedef struct Node
{
    int value;
    struct Node *right, *left, *parent;
} Node;


typedef struct QueueNode
{
    struct Node *branch;
    struct QueueNode *next;
} QueueNode;

typedef struct queue
{
    struct QueueNode *head, *tail;
    int size;
} queue;




//Tree functions
void insert(Node**);
void preorder(Node*);
void inorder(Node*);
void postorder(Node*);
void width(Node*);
void search(Node*);
void extract(Node**);
void maximum(Node*);
void minimum(Node*);
void predecessor(Node*);
void successor(Node*);
int search_interval(Node*, int, int, int);
void cut(Node*);

//Debugging function
void details(Node*);

//Queue functions
void enqueue(queue*, Node*);
void dequeue(queue*);


#endif // BYNARYTREEH
