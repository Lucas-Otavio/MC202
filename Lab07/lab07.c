#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sequencias.c"

/*
Objetivo: Manipular uma sequencia/lista, usando um vetor dinamico
O programa deve ser capaz de inserir, remover e printar no inicio e no fim
e dizer se a sequencia se encontra vazia ou nao
Entrada: Ordem, seguido de numero se for insercao
Saida: resposta se a sequencia esta vazia (yes/no), printar o elemento desejado
Status: Tudo Funcionando perfeitamente
*/

int main()
{
    //Inicialziacao das variaveis
    VetorDinamico sequencia;
    sequencia.Vetor = malloc(sizeof(int));
    sequencia.Vetor[0] = 0;
    sequencia.inicio = sequencia.fim = 0;
    sequencia.tamanho = 1;
    sequencia.QuantOcup = 0;
    int numero;
    char ordem[30]; //Tamanho suficiente para receber o maior comando

    //Loop que permite a execucao das ordens
    while(scanf("%s", ordem) != EOF)
    {
        if (!strcmp(ordem, "is-empty")) IsEmpty(sequencia);
        else if (!strcmp(ordem, "insert-first"))
        {
            scanf("%d", &numero);
            if (InsertFirst(&sequencia, numero) == 1) return 0xABCDEF;
        }
        else if (!strcmp(ordem, "remove-first")) RemoveFirst(&sequencia);
        else if (!strcmp(ordem, "print-first")) PrintFirst(sequencia);
        else if (!strcmp(ordem, "insert-last"))
        {
            scanf("%d", &numero);
            InsertLast(&sequencia, numero);
        }
        else if (!strcmp(ordem, "remove-last")) RemoveLast(&sequencia);
        else if (!strcmp(ordem, "print-last")) PrintLast(sequencia);
        else if (!strcmp(ordem, "exit")) break;
    }

    free(sequencia.Vetor);

    return 0;
}

