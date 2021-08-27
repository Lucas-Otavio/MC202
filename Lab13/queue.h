#ifndef QUEUEH
#define QUEUEH

//libraries and definitions used in both main, queue and bfs
#include <stdio.h>
#include <stdlib.h>
#define seven 0x00000007

//Important Queue declarations
typedef struct QueueNode
{
    int Vertice;
    int distance;
    struct QueueNode *next;
} QueueNode;
typedef QueueNode * p_QueueNode;

typedef struct Queue
{
    p_QueueNode head, tail;
    int size;
} Queue;
typedef Queue * p_Queue;

void enqueue(p_Queue, char*, int, int);
int dequeue(p_Queue);

#endif // QUEUEH
