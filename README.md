# UTD - Projeto de Conversão de Bases com C
Universidade do Trabalho Digital - Projeto Conversor Bases com C

### Objetivo
Desenvolver um conversor de tipos de bases que suporte os tipos:
- Binário (2)
- Decimal (10)
- Hexadecimal (16)
- Octal (8)

### Autor
- [Felipe Figueiredo Bezerra](https://github.com/FigFelipe)

### Ambiente de Desenvolvimento
 - [Replit](https://replit.com/)

### Onde está o código?
- [Codigo 'main.c'](https://github.com/FigFelipe/utd-projeto-conversor-bases-c/blob/main/main.c)


## Metodologia

### Valores de Entrada

A entrada de valores deve seguir o padrão abaixo:

| Base | Sinal | Sufixo | Exemplo | Observação |
|------|-------|--------|---------|------------|
| Binária | Não | b | 0110b | Somente valores numéricos entre 0 e 1|
| Decimal | Sim | d | +25d ou -25d | O uso do sinal é obrigatório, realiza também a conversão de números negativos |
| Hexadecimal | Não | h | 109FEh | Letras devem ser maiúsculas|
| Octal | Não | o | 107o | O dígito deve conter valores entre 0 e 7  |


### Exemplos de Valores de Entrada

| Sinal | Valor | Sufixo | Descrição |
|-------|-------|--------|------------|
| + | 25 | d | Exemplo de valor positivo decimal |
| - | 25 | d | Exemplo de valor negativo decimal |
| Não tem | 0110 | b | Exemplo de valor binário |
| Não tem | 109FE | h | Exemplo de valor hexadecimal |
| Não tem | 107 | o | Exemplo de valor octal |

Digitei um valor errado com a base errada. Vou quebrar a execução do código?

> Definitivamente não. O código utiliza um validador de expressões regulares (regex), o qual aceita somente valores dentro do padrão determinado por tipo de base.


### Abstração

As funções do tipo **'MAIN'**, devem ser reutilizáveis por todos os outros métodos de conversão.

| Tipo | Origem | Destino| Expressão | Método |
|------|-----|----|---|----|
| MAIN | Decimal | Binário |  = valor [ i ] % 2| Divisão sucessiva |
| MAIN | Decimal | Octal |  = valor [ i ] % 8 | Divisão sucessiva |
| MAIN | Decimal | Hexadecimal |  = valor [ i ] % 16 | Divisão sucessiva |
| MAIN | Binário | Decimal | = valor [ i ] * 2^[ i ] | Potenciação |
| MAIN | Hexadecimal | Decimal | = valor [ i ] * 16^[ i ] | Potenciação |
| MAIN | Octal | Decimal | = valor [ i ] * 8^[ i ] | Potenciação |

Sendo definido que, a conversão é feita em 2 (duas) etapas:

>i. Na primeira conversão, é obrigatório utilizar algum tipo 'MAIN'.

>ii. Na segunda conversão, também é obrigatório o uso do tipo 'MAIN'.

### Mapa de Conversão
Abaixo é ilustrada todas as conversões de tipos possíveis (com o reuso das funções principais do tipo **'MAIN'**):

![image](https://github.com/user-attachments/assets/4fb5ba92-0550-4d3a-ab94-31a9d570c1b0)

### Exemplos
* Converter um número **Decimal** para base tipo **Binário**:
  1. Realizar a conversão **'DEC --> BIN'** (MAIN)

* Converter um número **Binário** para base tipo **Hexadecimal**:
  1. Realizar a conversão **'BIN --> DEC'** (MAIN)
  2. Realizar a conversão **'DEC --> HEX'** (MAIN)

* Converter um número **Hexadecimal** para base tipo **Octal**:
  1. Realizar a conversão **'HEX --> DEC'** (MAIN)
  2. Realizar a conversão **'DEC --> OCT'** (MAIN)

* Converter um número **Octal** para base tipo **Binário**:
  1. Realizar a conversão **'OCT --> DEC'** (MAIN)
  2. Realizar a conversão **'DEC --> BIN'** (MAIN)

## Vantagens da Abstração
* No total, são necessários 12 (doze) métodos de conversão **(100% de código)**.
* Após abstração, são necessários 6 (seis) métodos de reuso **‘MAIN’ (redução de -50% de código)**.
* Após abstração de método, são necessários somente 3 (três) métodos de conversão, e 3 (três) diferentes parâmetros de entrada **(redução de -50% código)**.
* **75%** de redução de código, e **25%** de codificação👍.

## Desvantagens da Abstração
* Aumento na dificuldade de manutenção e clareza do código.

## Afinal, usar ou não usar a abstração?
* O equilíbrio é a resposta. Um código claro e de fácil manutenção aumentam automaticamente o nível de abstração.

