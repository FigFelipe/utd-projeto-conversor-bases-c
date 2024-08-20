void CalculadoraIMC()
{
  float altura;
  char sexo;
  float IMC;
  
  // Entrada de dados
  printf("Digite a altura (em metros): ");
  scanf("%f", &altura);

  printf("Digite o sexo (M/F): ");
  scanf(" %c", &sexo);

  // Processamento
  if(sexo == 'f' || sexo == 'F')
  {
    IMC = (62.1 * altura) - 44.7;

    // Saída de dados
    printf("\n[Feminino] Seu IMC é: %.2f", IMC);
  }
  else if(sexo == 'm' || sexo == 'M')
  {
    IMC = (72.7 * altura) - 58;

    // Saída de dados
    printf("\n[Masculino] Seu IMC é: %.2f", IMC);
  }
  else
  {
    printf("\nSexo inválido!");
  }
}