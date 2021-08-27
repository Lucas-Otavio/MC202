#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
Objetivo: Organizar e Manipular uma agenda de contatos
Entrada: Letra representando operacao:
i -> Inserir um contato novo, seguido de Nome, Endereco, Telefone e Data de nascimento
p -> Imprimir os contatos
b -> Realizar uma busca, seguido do pedaco de nome que se deseja encontrar
r -> Remover um contato, seguido do nome exato que se deve retirar
f -> Finalizar o programa

Situacao atual:
Funcionam bem as funcoes de impressao, insercao, busca, remocao e finalizacao
*/


/*
* Um struct que permite a manipulacao de todos os dados de maneira eficiente
* nome, endreco e telefone se referem as proprias variaveis definidas pelo enunciado
* data eh uma string que contem os numeros de dia, mes e ano separados por "/"
* available revela se aquela posicao da lista esta sendo usada (1 se sim; do contrario, nao)
*/

struct contato
{
  int available;
  char nome[51];
  char endereco[101];
  char telefone[13];
  char data[9];
};

//Declaracao das funcoes
void print(struct contato[1000]);
void inserir(struct contato agenda[1000]);
void busca(struct contato agenda[1000]);
void remover(struct contato agenda[1000]);

int main()
{
  //Inicializacao das variaveis, considerando todos os contatos da agenda nao utilizados
  char ordem;
  int i;
  struct contato agenda[1000];
  for(i = 0; i < 1000; i++) agenda[i].available = 0;

  //Loop que permite a execucao ate a finalizacao
  scanf("%c", &ordem);
  while(ordem !=  'f')
    {
    if (ordem == 'i') inserir(agenda);
    else if (ordem == 'p') print(agenda);
    else if (ordem == 'b') busca(agenda);
    else if (ordem == 'r') remover(agenda);
    scanf("%c", &ordem);
    }
  return 0;
}

void print(struct contato agenda[1000])
  {
  //Impressao contato a contato, tomando cuidado com o caso de nenhum contato
  int i;
  printf("%s\n", "Listagem:");
  for(i = 0; i < 1000; i++)
    {
    if (agenda[i].available == 1) printf("(%d) %s	%s	%s	%s\n", (i+1), agenda[i].nome, agenda[i].endereco, agenda[i].telefone, agenda[i].data);
    else if(i == 0 && agenda[i].available == 0) printf("Nenhum contato.\n");
    else break;
    }
  printf("\n");
  }

void inserir(struct contato agenda[1000])
  {
  //Index diz a posicao onde o novo contato deve ser salvo
  int i, index = 0;
  for(i = 0; i < 1000; i++)
    {
    if(agenda[i].available == 0)
      {
      agenda[i].available = 1;
      index = i;
      break;
      }
    }

  //Encontrada a posicao, basta adicionar caracteristica a caracteristica
  scanf(" %[^\n]\n", agenda[index].nome);
  scanf(" %[^\n]\n", agenda[index].endereco);
  scanf("%s\n", agenda[index].telefone);
  scanf("%s\n", agenda[index].data);

  printf("Contato para %s inserido.\n\n", agenda[index].nome);
}

void busca(struct contato agenda[1000])
{
  int i;
  char nome[51];
  int* index;
  int len = 1;
  //Procuro os indices em que aparece o segmento do nome e salvo em index usando alocacao de memoria dinamica
  index = (int *) malloc(sizeof(int));
  index[0] = -1;
  scanf(" %[^\n]\n", nome);

  for (i = 0; i < 1000; i++)
    {
    if (agenda[i].available == 0) break;
    else if (strstr(agenda[i].nome, nome))
      {
      index[len-1] = i;
      index = (int*) realloc((void*) index,(++len)*sizeof(int));
      index[len-1] = -1;
      }
    }


  //Impressao dos Contatos encontrados a partir de index
  if (index[0] == -1) printf("%s\n", "Resultado da busca:\nNenhum contato.\n");
  else
    {
    printf("%s\n", "Resultado da busca:");
    for(i = 0; i < len; i++)
      {
      if (index[i] == -1) break;
      else printf("(%d) %s	%s	%s	%s\n\n", (index[i]+1), agenda[index[i]].nome, agenda[index[i]].endereco, agenda[index[i]].telefone, agenda[index[i]].data);
      }
    }
  free(index);
  }

void remover(struct contato agenda[1000])
  {
  char nome[51];
  int i,j;
  int *index, cont, KeyLen, ContatosSalvos = 0;
  cont = 0;
  scanf("%s\n", nome);
  KeyLen = strlen(nome);

  //Novamente, salvo em index os indices na Agenda dos contatos que correspondem exatamente ao nome desejado usando alocacao de memoria dinamica
  index = (int *) malloc(sizeof(int));
  index[0] = -1;

  for (i = 0; i < 1000; i++)
      {
      if (agenda[i].available == 0) break;
      else
        {
        ContatosSalvos++;
        int len, Found = 1;
        len = strlen(agenda[i].nome);
        if (len != KeyLen) continue;

        //Para Identificar se realmente correspondem, percorro caracter a caracter, quando as strings tem igual tamanho
        for(j = 0; j < len; j++)
          {
          if (agenda[i].nome[j] != nome[j])
            {
            Found = 0;
            break;
            }
          }
        if (Found)
          {
          index[cont] = i;
          index = (int*) realloc((void*) index,(++cont + 1)*sizeof(int));
          index[cont] = -1;
          }
        }
      }

    /*
    Achados os indices, os removo, empurrando a lista ate que apenas os primeiros indices sejam ocupados, tomando cuidado com available
    Shift conta quantas casas devem ser puladas, ultrapasso o tamanho do vetor com os dados para poder reinicializar as variaveis ja usadas
    */
  printf("Contatos de %s removidos: %d.\n\n",nome, cont);
  int shift = 0;
  for(i = 0; i < ContatosSalvos + cont; i++)
    {
    if(i == index[shift]) shift++;
    else if (shift > 0 && i < ContatosSalvos)
      {
      strcpy(agenda[i - shift].nome, agenda[i].nome);
      strcpy(agenda[i - shift].endereco, agenda[i].endereco);
      strcpy(agenda[i - shift].telefone, agenda[i].telefone);
      strcpy(agenda[i - shift].data, agenda[i].data);
      }
    else if (shift > 0 && i >= ContatosSalvos)
      {
      agenda[i-shift].nome[0] = '\0';
      agenda[i-shift].endereco[0] = '\0';
      agenda[i-shift].telefone[0] = '\0';
      agenda[i-shift].data[0] = '\0';
      agenda[i-shift].available = 0;
      }
    }

  free(index);
  }
