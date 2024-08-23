#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <regex.h>

char valorInformado[32] = "";
int bitVaiUm = 0;


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

void ConversorBinToDec()
{
  int indiceSufixo = 0;
  int resultado = 0;
  long somatorio = 0;

  printf("\n\n --- Conversor Binário para Decimal ---\n");

  // Remover o caractere 'b'
  for(int i=0; i<32; i++)
  {
    if(valorInformado[i] == 'b')
    {
      indiceSufixo = i-1;
      valorInformado[i] = '\0';
    }

    //printf("\n[%i] %c", i, valorInformado[i]);    
  }

  for(int j=0; j<32; j++)
  {
    if(valorInformado[j] == '\0')
    {
      break;
    }

    // Converte char para int
    int valorConvertido = valorInformado[j] - '0';

    resultado = valorConvertido * pow(2, indiceSufixo);

    somatorio += resultado; // somatorio = somatorio + resultado

    printf("\n[%i] %c * (2^%i) = %i", j, valorInformado[j], indiceSufixo--, resultado);
  }

  printf("\n\n--> Resultado: '%s' binário = '%li' decimal.", valorInformado, somatorio);
  printf("\n");

}

void ConversorDecToBin(long numeroBaseDecimal)
{
  long numero = numeroBaseDecimal;

  int vetorBinario[64];
  int vetorBinarioInvertido[64];

  int vetorBinarioMaisUm[64];

  long resultadoDivisao = 0;
  long restoDivisao = 0;

  int indiceVetor = 0;

  if(numeroBaseDecimal < 0) // Numero negativo
  {
      numeroBaseDecimal = numeroBaseDecimal * (-1);
      printf("\n--> Detectado número negativo, convertendo-o para positivo... '[%i]'\n", numeroBaseDecimal);

  }

  // Realizar sucessivas divisões por 2
  printf("\n--> Realizando a conversão decimal para binário...");
  while(numeroBaseDecimal > 0)
  {
    restoDivisao = numeroBaseDecimal % 2;

    printf("\n    [%i] %li % 2 = %li", indiceVetor, numeroBaseDecimal, restoDivisao);

    numeroBaseDecimal = numeroBaseDecimal / 2;
    vetorBinario[indiceVetor] = restoDivisao;
    indiceVetor++;

  }

  printf("\n\n--> Preenchendo o restante do vetor com valor 'zero'...");

  // Preencher com valor '0' os bits restantes do long
  for(int i=indiceVetor; i<64; i++)
  {
      vetorBinario[i] = 0;

      printf("\n    [%i] %i", i,                 
      vetorBinario[i]);
  }

  // Exibe a resposta da conversão binária em ordem natural
  printf("\n\n--> ERRADO - Ordem natural (binário):    ");

  for(int i=0; i<=7; i++)
  {
      if(i == 4)
      {
        printf(" ");
      }

      printf("%i", vetorBinario[i]);
  }

  // Exibe a resposta da conversão binária em ordem inversa
  printf("\n--> CORRETO - Ordem invertida (binário): ");

  for(int j=7; j>=0; j--)
  {
    if(j == 3)
    {
      printf(" ");
    }

    printf("%i", vetorBinario[j]);    
  }


  if(numero < 0)
  {
      // Aplicavel somente no caso de número negativo
      printf("\n\n--- Aplicável somente para números negativos ---");
      printf("\n--> Preenchendo o vetor original com valores invertidos...");

      //1. Preencher o vetor original com valores invertidos
      for(int j=0; j<64; j++)
      {
        if(vetorBinario[j] == 0)
        {
          vetorBinarioInvertido[j] = 1;
        }
        else
        {
          vetorBinarioInvertido[j] = 0;
        }

        printf("\n    [%i] %i", j, vetorBinarioInvertido[j]);

      }

      // 2. Preenche o vetor invertido com a soma binária 'complemento de um'
      printf("\n\n--> Preenchendo o vetor invertido + 1 (soma binária)...");

      for(int k=0; k<64; k++)
      {
        vetorBinarioMaisUm[k] = SomaBinariaMaisUm(vetorBinarioInvertido[k]);
        printf("\n    [%i] %i", k, vetorBinarioMaisUm[k]);
      }

      // 3. Exibir os 8 primeiros bits da conversão realizada
      // Exibe a resposta da conversão binária em ordem natural
      printf("\n\n--> ERRADO - Ordem natural (binário):    ");

      for(int x=0; x<8; x++)
      {
          if(x == 4)
          {
            printf(" ");
          }

          printf("%i", vetorBinarioMaisUm[x]);
      }

      // Exibe a resposta da conversão binária em ordem inversa
      printf("\n--> CORRETO - Ordem invertida (binário): ");

      for(int y=7; y>=0; y--)
      {
        if(y == 3)
        {
          printf(" ");
        }

        printf("%i", vetorBinarioMaisUm[y]);    
      }
  }

}

void isValorTipoDecimal()
{
  bool isValido = false;
  bool isVetorBinario = false;
  int indiceSufixo = 0;
  int valorNumerico = 0;

  // https://regex101.com/
  // ^ : Indica o inicio da string
  // [+-]: permite que o primeiro caractere seja + ou -
  // [0-9]+: o primeiro caractere após o simbolo deve ser numérico
  // d$: o ultimo caractere deve ser b ou d

  char *padraoDecimal = "^[+-][0-9]*[0-9]d$";

  regex_t regex;

  // Avaliando a entrada com expressão regular
  // <regex.h>

  // Compila a expressão regular, tem o tipo de retorno int
  int expressaoDecimal = regcomp(&regex, padraoDecimal, REG_EXTENDED);

  if(expressaoDecimal)
  {
    fprintf(stderr, "\n--> Não foi possível compilar a expressão regular 'Decimal'.");
  }
  else
  {
    // Executa o regex de correspondencia com o valor de entrada informada
    expressaoDecimal = regexec(&regex, valorInformado, 0, NULL, 0);

    // Se a expressão regular corresponder
    if(!expressaoDecimal)
    {
      printf("\n--> O valor informado é válido como 'Decimal.'");

      // Retornar somente a parte numérica
      // 1. Substituir o caractere 'd' por '\0'
      for(int i=0; i<=10; i++)
      {
        if(valorInformado[i] == 'd') 
        {
          valorInformado[i] = '\0';
        }
      }

      // Convertendo o string para int
      long numeroConvertido = atoi(valorInformado);

      // Prevenir o overflow
      if(numeroConvertido > 2147483647)
      {
        numeroConvertido = 2147483647;
      }
      else if(numeroConvertido < -2147483648)
      {
        numeroConvertido = -2147483648;
      }

      printf("\n\n--> O valor 'Decimal' convertido é: %li", numeroConvertido);
      printf("\n");

      // Realiza a chamada da função de conversão para Binário
      ConversorDecToBin(numeroConvertido);

    }
    else if(expressaoDecimal == REG_NOMATCH) // Se a expressão não corresponder
    {
      printf("\n--> O valor informado é inválido como 'Decimal'.");
    }
    else
    {
      char mensagemErro[100] = "";

      regerror(expressaoDecimal, &regex, mensagemErro, sizeof(mensagemErro));

      fprintf(stderr, "\n--> Erro na correspondência regex: %s", mensagemErro);

    }

    // Libera o stream regex da memória alocada
    regfree(&regex);
  }

}

void isValorTipoBinario()
{
  bool isValido = false;
  bool isVetorBinario = false;
  int indiceSufixo = 0;
  int valorNumerico = 0;

  // https://regex101.com/
  // ^ : Indica o inicio da string
  // [+-]?: permite que o primeiro caractere seja + ou -
  // [0-9]+: o primeiro caractere após o simbolo deve ser numérico
  // [bd]$: o ultimo caractere deve ser b ou d

  char *padraoBinario = "^[01]*b$";

  regex_t regex;

  // Avaliando a entrada com expressão regular
  // <regex.h>

  // Compila a expressão regular, tem o tipo de retorno int
  int expressaoBinaria = regcomp(&regex, padraoBinario, REG_EXTENDED);
  //int expressaoDecimal = regcomp(&regex, padraoDecimal, REG_EXTENDED);

  if(expressaoBinaria)
  {
    fprintf(stderr, "\n--> Não foi possível compilar a expressão regular 'Binaria'.");
  }
  else
  {
    // Executa o regex de correspondencia com o valor de entrada informada
    expressaoBinaria = regexec(&regex, valorInformado, 0, NULL, 0);

    // Se a expressão regular corresponder
    if(!expressaoBinaria)
    {
      printf("\n--> O valor informado é válido como 'Binário'.");

      // Realiza a chamada da função de conversão para 'Decimal'
      ConversorBinToDec();

    }
    else if(expressaoBinaria == REG_NOMATCH) // Se a expressão não corresponder
    {
      printf("\n--> O valor informado é inválido como 'Binário'.");
    }
    else
    {
      char mensagemErro[100] = "";

      regerror(expressaoBinaria, &regex, mensagemErro, sizeof(mensagemErro));

      fprintf(stderr, "\n--> Erro na correspondência regex: %s", mensagemErro);

    }

    // Libera o stream regex da memória alocada
    regfree(&regex);
  }

}


// Função que verifica se o numero é binário ou decimal
void VerificaTipo()
{
  isValorTipoBinario();
  isValorTipoDecimal();
}

int main(void) {

  // Projeto - Conversor de numero Decimal para Bin
  printf("\n --- Formatos de entrada ---");
  printf("\n\n --> Decimal:");
  printf("\n    * No início, é obrigatorio usar um sinal (+) ou (-)!");
  printf("\n    * No final, é obrigatorio usar o sufixo [d]!");
  printf("\n\n     Exemplo: +25d ou -25d.");


  printf("\n\n --> Binário:");
  printf("\n    * No final, é obrigatorio usar o sufixo [b]!");
  printf("\n\n     Exemplo: 0011b.");

  printf("\n\n-----------------------------------------------");     
  printf("\n\nInforme um número (binário ou decimal): ");
  scanf("%s", &valorInformado);

  printf("\n-----------------------------------------------\n");     

  VerificaTipo();

  return 0;
}

