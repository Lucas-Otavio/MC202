#include <stdlib.h>
#include <stdio.h>
#include "sequencias.h"

int InsertFirst(VetorDinamico *sequencia, int numero)
{
    //Caso Vetor Vazio: So adicionamos o numero ao vetor e atualizamos os parametros
    if ((*sequencia).QuantOcup == 0)
    {
        (*sequencia).Vetor[0] = numero;
        (*sequencia).QuantOcup = 1;
    }

    //Se for o 1o redimensionamento, n % 1 == 0 => True para todo n, entao eh necessario esse caso especifico
    else if ((*sequencia).QuantOcup == 1 && (*sequencia).tamanho == 1)
    {
        int *Temp;
        Temp = malloc(2*sizeof(int));
        if (!Temp) return 1;
        Temp[1] = (*sequencia).Vetor[0];
        Temp[0] = numero;
        free((*sequencia).Vetor);
        (*sequencia).Vetor = Temp;
        (*sequencia).inicio = 0;
        (*sequencia).fim = 1;
        (*sequencia).tamanho = 2*((*sequencia).tamanho);
        ((*sequencia).QuantOcup++);
    }

    //Caso do Redimensionamento: Alto custo, aumentamos o tamanho do vetor, reorganizando os elementos no novo vetor,
    //entao adicionamos novo elemento e atualizamos os parametros
    else if ((*sequencia).QuantOcup == (*sequencia).tamanho)
    {
        int *Temp;
        Temp = malloc(2*((*sequencia).tamanho)*sizeof(int));
        if (!Temp) return 1;
        int i;
        for (i = (*sequencia).inicio; i % (*sequencia).tamanho != ((*sequencia).fim) % (*sequencia).tamanho; i++)
        {
            Temp[i-(*sequencia).inicio + 1] = (*sequencia).Vetor[i % (*sequencia).tamanho];
        }
        Temp[i-(*sequencia).inicio + 1] = (*sequencia).Vetor[i % (*sequencia).tamanho];
        Temp[0] = numero;
        free((*sequencia).Vetor);
        (*sequencia).Vetor = Temp;
        (*sequencia).tamanho = 2*((*sequencia).tamanho);
        ((*sequencia).QuantOcup++);
        (*sequencia).inicio = 0;
        (*sequencia).fim = (*sequencia).inicio + (*sequencia).QuantOcup - 1;
    }

    //Caso Geral: apenas adicionamos e atualizamos as variaveis
    else
    {
        //Se a posicao anterior seria negativa, coloca-se na ultima pos do vetor
        if ((*sequencia).inicio == 0)
        {
            (*sequencia).inicio = (*sequencia).tamanho - 1;
            (*sequencia).Vetor[(*sequencia).inicio] = numero;
            ((*sequencia).QuantOcup++);
        }

        //Caso Realmente Geral: adicionamos na posicao anterior
        else
        {
            (*sequencia).inicio = (*sequencia).inicio - 1;
            (*sequencia).Vetor[(*sequencia).inicio] = numero;
            ((*sequencia).QuantOcup++);
        }
    }
    return 0;
}


void RemoveFirst(VetorDinamico *sequencia)
{
    //Removeremos apenas se o QuantOcup for > 0
    if ((*sequencia).QuantOcup)
    {
        (*sequencia).Vetor[(*sequencia).inicio] = 0;

        //O novo valor de inicio sera o proximo valor a nao ser que ele ultrapasse o limite do vetor (entao sera zero)
        (*sequencia).inicio = ((*sequencia).inicio != (*sequencia).tamanho - 1)? ((*sequencia).inicio + 1) : 0;
        ((*sequencia).QuantOcup--);

        //Realiza o recomportamento do vetor a metade se chegar a um quarto do tamanho, liberando a memoria do anterior
        if (4*(*sequencia).QuantOcup <= (*sequencia).tamanho && (*sequencia).tamanho > 2)
        {
            int *temp, i;
            temp = malloc((*sequencia).tamanho/2*sizeof(int));
            for (i = (*sequencia).inicio; i % (*sequencia).tamanho != (*sequencia).fim + 1; i++)
            {
                temp[i - (*sequencia).inicio] = (*sequencia).Vetor[i % (*sequencia).tamanho];
            }
            free((*sequencia).Vetor);
            (*sequencia).Vetor = temp;
            (*sequencia).tamanho = (*sequencia).tamanho/2;
            (*sequencia).inicio = 0;
            (*sequencia).fim = (*sequencia).QuantOcup - 1;
        }

        if ((*sequencia).QuantOcup == 0) (*sequencia).fim = (*sequencia).inicio = 0;
    }
}


void PrintFirst(VetorDinamico sequencia)
{
    //Se tiver algum elemento, imprime-se o 1o
    if (sequencia.QuantOcup > 0) printf("%d\n", sequencia.Vetor[sequencia.inicio]);
}

void InsertLast(VetorDinamico *sequencia, int numero)
{
    //Caso Vetor Vazio: So adicionamos o numero ao vetor e atualizamos os parametros
    if ((*sequencia).QuantOcup == 0)
    {
        (*sequencia).Vetor[0] = numero;
        (*sequencia).QuantOcup = 1;
    }

    //Se for o 1o redimensionamento, n % 1 == 0 ===> True para todo n, entao eh necessario esse caso especifico
    else if ((*sequencia).QuantOcup == 1 && (*sequencia).tamanho == 1)
    {
        int *Temp;
        Temp = malloc(2*sizeof(int));
        Temp[0] = (*sequencia).Vetor[0];
        Temp[1] = numero;
        free((*sequencia).Vetor);
        (*sequencia).Vetor = Temp;
        (*sequencia).inicio = 0;
        (*sequencia).fim = 1;
        (*sequencia).tamanho = 2*((*sequencia).tamanho);
        ((*sequencia).QuantOcup++);
    }

    //Caso do Redimensionamento: Alto custo, dobramos o tamanho do vetor, reorganizando os elementos no novo vetor,
    //entao adicionamos novo elemento e atualizamos os parametros
    else if ((*sequencia).QuantOcup == (*sequencia).tamanho)
    {
        int *Temp;
        Temp = malloc(2*((*sequencia).tamanho)*sizeof(int));
        int i;
        for (i = (*sequencia).inicio; i % (*sequencia).tamanho != (*sequencia).fim % (*sequencia).tamanho; i++)
        {
            Temp[i-(*sequencia).inicio] = (*sequencia).Vetor[i % (*sequencia).tamanho];
        }
        Temp[i-(*sequencia).inicio] = (*sequencia).Vetor[i % (*sequencia).tamanho];
        (*sequencia).fim = (*sequencia).QuantOcup;
        Temp[(*sequencia).fim] = numero;
        free((*sequencia).Vetor);
        (*sequencia).Vetor = Temp;
        (*sequencia).tamanho = 2*((*sequencia).tamanho);
        ((*sequencia).QuantOcup++);
        (*sequencia).inicio = 0;
    }


    //Caso Geral: so fazemos a insercao tomando cuidado de nao ultrapassar o limite do vetor e atualizando as variaveis
    else
    {
        //Se o fim estiver na ultima posicao do vetor ele passa para o inicio
        if ((*sequencia).fim == (*sequencia).tamanho - 1)
        {
            (*sequencia).fim = 0;
            (*sequencia).Vetor[(*sequencia).fim] = numero;
        }

        //Caso Realmente Geral: inserimos na posicao anterior
        else
        {
            ((*sequencia).fim++);
            (*sequencia).Vetor[(*sequencia).fim] = numero;
        }
        ((*sequencia).QuantOcup++);
    }
}


void RemoveLast(VetorDinamico *sequencia)
{
    //1a exc: Vetor vazio . nao faz nada, sai da funcao
    if ((*sequencia).QuantOcup)
    {
        (*sequencia).Vetor[(*sequencia).fim] = 0;
        //O novo valor de inicio sera o proximo valor a nao ser que ele ultrapasse o limite do vetor (entao sera zero)
        (*sequencia).fim = ((*sequencia).fim != 0)? ((*sequencia).fim - 1) : (*sequencia).tamanho - 1;
        ((*sequencia).QuantOcup--);

        //Realiza o recomportamento do vetor se chegar a um quarto do tamanho, liberando a memoria do anterior
        if (4*((*sequencia).QuantOcup) <= (*sequencia).tamanho && (*sequencia).tamanho > 2)
        {
            int *temp, i;
            temp = malloc((*sequencia).tamanho/2*sizeof(int));
            for (i = (*sequencia).inicio; i % (*sequencia).tamanho != (*sequencia).fim + 1; i++)
            {
                temp[i - (*sequencia).inicio] = (*sequencia).Vetor[i % (*sequencia).tamanho];
            }
            free((*sequencia).Vetor);
            (*sequencia).Vetor = temp;
            (*sequencia).tamanho = (*sequencia).tamanho/2;
            (*sequencia).inicio = 0;
            (*sequencia).fim = (*sequencia).QuantOcup - 1;
        }

        if ((*sequencia).QuantOcup == 0) (*sequencia).fim = (*sequencia).inicio = 0;
    }
}

void PrintLast(VetorDinamico sequencia)
{
    if (sequencia.QuantOcup > 0) printf("%d\n", sequencia.Vetor[sequencia.fim]);
}

void IsEmpty(VetorDinamico sequencia)
{
    if (sequencia.QuantOcup == 0) printf("yes\n");
    else printf("no\n");
}

//Funcao de Debugging
void PrintList(VetorDinamico sequencia)
{
    int i;
    printf("\n\n  Alguns Dados: tamanho: %d; QuantoOcup: %d; inicio: %d; fim: %d \n", sequencia.tamanho, sequencia.QuantOcup, sequencia.inicio, sequencia.fim);
    if (sequencia.QuantOcup == 0) return;
    for(i = sequencia.inicio; i % sequencia.tamanho != sequencia.fim; i++)
    {
        printf("elemento na posicao %d: %d \n", (i % sequencia.tamanho), sequencia.Vetor[i % sequencia.tamanho]);
    }
    printf("Ultimo elemento: %d\n", sequencia.Vetor[i % sequencia.tamanho]);
    printf("Terminei de printar a lista\n");
}
