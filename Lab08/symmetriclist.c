#include <stdio.h>
#include <stdlib.h>
#include "symmetriclist.h"

//Essa funcao insere elementos na lista
void Insert(SymmetricList *L)
{
    //Inicializo variaveis e crio o novo Node
    int pos;
    double num;
    scanf("%d %lf", &pos, &num);
    Node *NewNode;
    NewNode = malloc(sizeof(Node));
    NewNode->num = num;

    //Primeira insercao eh mais facil assim
    if ((*L).head.b == NULL && (*L).tail.b == NULL)
    {
        (*L).head.b = NewNode;
        (*L).tail.b = NewNode;
        NewNode->a = NULL;
        NewNode->b = NULL;
    }

    //Se a insercao for no inicio, eh mais facil adaptar logo o inicio
    else if (pos == 0)
    {
        NewNode->b = (*L).head.b;
        NewNode->a = NULL;
        if ((*L).head.b->a == NULL) (*L).head.b->a = NewNode;
        else (*L).head.b->b = NewNode;
        (*L).head.b = NewNode;
    }

    //Se a insercao for no final, eh mais facil adaptar logo o final
    else if (pos >= (*L).size)
    {
        NewNode->a = (*L).tail.b;
        NewNode->b = NULL;
        if ((*L).tail.b->b == NULL) (*L).tail.b->b = NewNode;
        else (*L).tail.b->a = NewNode;
        (*L).tail.b = NewNode;
    }

    //Caso Geral: Percorre ate achar a posicao de insercao
    else
    {
        int contador;
        contador = 1;

        //Uso anterior e proximo para percorrer a lista,
        //mantendo em maos as posicoes anterior e proxima so local onde ocorrera a insercao.
        //Isso facilita a posterior manipulacao dos ponteiros
        Node *proximo, *anterior;
        anterior = (*L).head.b;
        proximo = (anterior->b == NULL)? anterior->a : anterior->b;

        //Avanco com os ponteiros pela lista ate achar a posicao de insercao
        while(contador != pos)
        {
            contador++;
            if (proximo->a == anterior)
            {
                anterior = proximo;
                proximo = anterior->b;
            }
            else
            {
                anterior = proximo;
                proximo = anterior->a;
            }
        }


        //Encontrada a posicao, corrigo os ponteiros de NewNode
        NewNode->a = anterior;
        NewNode->b = proximo;

        //Entao, identifico quais sao os apontadores de proximo e anterior que devem ser modificados
        // e realizo o ajuste
        if (anterior->a == proximo && proximo->a == anterior)
        {
            anterior->a = NewNode;
            proximo->a = NewNode;
        }
        else if (anterior->a == proximo && proximo->b == anterior)
        {
            anterior->a = NewNode;
            proximo->b = NewNode;
        }
        else if (anterior->b == proximo && proximo->a == anterior)
        {
            anterior->b = NewNode;
            proximo->a = NewNode;
        }
        else if (anterior->b == proximo && proximo->b == anterior)
        {
            anterior->b = NewNode;
            proximo->b = NewNode;
        }
    }

    //Atualizo o comprimento
    ((*L).size)++;
}

//Essa funcao imprime todos os elementos da lista simetrica, em ordem de head a tail
void Print(SymmetricList L)
{
    int contador = 1;
    Node *anterior;
    anterior = L.head.b;

    //Se nao temos nenhum elemento nao se preocupe
    if (L.size == 0) return;

    //Se ha somente 1 elemento, melhor simplificar
    if (L.size == 1) printf("%.4lf ", anterior->num);

    //Do contrario percorre a lista normal,
    //eh preciso tomar cuidado com qual ponteiro aponta para o proximo
    else
    {
        Node *proximo;
        proximo = (anterior->b == NULL)? anterior->a : anterior->b;
        printf("%.4lf ", anterior->num);
        while(contador != L.size)
        {
            printf("%.4lf ", proximo->num);
            contador++;
            if (proximo->a == anterior)
            {
                anterior = proximo;
                proximo = anterior->b;
            }
            else
            {
                anterior = proximo;
                proximo = anterior->a;
            }
        }
    }

    printf("\n");

}


//Essa funcao inverte uma parte da lista
void Revert(SymmetricList *L)
{
    int inicio, termino;
    scanf("%d %d", &inicio, &termino);

    //Caso mais simples: reversao completa
    if (inicio == 0 && termino == (*L).size - 1)
    {
        Node *aux;
        aux = (*L).head.b;
        (*L).head.b = (*L).tail.b;
        (*L).tail.b = aux;
    }

    //Inicio no primeiro termo e final em um caso generico
    else if (inicio == 0)
    {
        int contador = 1;
        Node *proximo, *anterior;
        anterior = (*L).head.b;
        proximo = (anterior->b == NULL)? anterior->a : anterior->b;

        //Avanco com os ponteiros pela lista enquanto possivel
        while(contador != termino + 1)
        {
            contador++;
            if (proximo->a == anterior)
            {
                anterior = proximo;
                proximo = anterior->b;
            }
            else
            {
                anterior = proximo;
                proximo = anterior->a;
            }
        }

        //Entao troco os apontadores, notando se eh a ou b o ponteiro certo
        if ((*L).head.b->b == NULL) (*L).head.b->b = proximo;
        else (*L).head.b->a = proximo;

        if(proximo->b == anterior) proximo->b = (*L).head.b;
        else proximo->a = (*L).head.b;

        if (anterior->b == proximo) anterior->b = NULL;
        else anterior->a = NULL;

        (*L).head.b = anterior;
    }

    //Inicio em um caso generico e final no ultimo termo
    else if (termino == (*L).size - 1)
    {
        //printf("Fim = n - 1 \n");
        int contador = 1;
        Node *proximo, *anterior;
        anterior = (*L).head.b;
        proximo = (anterior->b == NULL)? anterior->a : anterior->b;

        //Avanco com os ponteiros pela lista enquanto possivel
        while(contador != inicio)
        {
            contador++;
            if (proximo->a == anterior)
            {
                anterior = proximo;
                proximo = anterior->b;
            }
            else
            {
                anterior = proximo;
                proximo = anterior->a;
            }
        }

        //Entao troco os apontadores, notando se eh a ou b o ponteiro certo
        if ((*L).tail.b->b == NULL) (*L).tail.b->b = anterior;
        else (*L).tail.b->a = anterior;

        if(proximo->b == anterior) proximo->b = NULL;
        else proximo->a = NULL;

        if (anterior->b == proximo) anterior->b = (*L).tail.b;
        else anterior->a = (*L).tail.b;

        (*L).tail.b = proximo;
    }

    //Caso Geral
    else
    {
        int contador = 1;
        Node *proximo1, *anterior1;
        anterior1 = (*L).head.b;
        proximo1 = (anterior1->b == NULL)? anterior1->a : anterior1->b;

        //Avanco com os ponteiros pela lista ate achar o ponto de virada do inicio
        while(contador != inicio)
        {
            contador++;
            if (proximo1->a == anterior1)
            {
                anterior1 = proximo1;
                proximo1 = anterior1->b;
            }
            else
            {
                anterior1 = proximo1;
                proximo1 = anterior1->a;
            }
        }

        Node *anterior2, *proximo2;
        anterior2 = anterior1;
        proximo2 = proximo1;

        //Avanco com os ponteiros pela lista ate achar o ponto de virada do termino
        while(contador != termino + 1)
        {
            contador++;
            if (proximo2->a == anterior2)
            {
                anterior2 = proximo2;
                proximo2 = anterior2->b;
            }
            else
            {
                anterior2 = proximo2;
                proximo2 = anterior2->a;
            }
        }


        //Entao troco os ponteiros
        if (anterior1->b == proximo1) anterior1->b = anterior2;
        else anterior1->a = anterior2;

        if (anterior2->b == proximo2) anterior2->b = anterior1;
        else anterior2->a = anterior1;

        if (proximo1->b == anterior1) proximo1->b = proximo2;
        else proximo1->a = proximo2;

        if (proximo2->b == anterior2) proximo2->b = proximo1;
        else proximo2->a = proximo1;
    }
}

//Essa funcao libera toda a memoria
void Destroy(SymmetricList *L)
{
    //Em uma lista vazia, nada se faz
    if ((*L).size == 0) return;

    //Se tiver so um elemento, liberamos so ele
    else if ((*L).size == 1) free((*L).head.b);

    //Do contrario vamos percorrer liberando toda a lista
    else
    {
        Node *proximo, *percorre;
        percorre = (*L).head.b;
        proximo = (percorre->b == NULL)? percorre->a : percorre->b;
        while(proximo->b != NULL && proximo->a != NULL)
        {
            if (proximo->a == percorre)
            {
                free(percorre);
                percorre = proximo;
                proximo = percorre->b;
            }
            else
            {
                free(percorre);
                percorre = proximo;
                proximo = percorre->a;
            }
        }

        //Se o tamanho for 2, o while nao eh realizado
        if ((*L).size == 2) free(percorre);

        //Sempre falta eliminar o proximo
        free(proximo);
    }
}
