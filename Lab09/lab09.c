#include <string.h>
#include "bynarytree.h"

/*
IMPORTANT INFORMATION:
Author: Lucas Otavio Nascimento de Araujo 240106
Objective: Create and operate (insert, extract, search and print) in an integer Binary Search Tree
Input: Operation (insert, extract, search, preorder, inorder, postorder, width) and number if needed
Output: The result of the printing (All numbers in preorder, inorder, postorder or width) if necessary
and if a number belongs or not to the tree
Current Situation: everything working nice and clean
*/

int main()
{
    //initializing variables
    char order[12];
    Node *root = 0x0;

    //loop that receives the orders and commands its executions
    while(scanf("%s", order) != EOF)
    {
        if (!strcmp(order, "inserir")) insert(&root);
        else if (!strcmp(order, "excluir")) extract(&root);
        else if (!strcmp(order, "buscar")) search(root);
        else if (!strcmp(order, "pre-ordem"))
        {
            if (root == 0x0)
            {
                printf("vazia\n");
                continue;
            }
            preorder(root);
            printf("\n");
        }
        else if (!strcmp(order, "pos-ordem"))
        {
            if (root == 0x0)
            {
                printf("vazia\n");
                continue;
            }
            postorder(root);
            printf("\n");
        }
        else if (!strcmp(order, "em-ordem"))
        {
            if (root == 0x0)
            {
                printf("vazia\n");
                continue;
            }
            inorder(root);
            printf("\n");
        }
        else if (!strcmp(order, "largura"))
        {
            if (root == 0x0)
            {
                printf("vazia\n");
                continue;
            }
            width(root);
            printf("\n");
        }
        else if (!strcmp(order, "terminar")) break;
    }
    if (root != 0x0) cut(root);
}
