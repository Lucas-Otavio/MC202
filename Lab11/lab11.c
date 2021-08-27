#include "hashing.h"

/*
IMPORTANT INFORMATION:
Author: Lucas Otavio Nascimento de Araujo 240106
Objective: Save, Access and Remove Strings from a Hashing Table
Input: Operation(i for insert, b for browse, r for remove or f for finish) and the string
Output: Browsing Report
*/



int main()
{
    //A few declarations
    p_Node Table[7499];
    //I chose size 7499 because I created a program to test exhaustedly all the prime numbers
    //greater than 0.8 * 5000 in all the 3 letters possibilities and it turned out to perform the best
    int i;
    int NextId = 0; //It tracks the id
    char order;

    //Setting all the pointers to NULL so that it works on Windows
    for(i = 0; i < 7499; i++) Table[i] = 0x0;

    //Loop that controls the orders
    while(1)
    {
        scanf("%c", &order);

        if (order == 'i') NextId = insertion(Table, NextId);
        else if (order == 'b') browse(Table);
        else if (order == 'r') erase(Table);
        else if (order == 'f') break;
    }

    //This section releases the memory used in the chained lists
    p_Node toDelete, temp;
    for(i = 0; i < 7499; i++)
    {
        toDelete = Table[i];
        while(toDelete)
        {
            temp = toDelete->next;
            free(toDelete);
            toDelete = temp;
        }
    }

    return 0;
}


