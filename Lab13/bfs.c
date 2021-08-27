#include "bfs.h"
#include "queue.h"


//This function creates a new edge. It takes as parameters the numbers of the nodes that are connected by the edge and the Graph
void AddEdge(p_Edge *EdgesList, int begin, int end)
{
    //After creating a new edge, it is inserted in the such a way that the edges keep ordered by the initial vertice ignoring the terminal one
    p_Edge NewNode = CreateEdge(begin, end);
    p_Edge Running = *EdgesList; //This pointer runs through the list

    //If the list is empty its head has to be changed
    if(!Running)
    {
        *EdgesList = NewNode;
        return;
    }

    //While there is a next edge and it is smaller than the edge to be inserted, we move forward
    while(Running->next)
    {
        if (NewNode->initial <= Running->next->initial) break;
        Running = Running->next;
    }

    //After determining a correct spot to insert, we just change a few pointers
    NewNode->next = Running->next;
    Running->next = NewNode;
}

//This function creates a new node, it receives as parameter the numbers of the nodes that are connected by an edge and return the edge
p_Edge CreateEdge(int begin, int end)
{
    p_Edge NewNode = malloc(sizeof(Edge));
    if (!NewNode) exit(1); //In case of memory allocation failure, it ends the program

    //Setting important variables
    NewNode->initial = begin;
    NewNode->terminal = end;
    NewNode->next = 0x0;
    return NewNode;
}

//This function creates and returns a Vector from the Linked List of Edges and correctly change the values of the Vertices Vector,
//so that it is represented as a Vector of adjacencies.
//It takes as parameters the Edges Linked List, the Vertices Vector and the total number of Edges(x2) and Vertices
int * FromListtoVector(p_Edge EdgesList, int *VerticesVector, int E, int V)
{
    int *EdgesVector = malloc(E*sizeof(int));
    int i, j = 0;
    for (i = 0; i < E; i++)
    {
        EdgesVector[i] = EdgesList->terminal;
        while (j < EdgesList->initial && j < V) VerticesVector[j++] = i;
        if (VerticesVector[j] == -1 && EdgesList->initial == j) VerticesVector[j++] = i;
        EdgesList = EdgesList->next;
    }
    VerticesVector[V] = E;
    return EdgesVector;
}

//This Recursive function releases used memory in the linked list
void destroy(p_Edge Edge)
{
    if (Edge->next) destroy(Edge->next);
    free(Edge);
}

//This function applies BFS to the Graph using a queue and 2 auxiliary queue functions (queue and dequeue)
void BFS(int *VerticesVector, int *EdgesVector, int V, int source)
{
    //Creating Visited Bit Vector -> 0 if the Vertice wasn't visited; 1, otherwise
    //And also initializing many important variables
    int i, Vertice, distance = 0, lenght, edge;
    lenght = (V >> 3) + 1;
    char Visited[lenght];
    for (i = 0; i < lenght; i++) Visited[i] = 0;
    Queue BFSqueue;
    BFSqueue.size = 0;

    //Beginning BFS from the source
    enqueue(&BFSqueue, Visited, source, distance);

    //While the queue is not empty, still there are reachable Graph Vertices
    while(BFSqueue.size)
    {
        //In every loop, the distance of the to be added Graph Vertices are determined,
        //the vertice to be evaluated id dequeued and the non previously visited Nodes are visited
        distance = BFSqueue.head->distance + 1;
        Vertice = dequeue(&BFSqueue);
        for (edge = VerticesVector[Vertice]; edge < VerticesVector[Vertice + 1]; edge++)
        {
            if (!((Visited[((EdgesVector[edge]) >> 3)] >> (EdgesVector[edge] & seven)) & 00000001 )) enqueue(&BFSqueue, Visited, EdgesVector[edge], distance);
        }
    }
}

