#ifndef HASHINGH
#define HASHINGH

//Libraries used for both hashing.c and lab11.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Item structure: it stores the string, its id and the next node, in case a collision occurs
typedef struct Node
{
    char sentence[256];
    int id;
    struct Node *next;
} Node;


//A few declarations
typedef Node * p_Node;

short hashing(char str[256]);
int insertion(p_Node Table[7499], int NextId);
p_Node CreateNode(char str[256], int id);
void browse(p_Node Table[7499]);
void erase(p_Node Table[7499]);

#endif // HASHINGH
