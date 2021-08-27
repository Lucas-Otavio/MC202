#ifndef SEQUENCIASH
#define SEQUENCIASH

//Um struct para manipular vetores dinamicos, esses inteiros facilitam as operacoes
//Eh uma memoria que vale a pena sacrificar
typedef struct VetorDinamico
{
    int *Vetor;
    int inicio;
    int fim;
    int QuantOcup; //Refere-se a quantidade de posicoes ocupadas do vetor
    int tamanho;
} VetorDinamico;

void IsEmpty(VetorDinamico);

int InsertFirst(VetorDinamico*, int);
void RemoveFirst(VetorDinamico*);
void PrintFirst(VetorDinamico);

void InsertLast(VetorDinamico*, int);
void RemoveLast(VetorDinamico*);
void PrintLast(VetorDinamico);

void PrintList(VetorDinamico);

#endif // SEQUENCIASH
