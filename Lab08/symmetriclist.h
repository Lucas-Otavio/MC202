#ifndef SYMMETRICLISTH
#define SYMMRTRICLISTH

//Struct Node:
//Contem o no com seu double e seus apontadores para os nos adjacentes.
//Quando na ponta, um dos ponteiros se refere ao NULL
typedef struct Node
{
    double num;
    struct Node *a, *b;
} Node;


//Struct DummyNode:
//Facilita o trabalho com ponteiros por meio de nos sentinelas
//Usando eles como nos, nao eh preciso guardar ponteiros mas sim os nos em si
typedef struct DummyNode
{
    Node *b;
} DummyNode;

//Struct SymmetricList:
//Guarda o inicio, o fim e o tamanho da lista
//Dessa forma, eh preciso passa menos parametros e casos de excecao sao facilitados ou deixam de existir
typedef struct SymmetricList
{
    DummyNode head;
    DummyNode tail;
    int size;
} SymmetricList;


//Declaracao das funcoes
void Insert(SymmetricList*);
void Print(SymmetricList);
void Revert(SymmetricList*);
void Destroy(SymmetricList*);

#endif
