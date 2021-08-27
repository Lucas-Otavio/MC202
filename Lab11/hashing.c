#include "hashing.h"

//Hashing Function close to the one suggested
short hashing(char str[256])
{
    unsigned long long int hash = 5381;
    char c;

    while ((c = *str++)) hash = (((hash << 5) + hash) + c) & 0x00ffffffffffffff; //Preventing Overflow
    return (short) (hash % 7499);
}

//Function that creates a new node and sets its variables
p_Node CreateNode(char str[256], int id)
{
    p_Node NewNode = malloc(sizeof(Node));
    strcpy(NewNode->sentence, str);
    NewNode->id = id;
    NewNode->next = 0x0;
    return NewNode;
}

//Function that inserts the string in the Hashing Table and returns the next id
int insertion(p_Node Table[7499], int NextId)
{
    //First of all, we get the string, hash it and find out what to do with it
    char str[256];
    scanf(" %[^\n]", str);
    short position = hashing(str);
    p_Node prev = Table[position];


    //After determined where it should be inserted, we put it there
    if (!prev) Table[position] = CreateNode(str, NextId++);

    //Or chain it, in case it isn't in the chain
    else
    {
        //Loop that finds where to insert and stops if the string is in the Table
        while(prev->next && strcmp(prev->sentence, str)) prev = prev->next;

        //If the strings are different, we add a node
        if(strcmp(prev->sentence, str)) prev->next = CreateNode(str, NextId++);
    }

    return NextId; //The return fixes the id in main
}

//Function that searches for the string
void browse(p_Node Table[7499])
{
    //First of all, we get the string and hash it
    char str[256];
    scanf(" %[^\n]", str);
    short position = hashing(str);
    p_Node ptr = Table[position];

    //The idea is to, once found the position through hashing, run through the chain and find out if is in it
    while (ptr)
    {
        //If so, we let it know that it was found
        if (!strcmp(ptr->sentence, str))
        {
            printf("%s encontrada, id %d\n", str, ptr->id);
            return;
        }
        ptr = ptr->next;
    }

    //Otherwise, it is not in the Table
    printf("%s nao encontrada\n", str);

}

//Function that removes a string from the Hashing Table
void erase(p_Node Table[7499])
{
    //First of all, we get the string and hash it
    char str[256];
    scanf(" %[^\n]", str);
    short position = hashing(str);
    p_Node prev = Table[position];

    //If there's no string in that position, forget about it
    if (!prev) return;

    //Check for the first element of the chain; if so, we release memory and fix a Table's pointer
    if (!strcmp(prev->sentence, str))
    {
        Table[position] = prev->next;
        free(prev);
        return;
    }

    //If is not in the first node, we run through the chain looking for the next node
    while(prev->next)
    {
        //If it is in the chain we take it out and release memory; otherwise, we leave it as it is
        if (!strcmp(prev->next->sentence, str))
        {
            p_Node toDelete = prev->next;
            prev->next = prev->next->next;
            free(toDelete);
            return;
        }
        prev = prev->next;
    }
}


