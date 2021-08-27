#include "heap.h"

/*
IMPORTANT INFORMATION:
This is a code made for the subject Data Structures (MC202) at Unicamp-IC taught by GPT
Author: Lucas Otavio Nascimento de Araujo 240106
Objective: Implement in-place heap sort in an implicit heap structure
Input: The size of the heap followed by <size> integers
Output: The heap, after being sorted with a space after each element
Current Situation: Everything working nice and clean
*/


//The strategy was to implement a maximum heap, so that after removing the maximum
//it could be put after the heap in its vector, keeping the algorithm in-place
int main()
{
    //Initializing and creating the Heap and some important variables
    int i;
    Heap heap;
    scanf("%d", &(heap.size));
    if (heap.size < 1) return 0;
    heap.end = -1;
    CreateHeap(&heap);

    //Removing the maximum of the Heap and putting it right at its end
    for(i = 0; i < heap.size; i++) Removal(&heap);

    //Printing the heap after being sorted
    for(i = 0; i < heap.size; i++) printf("%i ", heap.heap[i]);
    printf("\n");

    //Releasing memory to avoid memory leak
    if (heap.heap) free(heap.heap);
    return 0;
}
