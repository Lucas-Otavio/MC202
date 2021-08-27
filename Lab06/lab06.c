#include <stdio.h>
#include <stdlib.h>
#include "lists.h"

int main()
{
    //Inicializacao de variaveis de controle, node inicial e vetores que vao tornar o codigo mais simpatico
    int size, NumRequest, i, j;
    int (*operacoes[3]) (Node**, int*, int) = {MTF, TPS, CNT};
    char ar[] = {' ', ' ', '\n'};
    Node *head;

    //Formacao do vetor de requisicoes
    scanf("%d\n", &size);
    scanf("%d\n", &NumRequest);
    int requests[NumRequest];
    for(i = 0; i < NumRequest; i++) scanf("%d", &requests[i]);


    //Chamada de funcoes
    for(j = 0; j < 3; j++)
    {
        head = malloc(sizeof(Node));
        CreateList(size, head);
        printf("%d%c", operacoes[j](&head, requests, NumRequest), ar[j]);
        ObliterateList(&head);
    }
    return 0;
}
