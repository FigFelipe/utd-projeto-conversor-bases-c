#include <stdlib.h>

void CalculadoraMedias()
{
    int qtdNotas = 0;
    float nota = 0;
    float media = 0.0;
    
    printf("Informe a qtd de notas à inserir: ");
    scanf("%i", &qtdNotas);

    if(qtdNotas > 0)
    {
        for(int i=0; i<qtdNotas; i++)
        {
            do
            {
                printf("\nInforme a nota número %i: ", i+1);
                scanf("%f", &nota);

                // Se a nota for negativa
                if(nota < 0)
                {
                    // Limpa o console, porém antes adicione <stdlib.h>
                    system("clear");
                    printf("\nO valor da nota deve ser positivo\n");
                }
                else if(nota > 10)
                {
                    system("clear");
                    printf("\nO valor da nota deve ser <= 10.\n");
                }
                
            }while(nota < 0 || nota > 10);

            // Soma acumulativa da nota
            nota += nota;
        }

        // Calcula a média das notas
        media = nota / qtdNotas;

        printf("\nA média das nota(s) é: %.2f", media);
    }
    else
    {
        printf("\nQuantidade de notas inválida!");
    }
  
}