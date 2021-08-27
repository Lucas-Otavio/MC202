#ifndef HEAPH
#define HEAPH

//Libraries used by both lab12.c and heap.c
#include <stdio.h>
#include <stdlib.h>

//A Heap structure, so that less parameters are needed in the function calls
typedef struct Heap
{
    int size;  //List size
    int *heap; //Elements list
    int end;   //The last heap element
} Heap;


//A few declarations
typedef Heap * p_Heap;

void CreateHeap(p_Heap);
void Insertion(p_Heap, int);
void Removal(p_Heap);
int WhichIsMaxChild(p_Heap, int, int, int);
void Swap(int*, int*);
//Pointers were used so that Heap.end value could be changed inside these functions

#endif // HEAPH
