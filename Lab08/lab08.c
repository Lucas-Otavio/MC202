#include <stdio.h>
#include <stdlib.h>
#include "symmetriclist.c"

/*
Objetivo: Controlar e Realizar operacoes (insercao, reversao e impressao) em uma lista simetrica.
Em uma lista simetrica, cada ponteiro aponta para os nos adjacente,
mas eles nao identificam de maneira fixa o proximo e o anterior

Entrada: Operacoes no formato:
    * Insercao: i pos valor
    * Reversao: v posi posf
    * Impressao: p

Saida: Gerada pela impressao no formato:
    x_1 x_2 x_3 ... x_(SymmetricList).size

Situacao Atual: Todas as funcoes funcionam conforme o esperado - FINALIZADO
*/

int main()
{
    //Criacao da lista simetrica
    char op;
    DummyNode *h, *t;
    SymmetricList Lista;
    h = malloc(sizeof(DummyNode));
    t = malloc(sizeof(DummyNode));
    (*h).b = NULL;
    (*t).b = NULL;
    Lista.head = *h;
    Lista.tail = *t;
    Lista.size = 0;

    //Loop que direciona os comandos as suas funcoes
    while(scanf("%c", &op) != EOF)
    {
        if (op == 'i') Insert(&Lista);
        else if (op == 'p') Print(Lista);
        else if (op == 'v') Revert(&Lista);
        else if (op == 't') break;
    }

    Destroy(&Lista);
    free(h);
    free(t);

    return 0;
}
