#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define quad(x) ((x)*(x))


int main()
{
    //Inicializo as variaveis
    int i, j, tam, num;
    double **Matriz, media, desvio;

    //Comeco a formar a matriz
    scanf("%d ", &tam);
    Matriz = calloc(tam, sizeof(double*));
    media = 0.0; desvio = 0.0;
    num = (tam * (tam + 1))/2;

    //Leio elemento a elemento da matriz, enquanto calculo a media
    for(i = 0; i < tam; i++)
    {
        Matriz[i] = calloc(i+1, sizeof(double));
        for(j = 0; j < i + 1; j++)
        {
            scanf("%lf", &Matriz[i][j]);
            media = (double) (media + Matriz[i][j]);
        }
    }
    media = media/num;

    //Tendo calculado a media, vejo qual eh o desvio padrao
    for(i = 0; i < tam; i++)
    {
        for(j = 0; j <= i ; j++)
        {
            desvio = desvio + pow(media - Matriz[i][j], 2);
        }
    }
    desvio = sqrt(desvio/num);


    //Entao, imprimo o devido valor calculado a partir da media e do desvio padrao, liberando a memoria em sequencia
    for(i = 0; i < tam; i++)
    {
        for(j = 0; j <= i; j++)
        {
            printf("%.12lf ", ((Matriz[i][j] - media)/desvio));
        }
        printf("\n");
        free(Matriz[i]);
    }

    //Finalmente, libero a memoria dos vetor principal e imprimo a media e o desvio padrao
    free(Matriz);
    printf("\n%.12lf %.12lf \n", media, desvio);

    return 0;
}
