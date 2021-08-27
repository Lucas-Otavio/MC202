#include <stdio.h>

int main ()
{
    //Inicializado variaveis de controle e de loops e matriz
    int n, m, r, s;
    int i, j, k, l;
    scanf("%d %d %d %d", &n, &m, &r, &s);
    int M[n][m];
    
    //Recebendo a matriz
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            int ent;
            scanf("%d", &ent);
            M[i][j] = ent;
        }
    }
    
    
    int maxi = 0, sum = 0;
    /*
    //Tentando descobrir a resposta do problema testando todas as possibilidades
    for(i = 0; i <= n-r; i++)
    {
        for(j = 0; j <= m-s; j++)
        {
            //printf("%d %d\n", i,j);
            sum = 0;
            for(k = i; k < i+r; k++)
            {
                for(l = j; l < j+s; l++)
                {
                    sum += M[k][l];
                    //printf("\t%d %d\n", k,l);
                }
            }
            //Conferindo se foi encontrada uma resposta maior
            maxi = sum > maxi? sum : maxi;
        }
    }
    */
    int Sums[n-r+1][m-s+1];
    for(i = 0; i < n; i++)
    {
        int acum = 0;
        for(int z = 0; z < s; z++)
        {
            acum += M[i][z];
        }
        Sums[i][0] = acum;
        for(j = s; j < m; j++)
        {
            acum = acum - M[i][j-s] + M[i][j];
            Sums[i][j-1] = acum;
        }

    }

    for(j = 0; j <= m-s+1;j++)
    {
        int acum = 0;
        for(int z = 0; z < r; z++)
        {
            acum += Sums[z][j];
        }
        maxi = acum > maxi? acum : maxi;
        for(i = r; i < n; i++)
        {
            acum = acum - Sums[i-r][j] + Sums[i][j];
        }
        maxi = acum > maxi? acum : maxi;
    }
    
    printf("%d", maxi);
    
    return 0;
}