void ContarVogais()
{
  char vogais[5] = {'a', 'e', 'i', 'o', 'u'};
  
  char palavraInformada[50] = "";

  int qtdLetras = 0;
  
  int qtdVogais = 0;
  int qtdConsoantes = 0;

  int qtdVogalA = 0;
  int qtdVogalE = 0;
  int qtdVogalI = 0;
  int qtdVogalO = 0;
  int qtdVogalU = 0;

  printf("Informe uma palavra (max. 50 letras): ");
  scanf(" %s", &palavraInformada);

  tolower(palavraInformada);
  
  qtdLetras = strlen(palavraInformada);
  
  printf("\nQtd de letras: %i", qtdLetras);

  // Percorre o laço de acordo com a qtd de letras informadas
  for(int i=0; i < qtdLetras; i++)
  {
    
    // Percorre o vetor de vogais
    // comparando a letra informada
    // com cada elemento do vetor (não recomendo kkk)
    for(int j=0; j<5; j++)
    {
      if(palavraInformada[i] == vogais[0])
      {
        qtdVogalA++;
        break;
      }
      else if(palavraInformada[i] == vogais[1])
      {
        qtdVogalE++;
        break;
      }
      else if(palavraInformada[i] == vogais[2])
      {
        qtdVogalI++;
        break;
      }
      else if(palavraInformada[i] == vogais[3])
      {
        qtdVogalO++;
        break;
      }
      else if(palavraInformada[i] == vogais[4])
      {
        qtdVogalU++;
        break;
      }

    }
    
  }

  qtdVogais = qtdVogalA + qtdVogalE + qtdVogalI + qtdVogalO + qtdVogalU;

  qtdConsoantes = qtdLetras - qtdVogais;

  if(qtdConsoantes < 0)
  {
    qtdConsoantes += qtdConsoantes * (-1);
  }
  if(qtdVogais < 0)
  {
    qtdVogais += qtdVogais * (-1);
  }

  printf("\nQtd de consoantes: %i", qtdLetras - qtdVogais);
  printf("\nQtd de vogais: %i", qtdVogais);

  printf("\n\nQtd de vogal 'a': %i", qtdVogalA);
  printf("\nQtd de vogal 'e': %i", qtdVogalE);
  printf("\nQtd de vogal 'i': %i", qtdVogalI);
  printf("\nQtd de vogal 'o': %i", qtdVogalO);
  printf("\nQtd de vogal 'u': %i", qtdVogalU);
  
}