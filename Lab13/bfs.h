#ifndef BFSH

#define BFSH

//Edge declaration
typedef struct Edge
{
    int initial; //The initial graph vertice of the edge
    int terminal; //The terminal graph vertice of the edge
    struct Edge *next;
}Edge;
typedef Edge * p_Edge;

//Important declarations
void AddEdge(Edge **, int, int);
p_Edge CreateEdge(int, int);
int * FromListtoVector(p_Edge, int*, int, int);
void destroy(p_Edge);
void BFS(int*, int*, int, int);

#endif // BFSH
