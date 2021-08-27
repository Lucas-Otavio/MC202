#ifndef LISTSH
#define LISTSH

struct Node
{
    int n;
    int count;
    struct Node *next;
};

typedef struct Node Node;

void CreateList(int, Node*);
void PrintList(Node* p);
void ObliterateList(Node**);

int MTF(Node**, int*, int);
int TPS(Node**, int*, int);
int CNT(Node**, int*, int);

#endif
