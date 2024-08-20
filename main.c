#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <regex.h>

// Variáveis globais
char valor[33] = ""; // Vetor de entrada de dados do usuario
int bitVaiUm = 0;
bool isValorNegativo = false;

// Padrões REGEX
char *padraoBinario = "^[01]*b$";
char *padraoDecimal = "^[+-][0-9]*[0-9]d$";
char *padraoHexadecimal = "^[0-9A-F]*h$";
char *padraoOctal = "^[0-7]*o$";

// Tipo do valor informado pelo usuario
bool isTipoBinario = false;
bool isTipoDecimal = false;
bool isTipoHexadecimal = false;
bool isTipoOctal = false;

// Vetores de conversao
char vetorBinario[63];
char vetorDecimal[63];
char vetorHexadecimal[63];
char vetorOctal[63];
char vetorNegativo[63];


bool ValidaInformacao(char *padrao, char *tipo)
{
  regex_t regex; // Instancia um novo objeto regex_t

  int expressao = regcomp(&regex, padrao, REG_EXTENDED);

  if(expressao)
  {
    fprintf(stderr, "\n--> Não foi possível compilar a expressão regular!");

    return false;
  }
  else
  {
    expressao = regexec(&regex, valor, 0, NULL, 0);

    if(!expressao)
    {
      //printf("\n    Informação válida como... %s!", tipo);

      return true;

    }
    else if(expressao == REG_NOMATCH)
    {
      //printf("\n    Informação inválida como... %s!", tipo);

      return false;
    }
    else
    {
      char mensagemErro[100];

      regerror(expressao, &regex, mensagemErro, sizeof(mensagemErro));

      fprintf(stderr, "\n--> Erro na correspondência regex: %s", mensagemErro);

      return false;
    }

  }

  regfree(&regex);
}


int SomaBinariaMaisUm(int numero)
{
  int resultado = 0;

  if(bitVaiUm == 0)
  {
    if(numero == 0) //(0 + 1)
    {
      bitVaiUm = 9;
      return resultado = 1;
    }
    else //(1 + 1)
    {
      bitVaiUm = 1;
      return resultado = 0;
    }
  }
  else if(bitVaiUm == 1)
  {
    if(numero == 0) //(1 + 0)
      {
        bitVaiUm = 9;
        return resultado = 1;
      }
      else //(1 + 1)
      {
        bitVaiUm = 1;
        return resultado = 0;
      }
  }
  else
  {
    return numero;  
  }

}

// Funções principais de conversão 'MAIN'
void ConversorAnyToDec(int base)
{
  long resultado = 0;
  long resultadoAcumulado = 0;
  int valorConvertido = 0;
  int indice = 0;

  int vetorAux[63];

  printf("\n\n-----------------------------------------------");     
  printf("\n\n-->  Convertendo base '(%i)' para Decimal...\n", base);

  // Percorre o vetor de entrada de dados
  for(int i=0; i<64; i++)
  {
    // Manter somente a parte numérica
    // Comparação no formato 'char'
    if(valor[i] == 'b' || valor[i] == 'h' || valor[i] == 'o')
    {
      indice = i;
      vetorAux[i] = 0;
    }
    else if(valor[i] == '\0')
    {
      vetorAux[i] = 0;
    }
    else
    {
      // Converter 'char' para 'inteiro'
      valorConvertido = valor[i] - '0';

      // Validação de valores em base no tipo
      if(isTipoBinario)
      {
        // Mantem somente valores 'zero' ou 'um'
        // Comparação de valor numérico
        if(valorConvertido != 0 && valorConvertido != 1)
        {
          valorConvertido = 0;
        }
      }

      // Validação de valores em base no tipo
      if(isTipoHexadecimal && valorConvertido >= 17 && valorConvertido < 23)
      {
        // 17 == A  
        // 18 == B  
        // 19 == C  
        // 20 == D
        // 21 == E  
        // 22 == F

        valorConvertido -= 7; // Ajuste de offset
      }

      // Validação de valores em base no tipo
      if(isTipoOctal)
      {

      }

      vetorAux[i] = valorConvertido;

    }

    // Atualiza o valor do vetor correspondente
    vetorDecimal[i] = vetorAux[i];

  }

  // Com base no indice encontrado anteriormente,
  // realiza o calculo de conversão

  indice -= 1; // Ajuste do indice

  for(int i=0; i<64; i++)
  {
    if(indice >= 0)
    {
      // Calcula a conversão para 'decimal'
      resultado = vetorAux[i] * pow(base, indice);

      // Armazena a soma dos resultados da conversão
      resultadoAcumulado += resultado;

      printf("\n    [%i]  %i * (%i^%i) = %li", i, vetorAux[i], base, indice, resultado);

      indice--;
    }

  }

  // Exibe o valor de resultado da conversão
  printf("\n\n    Resultado: '%s' = '%lid'", valor, resultadoAcumulado);

  // Atribui o resultado ao vetorDecimal[]
  // convertendo 'long' em 'string'
  sprintf(vetorDecimal, "%ld", resultadoAcumulado);

}

void ConversorDecToAny(int base)
{
  long valorConvertido = 0;
  int dividendo = 0;
  int restoDivisao = 0;
  
  int indice = 0;
  int indiceAux = 0;
  int indiceBaseOctal = 0;
  int indiceBaseHexadecimal = 0;

  long resultado = 0;
  long resultadoAcumulado = 0;

  char vetorAux[63];

  printf("\n\n-----------------------------------------------");     
  printf("\n\n-->  Convertendo Decimal para a base '(%i)'...\n", base);

  if(valor[0] == '-')
  {
    isValorNegativo = true;
  }


  // 1. Obter somente a parte numérica do vetor
  for(int i=0; i<63; i++)
  {

    //printf("\n    [%i]  %c", i, vetorDecimal[i]);

    // Remove o caracter 'd' do vetor
    if(vetorDecimal[i] == 'd')
    {
      vetorDecimal[i] = '\0';
    }

  }

  // Converter 'string' para 'inteiro'
  valorConvertido = atoi(vetorDecimal);

  // 2. Exibe o resultado numérico da conversão 'string' para 'inteiro'
  printf("\n-->  O valor da conversão 'string' é: %li\n", valorConvertido);

  // 3. Se o valor convertido for negativo
  if(valorConvertido < 0)
  {
    valorConvertido *= -1; // Torna-lo um valor positivo
  }

  dividendo = valorConvertido;

  // 4. Realiza a conversão para a base informada
  for(int j=0; j<64; j++)
  {

    if(dividendo > 0)
    {
      // Calculo para a conversão binária
      restoDivisao = dividendo % base;

      // Se o valor for um numero negativo
      if(isValorNegativo == true)
      {
        // Inverter valores
        if(restoDivisao == 0)
        {
          restoDivisao = 1;

        }
        else
        {
          restoDivisao = 0;
        }

        if(base == 2)
        {
          restoDivisao = SomaBinariaMaisUm(restoDivisao);

          printf("\n    INV+1 [%i]  %i %% %i = %i", j, dividendo, base, restoDivisao);

          dividendo = dividendo / base;

          vetorAux[j] = restoDivisao + '0';

          vetorDecimal[j] = vetorAux[j];

          vetorNegativo[j] = vetorAux[j];

        }

        if(base == 8)
        {

          if(vetorNegativo[j] == '\0')
          {
            vetorNegativo[j] = 1 + '0'; // Converte 'int' para 'char'
          }

          // Converter 'char' para 'int'
          vetorNegativo[j] = vetorNegativo[j] - '0';
          
          // Realiza o calculo para conversao 'octal'
          resultado = vetorNegativo[j] * pow(2, indiceBaseOctal);
          
          printf("\n    [%i] %i * (%i^%i) = %li", j, vetorNegativo[j], 2, indiceBaseOctal, resultado);

          indiceBaseOctal++;
          resultadoAcumulado += resultado;

          if(indiceBaseOctal > 2)
          {
              printf("  --> Acumulado: %li", resultadoAcumulado);
              vetorOctal[indiceAux] = resultadoAcumulado;
            
              indiceBaseOctal = 0;
              resultadoAcumulado = 0;

              indiceAux++;
          }

        }

        if(base == 16)
        {
            // Realiza o calculo para conversao 'octal'
            resultado = vetorNegativo[j] * pow(2, indiceBaseHexadecimal);

            printf("\n    [%i] %i * (%i^%i) = %li", j, vetorNegativo[j], 2, indiceBaseHexadecimal, resultado);

            indiceBaseHexadecimal++;
            resultadoAcumulado += resultado;

            if(indiceBaseHexadecimal > 3)
            {
                printf("  --> Acumulado: %li", resultadoAcumulado);

                if(resultadoAcumulado > 9)
                {
                  switch(resultadoAcumulado)
                  {
                    case 10:
                      vetorHexadecimal[indiceAux] = 'A';
                      break;

                    case 11:
                      vetorHexadecimal[indiceAux] = 'B';
                      break;

                    case 12:
                      vetorHexadecimal[indiceAux] = 'C';
                      break;

                    case 13:
                      vetorHexadecimal[indiceAux] = 'D';
                      break;

                    case 14:
                      vetorHexadecimal[indiceAux] = 'E';
                      break;

                    case 15:
                      vetorHexadecimal[indiceAux] = 'F';
                      break;
                    
                  }
                }
                else
                {
                  vetorHexadecimal[indiceAux] = resultadoAcumulado + '0';
                }

                indiceBaseHexadecimal = 0;
                resultadoAcumulado = 0;

                indiceAux++;
            }
        }

      }
      else // Se o valor for um numero positivo
      {
        printf("\n    [%i]  %i %% %i = %i", j, dividendo, base, restoDivisao);

        dividendo = dividendo / base;

        if(base == 2)
        {
          vetorAux[j] = restoDivisao + '0';
          vetorBinario[j] = vetorAux[j];
        }
        else if(base == 8)
        {

          vetorAux[j] = restoDivisao + '0'; // Converter 'int' para 'char'
          vetorOctal[j] = vetorAux[j];

        }
        else if(base == 16)
        {
          if(restoDivisao <= 9)
          {
            vetorAux[j] = restoDivisao + '0';
            vetorHexadecimal[j] = vetorAux[j];

          }
          else
          {
            switch(restoDivisao)
            {
              case 10:
                vetorAux[j] = 'A'; // Converte 'int' para 'char'
                break;

              case 11:
                vetorAux[j] = 'B'; // Converte 'int' para 'char'
                break;

              case 12:
                vetorAux[j] = 'C'; // Converte 'int' para 'char'
                break;

              case 13:
                vetorAux[j] = 'D'; // Converte 'int' para 'char'
                break;

              case 14:
                vetorAux[j] = 'E'; // Converte 'int' para 'char'
                break;

              case 15:
                vetorAux[j] = 'F'; // Converte 'int' para 'char'
                break;
            }

            // Atribui o resultado ao vetor correspondente
            vetorHexadecimal[j] = vetorAux[j];

          }


        }


      }


      indice++;

    }
    else // Preenche obrigatoriamente o restante do vetor com o valor 'zero'
    {

      if(base == 2)
      {
        if(isValorNegativo)
        {
          vetorBinario[j] = 1;

          printf("\n    INV+1 [%i]  %i", j, vetorBinario[j]);

        }
        else
        {
          vetorBinario[j] = 0;

          printf("\n    [%i]  %i", j, vetorBinario[j]);

        }

      }
      else if(base == 8)
      {
        vetorOctal[j] = 0;
      }
      else if(base == 16)
      {
        vetorHexadecimal[j] = 0;
      }

    }



  }

  // 5. Exibe os resultados da conversao
  //printf("\n\n    Resultado (ordem errada): %s", vetorAux);

  // Exibe uma resposta customizada
  // somente para valores negativos
  if(isValorNegativo)
  {
    if(base == 8)
    {
      printf("\n\n    Resultado '%s' = '", valor);

      // No tamanho de uma resposta de 64bits
      // 64 % 3 = 1
      // portanto, o ultimo valor, do bit 63
      // é adicionado manualmente
      printf("%i ", vetorNegativo[63]);

      int indiceEspaco = 1;
      
      for(int i=indiceAux-1; i>=0; i--)
      {
        printf("%i", vetorOctal[i]);

        if(indiceEspaco == 3 && i != 0)
        {
          printf(" ");
          indiceEspaco = 0;
        }

        indiceEspaco++;
        
      }

      printf("o'");
      
    }
    else if(base == 16)
    {
      printf("\n\n    Resultado '%s' = '", valor); 
      
      for(int i=indiceAux; i>=0; i--)
      {
        printf("%c", vetorHexadecimal[i]);   
      }

      printf("h'");
    }
    
  }
  else // Exibe o resultado para valores positivos
  {
    indice += -1; // ajuste do indice

    //printf("\n\nIndice: %i", indice);

    printf("\n\n    Resultado '%s' = '", valor);

    // 6. Resultado na ordem correta
    for(int i=indice; i>=0; i--)
    {
       printf("%c", vetorAux[i]);     
    }

    switch(base)
    {
      case 2:
        printf("b'");
        break;

      case 16:
        printf("h'");
        break;

      case 8:
        printf("o'");
        break;
    }
    
  }



  
}

void AtribuiVetor(int base)
{
  for(int i=0; i<64; i++)
  {
     switch(base)
     {
        case 2:
          vetorBinario[i] = valor[i];
          break;

       case 10:
          vetorDecimal[i] = valor[i];
          break;

       case 16:
          vetorHexadecimal[i] = valor[i];
          break;

       case 8:
           vetorOctal[i] = valor[i];
           break;
     }
  }
}

// Função que verifica o tipo do número informado
void VerificaTipo()
{
  system("clear"); // Limpa o console
  printf("\n--> Detectando o tipo para o valor... '%s'\n", valor);  

  isTipoBinario = ValidaInformacao(padraoBinario, "Binario");
  isTipoDecimal = ValidaInformacao(padraoDecimal, "Decimal");
  isTipoHexadecimal = ValidaInformacao(padraoHexadecimal, "Hexadecimal");
  isTipoOctal = ValidaInformacao(padraoOctal, "Octal");

  if(isTipoBinario)
  {
    printf("\n--> O valor informado é um número binário!");

    // Realiza a atribuição do vetor correspondente
    AtribuiVetor(2);

    // 'MAIN': BIN --> DEC
    ConversorAnyToDec(2);

    // BIN --> HEX
    // 1. BIN --> DEC
    // 2. DEC --> HEX
    ConversorDecToAny(16);

    // BIN --> OCT
    // 1. BIN --> DEC
    // 2. DEC --> OCT
    ConversorDecToAny(8);

  }
  else if(isTipoDecimal)
  {
    printf("\n--> O valor informado é um número decimal!");

    // Realiza a atribuição do vetor correspondente
    AtribuiVetor(10);

    // 'MAIN': DEC --> BIN
    ConversorDecToAny(2);

    // 'MAIN': DEC --> OCT
    ConversorDecToAny(8);

    // 'MAIN': DEC --> HEX
    ConversorDecToAny(16);

  }
  else if(isTipoHexadecimal)
  {
    printf("\n--> O valor informado é um número hexadecimal!");

    // Realiza a atribuição do vetor correspondente
    AtribuiVetor(16);

    // 'MAIN': HEX --> DEC
    ConversorAnyToDec(16);

    // HEX --> BIN
    // 1. HEX --> DEC
    // 2. DEC --> BIN
    ConversorDecToAny(2);

    // HEX --> OCT
    // 1. HEX --> DEC
    // 2. DEC --> OCT
    ConversorDecToAny(8);

  }
  else if(isTipoOctal)
  {
    printf("\n--> O valor informado é um número octal!"); 

    // Realiza a atribuição do vetor correspondente
    AtribuiVetor(8);

    // 'MAIN': OCT --> DEC
    ConversorAnyToDec(8);

    // OCT --> BIN
    // 1. OCT --> DEC
    // 2. DEC --> BIN
    ConversorDecToAny(2);

    // OCT --> HEX
    // 1. OCT --> DEC
    // 2. DEC --> HEX
    ConversorDecToAny(16);

  }
  else
  {
    printf("\n\n--> O valor é inválido, tente novamente.");
  }

}

int main(void) {

  // 1. Calculadora IMC
  //CalculadoraIMC();

  // 2. Exemplo While
  //CalculadoraMedias();

  // 3. Vetores
  //ExemploVetores();
  //ContarVogais();

  // 4. Potenciação
  //Potenciacao();

  // Projeto - Conversor de numero Decimal para Bin
  printf("\n --- Exemplos de Formatos de Entrada ---");

  printf("\n\n --> BINÁRIO (base 2): '0011b'");
  printf("\n    * No final, é obrigatorio usar o sufixo [b]!");

  printf("\n\n --> DECIMAL (base 10): '+25d' ou '-25d'");
  printf("\n    * No início, é obrigatorio usar um sinal (+) ou (-)!");
  printf("\n    * No final, é obrigatorio usar o sufixo [d]!");

  printf("\n\n --> HEXADECIMAL (base 16): '109AFh'");
  printf("\n    * Letras devem ser MAIUSCULAS.");
  printf("\n    * No final, é obrigatorio usar o sufixo [h]!");

  printf("\n\n --> OCTAL (base 8): '123o'");
  printf("\n    * No final, é obrigatorio usar o sufixo letra [o]!");

  printf("\n\n-----------------------------------------------");     
  printf("\n\nInforme um valor à ser convertido (com sinal e/ou sufixo): ");
  scanf("%s", &valor);


  VerificaTipo();

  return 0;
}

