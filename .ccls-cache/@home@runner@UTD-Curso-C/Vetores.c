#include <stdio.h>
#include <stdlib.h>

void ExemploVetores()
{
    int numeros[5];
    char nome[5]={'t', 'e', 's', 't', 'e'};

    for(int i=0; i<5; i++)
    {
      printf("Informe o char %i: ", i+1);
      scanf(" %c", &nome[i]);
      
    }
}