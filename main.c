#include <stdio.h>
#include <stdlib.h>
#include "Lista.h"

void imprimir(Lista * l){
	int i;
	printf(" ");
	if(tamanho(l) > 0){
		for(i = 0; i< tamanho(l); i++){
			printf("%d", ler_pos(l, i) );
		}	
	}else{
		printf("0");
	}
	printf(" ");
}
int menu()
{
  int option;
  printf("\n1.Definir o valor do operando 1\n2. Definir o valor do operando 2\n3. Mostrar o resultado da soma\n4. Mostrar o resultado do produto\n5. Sair do programa.\n");
  printf(" => ");
  scanf("%d", &option);
  while (option < 1 || option > 5)
  {
    printf("-- Opcao invalida! Digite a opcao novamente --\n");
    scanf("%d", &option);
  }
  return option;
}
void removerExeption(Lista * l){
	while(primeiro(l) == 0 && tamanho(l) > 1){
		remover(l, 0);
	}
}

Lista *handleStringToList(char *v1)
{
  Lista *l = criar();
  int i;
  for (i = 0; *(v1 + i) != '\0'; i++)
  {
    if (*(v1 + i) == '0')
    {
      inserir_ultimo(l, 0);
    }
    else if (*(v1 + i) == '1')
    {
      inserir_ultimo(l, 1);
    }
    else if (*(v1 + i) == '2')
    {
      inserir_ultimo(l, 2);
    }
    else if (*(v1 + i) == '3')
    {
      inserir_ultimo(l, 3);
    }
    else if (*(v1 + i) == '4')
    {
      inserir_ultimo(l, 4);
    }
    else if (*(v1 + i) == '5')
    {
      inserir_ultimo(l, 5);
    }
    else if (*(v1 + i) == '6')
    {
      inserir_ultimo(l, 6);
    }
    else if (*(v1 + i) == '7')
    {
      inserir_ultimo(l, 7);
    }
    else if (*(v1 + i) == '8')
    {
      inserir_ultimo(l, 8);
    }
    else if (*(v1 + i) == '9')
    {
      inserir_ultimo(l, 9);
    }
  }
  return l;
}

Lista *somar(Lista *a, Lista *b)
{
  Lista *lSomar = criar();
  int tamA = tamanho(a), tamB = tamanho(b);
  int i, resto = 0, v, soma;
  for (i = 0; i < tamA || i < tamB; i++)
  {
    int A = i < tamA ? ler_pos(a, tamA - 1 - i) : 0;
    int B = i < tamB ? ler_pos(b, tamB - 1 - i) : 0;
    soma = v = A + B + resto;
    if (v >= 10)
    {
      v = v % 10;
      resto = 1;
    }
    else
    {
      resto = 0;
    }
    inserir_primeiro(lSomar, v);
  }

  if (resto > 0)
  {
    inserir_primeiro(lSomar, v);
  }

  if (tamA == 0 && tamB == 0)
  {
    inserir_primeiro(lSomar, 0);
  }

  return lSomar;
}
Lista *multiplicar(Lista *a, Lista *b)
{
  Lista *lMulti = criar();
  int tamA = tamanho(a), tamB = tamanho(b), i, j;
  if (tamA == 0 || tamB == 0)
  {
    inserir_primeiro(lMulti, 0);
  }
  int v, multi, resto = 0;
  for (i = 1; i <= tamA; i++)
  {
    Lista *aux = criar();
    int count = 1;
    //Inserindo os 0
    while (count != i)
    {
      inserir_primeiro(aux, 0);
      count++;
    }
    for (j = 1; j <= tamB; j++)
    {
      multi = v = (ler_pos(a, tamA - i) * ler_pos(b, tamB - j)) + resto;

      if (v >= 10)
      {
        v = multi % 10;
        resto = (multi - v) / 10;
      }
      else
      {
        resto = 0;
      }

      inserir_primeiro(aux, v);
    }
    if (resto > 0)
    {
      inserir_primeiro(aux, resto);
    }
    lMulti = somar(lMulti, aux);
    destruir(aux);
    resto = 0;
  }

  return lMulti;
}
int main(int argc, char *argv[])
{
  int option = menu(), soma, mult;
  char *v1 = malloc(5000), *v2 = malloc(5000);
  Lista *l1 = criar(), *l2 = criar(), *lSoma, *lMult;
  while (option != 5)
  {
    switch (option)
    {
    case 1:
    {
      system("cls");
      printf("Numero 1 =");
      imprimir(l1);
      printf("Numero 2 = ");
      imprimir(l2);
      printf("\n\n");
      printf(" => ");
      scanf("%s", v1);
      l1 = handleStringToList(v1);
      removerExeption(l1);
      option = menu();
      break;
    }
    case 2:
    {
      system("cls");
      printf("Numero 1 =");
      imprimir(l1);
      printf("Numero 2 = ");
      imprimir(l2);
      printf("\n\n");
      printf(" => ");
      scanf("%s", v2);
      l2 = handleStringToList(v2);
      removerExeption(l2);
      option = menu();
      break;
    }
    case 3:
    {
      system("cls");
      imprimir(l1);
      printf("+");
      imprimir(l2);
      printf("\n");
      printf("\n => A soma e: ");
      lSoma = somar(l1, l2);
      imprimir(lSoma);
      printf("\n");
      option = menu();
      break;
    }
    case 4:
    {
      system("cls");
      
      imprimir(l1);
      printf("x");
      imprimir(l2);
      printf("\n");
      printf("\n => A multiplicacao e: ");
      lMult = multiplicar(l1, l2);
      imprimir(lMult);
      printf("\n");
      option = menu();
      break;
    }
    default:
      break;
    }
  }
  destruir(l1);
  destruir(l2);
  destruir(lSoma);
  destruir(lMult);
  system("pause");
  return 0;
}
