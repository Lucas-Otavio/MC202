#include "queue.h"


//This function enqueues a value to the queue, updating its status in the Visited bit arrow,
//including the vertice and distance values and increasing the queue's size
void enqueue(p_Queue queue, char *Visited, int element, int dist)
{
    p_QueueNode NewQueueNode = malloc(sizeof(QueueNode));
    NewQueueNode->Vertice = element;
    NewQueueNode->distance = dist;
    Visited[(element >> 3)] |= 00000001 << (element & seven);
    if (!queue->size) queue->head = NewQueueNode;
    else queue->tail->next = NewQueueNode;
    queue->tail = NewQueueNode;
    NewQueueNode->next = 0x0;
    (queue->size)++;
}


//Queue Function: removes the head element and returns its vertice, but before it prints an expected part of the output
int dequeue(p_Queue queue)
{
    if (!queue->size) return -1;
    p_QueueNode toDelete;
    toDelete = queue->head;
    int v = toDelete->Vertice;
    printf("%d %d\n", (toDelete->Vertice + 1), toDelete->distance);
    queue->head = queue->head->next;
    free(toDelete);
    (queue->size)--;
    return v;
}
