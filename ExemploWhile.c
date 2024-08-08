#include <stdio.h>

void ExemploWhile ()
{
    int i = 1;
    
    while (i <= 5)
    {
        printf("%d\n", i);
        i++;
    }
}

void ExemploFor()
{
    printf("FOR:");
    for(int i=0; i<5; i++)
    {
        printf("%d\n", i);
    }
}
