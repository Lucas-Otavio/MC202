#include <stdio.h>

/*
Objetivo: Estimar o tempo de espera de clientes em uma fila de acordo com o momento de chegada,
tempo necessario para resolver o problema e o numero de atendentes;
Entrada: Uma linha com o numero de A atendentes e C clientes, seguida de C linhas com
o momento de chegada e o tempo gasto;
Saida: Media de tempo de espera e quantidade de clientes que tiveram que esperar mais de 10 mins
Estrategia: Tenho uma lista com o momento em que cada atendente vai ficar livre,
a cada iteracao eu recebo os dados do proximo cliente e o direciono para ultima atendente livre
(ou mais proxima disso) mais proxima do fim da lista, com isso consigo estimar o tempo de espera.

*********Futuro: Houve problema no caso de teste 18. Tenho que tentar descobrir o que houve de errado.
*/

int main() {
  //Inicializacao das variaveis
  int atend, clientes, chegada, tempoGasto, mais10 = 0, atraso = 0, min = 0;
  float Sespera = 0.0;
  int i, j;

  //Leitura da primeira linha seguida de inicializacao da lista de atendentes
  scanf("%d %d", &atend, &clientes);
  int caixas[atend];
  for(i = 0; i < atend; i++)
  {
      caixas[i] = 0;
  }
  
  
  
  
  for(i = 0; i < clientes; i++)
  {
    // A cada iteracao eu leio os dados do proximo cliente e encontro o proximo atendente livre
    scanf("%d %d", &chegada, &tempoGasto);
    
    min = 0;
    for(j = 0; j < atend; j++)
    {
        if (caixas[j] < caixas[min]) min = j;
    }
    
    
    /*
    Se o proximo atendente esta livre antes do proximo cliente chegar, ele eh atendido.
    Do contrario, ele computa o atraso: a diferenca entre o momento em que o proximo atendente
    vai ficar livre e o momento de chegada do cliente.
    A partir disso, acumulamos o atraso e contamos a quantidade de clientes que esperou demais da conta.
    */
    if (caixas[min] <= chegada) caixas[min] = chegada;
    else
    {
      atraso = caixas[min] - chegada;
      Sespera += atraso;
      
      if (atraso > 10) mais10++;
    }
    
    caixas[min] += tempoGasto;
  }
  
  
  
  //Calculo a media e imprimo a saida
  float media = Sespera/clientes;
  printf("Espera media para %d clientes: %.1f minutos\n", clientes, media);
  printf("Numero de clientes que esperaram mais que 10 minutos: %d\n", mais10);
  return 0;
}
