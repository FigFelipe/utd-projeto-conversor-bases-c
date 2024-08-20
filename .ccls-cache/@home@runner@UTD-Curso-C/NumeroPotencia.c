#include <math.h>

void Potenciacao() 
{
  int expoente = 0;
  float base = 0.0;
  float resultado = 0.0;

  printf("Informe o numero de base: ");
  scanf("%f", &base);

  printf("Informe o numero do expoente: ");
  scanf("%i", &expoente);

  resultado = pow(base, expoente);

  printf("Resultado: %.2f", resultado);
  
}