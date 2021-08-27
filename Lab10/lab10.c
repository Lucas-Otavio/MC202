#include <string.h>
#include "bynarytree.c"

/*
IMPORTANT INFORMATION:
Author: Lucas Otavio Nascimento de Araujo 240106
Objective: Create and operate (insert, extract, search, minimum/maximum, predecessor/successor and print) in an integer Binary Search Tree
Input: Operation (insert, extract, search, search interval, maximum/minimum, predecessor/successor, preorder, inorder, postorder, width) and number if needed
Output: The result of the printing (All numbers in preorder, inorder, postorder or width) or of the retrieve(minimum\maximum, predecessor/successor)
and if a number/interval belongs or not to the tree
Current Situation: everything working nice and clean, separated in three files
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
        else if (!strcmp(order, "remover")) extract(&root);
        else if (!strcmp(order, "buscar")) search(root);
        else if (!strcmp(order, "minimo")) minimum(root);
        else if (!strcmp(order, "maximo")) maximum(root);
        else if (!strcmp(order, "predecessor")) predecessor(root);
        else if (!strcmp(order, "sucessor")) successor(root);
        else if (!strcmp(order, "buscar-intervalo"))
        {
            int n1, n2;
            scanf("%d", &n1);
            scanf("%d", &n2);
            if (root != 0x0) search_interval(root, n1, n2, 0);
            else printf("nenhuma");
            printf("\n");
        }
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
        else if (!strcmp(order, "detalhes"))
        {
            if (root == 0x0) printf("tudo vazio\n");
            else details(root);
        }
        else if (!strcmp(order, "terminar")) break;
    }
    if (root != 0x0) cut(root);
}
