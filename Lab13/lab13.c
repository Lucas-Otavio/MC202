#include "queue.h"
#include "bfs.h"


/*
IMPORTANT INFORMATION:
This is a code made for the subject Data Structures (MC202) at Unicamp-IC taught by GPT
Author: Lucas Otavio Nascimento de Araujo 240106
Objective: Implement BFS search in a non oriented graph
Input: The number of vertices V in the graph, then many edges beginning and terminal Nodes, finally the Vertice (source) wished to apply the BFS on
Output: All the Vertices reachable from the source followed by the distance between them
Current Situation: Everything working nice and clean
*/


int main()
{
    //Initializing vector and a few variables
    int V, E = 0, i, begin, end, source;
    scanf("%d", &V);
    int VerticesVector[V + 1];
    for(i = 0; i <= V; i++) VerticesVector[i] = -1;

    p_Edge EdgesList = 0x0;

    //Creating the Graph
    scanf("%d,%d", &begin, &end);
    while(begin-- != 0 && end-- != 0)
    {
        //It was needed to reduce begin, end and later source because the entrance considers 1 as the minimum entrance value
        //Since the Graph is non orientated, it is necessary to AddEdge in both directions
        E += 2;
        AddEdge(&EdgesList, begin, end);
        AddEdge(&EdgesList, end, begin);
        scanf("%d,%d", &begin, &end);
    }

    int * EdgesVector = FromListtoVector(EdgesList, VerticesVector, E, V);

    //Finding and printing the output through BFS
    scanf("%d", &source);
    printf("Origem da busca: %d\n", source);
    printf("Vertices alcancados e distancias:\n");
    BFS(VerticesVector, EdgesVector, V, --source);
    free(EdgesVector);
}
