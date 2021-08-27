#include <stdio.h>
#include <stdlib.h>
#include "lists.h"

//Cria a Lista Encadeada, com n adequado e count = 0
void CreateList(int size, Node* head)
{
    Node* p = head;
    int i;
    p->n = 1;
    p->count = 0;
    for(i = 1; i < size; i++)
    {
        p->next = malloc(sizeof(Node));
        p = p->next;
        p->n = i + 1;
        p->count = 0;
    }
    p->next = 0x0;
}

//Funcao para ajudar o processo de debbuging
void PrintList(Node* p)
{
    if (p->next)
    {
        printf("%d\t%d\n", p->n, p->count);
        PrintList(p->next);
    }
    else printf("%d\t%d\n", p->n, p->count);
    //printf("Printei!");
}

//Destroi a Lista Encadeada, liberando toda a memoria
void ObliterateList(Node** p)
{
    Node* ptr;
    if (*p)
    {
        ptr = *p;
        *p = (*p)->next;
        free(ptr);
    }
}

//Realiza o Move To Front, contando em cont os acessos a lista
int MTF(Node** head, int* requests, int NumRequest)
{
    int cont = 0;
    int i;
    Node* ptr, *ptraux;

    //Devemos achar a busca e mover o encontrado para o inicio
    for(i = 0; i < NumRequest; i++)
    {
        ptr = *head;

        //1a exc: Se a busca ja ta no inicio, so atualizamos o contador
        if (ptr->n == requests[i]) cont++;

        //Encontra-se a posicao e faz a troca
        else
        {
            while(ptr->next->n != requests[i])
            {
                ptr = ptr->next;
                cont++;
            }
            cont = cont + 2;
            ptraux = ptr->next;
            ptr->next = ptr->next->next;
            ptr = *head;
            *head = ptraux;
            ptraux->next = ptr;
        }
    }
    return cont;
}

//Realiza o TransPoSe, contando em cont os acessos a lista
int TPS(Node** head, int* requests, int NumRequest)
{
    int cont = 0;
    int i;
    Node *ptr, *ptraux;

    for(i = 0; i < NumRequest; i++)
    {
        ptr = *head;

        //1a exc: se busca esta em head, so atualiza o contador
        if (ptr->n == requests[i]) cont++;

        else if (ptr->next)
        {
            //2a exc: se esta na 2a posicao, eh necessario mudar a head
            if (ptr->next->n == requests[i])
            {
                cont = cont + 2;
                *head = ptr->next;
                ptr->next = ptr->next->next;
                (*head)->next = ptr;
            }


            //Caso Geral: achamos a posicao do busca e movemos ele uma posicao para frente
            else
            {
                while(ptr->next->next->n != requests[i])
                {
                    ptr = ptr->next;
                    cont++;
                }
                cont = cont + 3;
                ptraux = ptr->next->next;
                ptr->next->next = ptraux->next;
                ptraux->next = ptr->next;
                ptr->next = ptraux;
            }
        }
    }
    return cont;
}

//Realiza o CouNT, contanto em cont os acessos a lista
int CNT(Node** head, int* requests, int NumRequest)
{
    int cont = 0;
    int i;
    Node *ptr, *ptraux;

    /*
    A estrategia principal utilizada se baseou em um caso geral:
    ptraux->next->next eh o destino do node buscado e ptr->next eh o node buscado,
    ptraux se localizaria antes da margem entre dois numeros de counts

    Entao, a troca de posicao eh realizada, a variavel count do Node eh atualizada,
    assim como o contador de operacoes (cont) sofre mais algumas atualizacoes

    Entretanto, existem muitas excecoes (na verdade a maior parte das vezes as excecoes sao usadas)
    Elas normalmente ocorrem por posicoes anomalas do ptraux e ptr e pela influencia de head
    */
    for(i = 0; i < NumRequest; i++)
    {
        ptraux = *head;
        ptr = *head;
        int continua = 1; //variavel de controle, ela indica se a busca deve continuar ou nao

        //1a exc: Se a busca for o 1o termo, podemos ter pouco trabalho
        if(ptr->n == requests[i])
        {
            ((*head)->count)++;
            cont++;
            continua = 0;
        }

        //Enquanto o count observado nao mudar estaremos nesse loop, ele existe para atender a 2a exc.
        else if(ptr->count == ptr->next->count)
        {
            while(ptr->count == ptr->next->count)
            {
                //2a exc: busca e head tem o mesmo valor de count
                if(ptr->next->n == requests[i])
                {
                    continua = 0;
                    Node *p = ptr->next;
                    ptr->next = ptr->next->next;
                    p->next = *head;
                    *head = p;
                    ((*head)->count)++;
                    cont = cont + 2;
                    break;
                }
                cont++;
                ptr = ptr->next;
            }
        }

        //Devemos continuar a busca se ainda nao foi encontrada a busca
        if (continua)
        {
            while(ptr->next)
            {
                if(ptr->next->n == requests[i])
                {
                    //3a exc: nao eh preciso deslocamento
                    if (ptr->count > (ptr->next->count + 1))
                    {
                        (ptr->next->count++);
                        cont = cont + 2;
                    }

                    //ptr e ptraux estao adjacentes
                    else if(ptraux->next->n == ptr->n)
                    {
                        //4a exc: ptraux esta em head e a busca vai ocupar seu lugar
                        if(ptraux == *head && ptraux->count == ptr->next->count + 1)
                        {
                            Node *p = ptr->next;
                            ptr->next = p->next;
                            p->next = *head;
                            *head = p;
                            (p->count)++;
                        }

                        //5a exc: ptr e ptraux estao adjacentes, por isso a padrao de reogarnizacao geral nao funciona
                        else
                        {
                            Node *p;
                            p = ptr->next;
                            ptr->next = p->next;
                            ptraux->next = p;
                            p->next = ptr;
                            (p->count)++;
                        }
                        cont = cont + 2;
                    }

                    //6a exc: o 2o elemento ja eh o buscado, isso afeta o padrao de mudanca de posicao do caso geral
                    else if (ptr == ptraux)
                    {
                        *head = ptr->next;
                        ptr->next = (*head)->next;
                        (*head)->next = ptr;
                        ((*head)->count)++;
                        cont = cont + 2;
                    }

                    //Esse eh o caso geral
                    else
                    {


                        //7a exc: inserindo no inicio, quando ptr e ptraux nao estao adjacentes
                        if((*head)->count == ptr->next->count + 1)
                        {
                            Node *p = ptr->next;
                            ptr->next = p->next;
                            p->next = *head;
                            *head = p;
                            (p->count)++;
                        }

                        //8a exc: a insercao eh na 2a posicao
                        else if(*head == ptraux && ptr->next->count + 1 == ptraux->next->count)
                        {
                            Node *p = ptr->next;
                            ptr->next = p->next;
                            p->next = ptraux->next;
                            ptraux->next = p;
                            (p->count)++;
                        }

                        //Caso Geral
                        else
                        {
                            Node *p = ptr->next;
                            ptr->next = p->next;
                            p->next = ptraux->next->next;
                            ptraux->next->next = p;
                            (p->count)++;
                        }
                        cont = cont + 2;
                    }
                    break;
                }

                ptr = ptr->next;
                cont++;
                Node *livre = ptraux;

                //Atualiza o valor do ptraux para evitar percorrer a lista verdadeiramente 2 vezes
                while(livre != ptr || livre->next == ptr || livre->next->next == ptr)
                {
                    if (livre->next->next->count >= ptr->next->count + 1 && livre->next->next->count != livre->next->count) ptraux = livre;
                    if (livre->next->next->count == ptr->next->count + 1) break;
                    livre = livre->next;
                }
            }
        }
    }
    return cont;
}
