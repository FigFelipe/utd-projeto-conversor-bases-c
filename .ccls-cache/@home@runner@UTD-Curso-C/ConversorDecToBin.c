void ConversorDecToBin()
{
  int numeroBaseDecimal = 0;

  printf("Informe um número (base 10): ");
  scanf("%i", &numeroBaseDecimal);

  ConversorBinario(numeroBaseDecimal);

}

void ConvesorBinario(int numeroBaseDecimal)
{
  int vetorBinario[] = {};
  int resultadoDivisao = 0;
  int restoDivisao = 0;

  int aux = 0;

  // Realizar divisões sucessivas por 2
  while(numeroBaseDecimal > 0)
  {

    numeroBaseDecimal = numeroBaseDecimal / 2;
    restoDivisao = numeroBaseDecimal % 2;

    vetorBinario[aux] = restoDivisao;

    aux++;
  }

  for(int i=0; i<aux; i++)
  {
     printf("%i", vetorBinario[i]);   
  }

}
