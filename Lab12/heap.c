#include "heap.h"

//This function creates the heap
void CreateHeap(p_Heap p_heap)
{
    //Allocating memory for the vector
    p_heap->heap = malloc(p_heap->size * sizeof(int));
    if (!p_heap->heap) exit(1); //Preventing memory allocation errors
    int NewNumber, i;

    //Inserting element by element while worrying with keeping the vector an implicit heap
    for(i = 0; i < p_heap->size; i++)
    {
        scanf("%d", &NewNumber);
        Insertion(p_heap, NewNumber);
    }
}

//This function inserts a new number to the heap, while keeping its characteristics and updating the end place
void Insertion(p_Heap p_heap, int NewNumber)
{
    //Initializing a few important variables, updating the end, entering the new number in the leftest empty place
    int added, parent;
    added = ++(p_heap->end);
    p_heap->heap[added] = NewNumber;
    parent = (added - 1)/2;

    //This loop maintains the vector a maximum heap: it brings the number to its parent place while it is greater
    while (p_heap->heap[parent] < p_heap->heap[added])
    {
        //Switching places
        Swap(&(p_heap->heap[parent]), &(p_heap->heap[added]));

        //Updating variables accordingly to the switch
        added = parent;
        parent = (added - 1)/2; //Since it is an operation between integers we are going to get the floor of it
    }
}

//This function removes the maximum number of the heap, while keeping its characteristics and updating the end place
void Removal(p_Heap p_heap)
{
    //Removing the maximum number and putting the rightest element in the implicit root
    Swap(&(p_heap->heap[(p_heap->end)--]), &(p_heap->heap[0]));

    //Defining important variables respecting the heap limit
    int Moved = 0, MaxChild = 0, l, r;
    l = 1;
    r = 2;
    MaxChild = WhichIsMaxChild(p_heap, l, r, MaxChild);

    //This loop maintains the vector a maximum heap: it brings the number to its maximum child place if it is greater and in the heap
    while (p_heap->heap[MaxChild] > p_heap->heap[Moved])
    {
        //Switching places
        Swap(&(p_heap->heap[Moved]), &(p_heap->heap[MaxChild]));

        //Updating variables accordingly to the switch, the heap distribution and limit
        Moved = MaxChild;
        l = 2 * Moved + 1;
        r = 2 * Moved + 2;
        MaxChild = WhichIsMaxChild(p_heap, l, r, MaxChild);
    }
}

//This function finds the Maximum Child and returns it
int WhichIsMaxChild(p_Heap p_heap, int l, int r, int MC)
{
    //The strategy is to check if the given child is in the heap and if so determine which (left or right) is greater
    //If the Max Child value is not changed, the loop is ended, since Moved and MaxChild will refer to the same value
    if (l <= p_heap->end) MC = l;
    if (r <= p_heap->end && p_heap->heap[r] > p_heap->heap[l]) MC = r;
    return MC;
}

//Function to promote swaps avoiding code repetition
void Swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
