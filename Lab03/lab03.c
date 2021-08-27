#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
    int i,j,k;
    int numFrases, numKeys;
    int cont = 0;
    while(scanf("%d %d", &numKeys, &numFrases)!= EOF)
    {
        cont++;
        char Frases[numFrases][100];
        char FrasesOriginais[numFrases][100];
        char Keys[numKeys][100];
        int Contador[numFrases];
        int PioresDesculpas[numFrases];
        
        for(i = 0; i < numKeys; i++)
        {
            scanf("%s\n", Keys[i]);
        }
        
        for(i = 0; i < numFrases; i++)
        {
            scanf("%[^\n]\n", FrasesOriginais[i]);
            for(j = 0; j < 100; j++) Frases[i][j] = tolower(FrasesOriginais[i][j]);
            Contador[i] = 0;
            PioresDesculpas[i] = 0;
        }
        
        for(i = 0; i < numFrases; i++)
        {
            
            for(j = 0; j < numKeys; j++)
            {
                char * chrptr = Frases[i];
                while(strstr(chrptr,Keys[j]) != NULL) {
                    Contador[i] += 1;
                    chrptr = strstr(chrptr,Keys[j]) + sizeof(char);
                }
            }
        }
        
        
        int maior = 0;
        for(i = 0; i < numFrases; i++)
        {
            if(Contador[maior] < Contador[i]) maior = i;
        }
        
        
        for(i = 0; i < numFrases; i++)
        {
            if(Contador[maior] == Contador[i]) PioresDesculpas[i] = 1;
        }
        
        printf("Conjunto de desculpas #%d\n", cont);
        for(i = 0; i < numFrases; i++)
        {
            if(PioresDesculpas[i] == 1)
            {
                printf("%s\n", FrasesOriginais[i]);
            }
        }
        printf("\n");
    }

    return 0;
}