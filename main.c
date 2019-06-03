#include <stdio.h>
#include <stdlib.h>
#include "Lista.h"

void clonarl(Lista * a, Lista * b){
  limpar(b);
  int tamA = tamanho(a);
  if(tamA != 0){
    int i;
    for(i =0; i< tamA; i++){
      inserir_ultimo(b, ler_pos(a, i));
    }
  }
}

void imprimir(Lista *l){
  int i;
  printf(" ");
  if (tamanho(l) > 0)
  {
    for (i = 0; i < tamanho(l); i++)
    {
      printf("%d", ler_pos(l, i));
    }
  }
  else
  {
    printf("0");
  }
  printf(" ");
}
int menu(){
  int option;
  printf("\n1.Definir o valor do operando 1\n2. Definir o valor do operando 2\n3. Mostrar o resultado da soma\n4. Mostrar o resultado do produto\n5. Sair do programa.\n");
  printf(" => ");
  scanf("%d", &option);
  while (option < 1 || option > 5){
    printf("-- Opcao invalida! Digite a opcao novamente --\n");
    scanf("%d", &option);
  }
  return option;
}

void checkingForLetters(char * v){
  char ns[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
  int isLetters = 1;
  int i, j;
  for(i = 0; *(v+i) != '\0'; i++ ){
    for(j = 0; j < 10; j++){
      if(*(v+i) == ns[j]){
        break;
      }
    }
    
    if( j == 10 ){
      printf("-- Apenas numeros, digite novamente --\n => ");
      scanf("%s", v);
      i = -1;
    }
  }
}

void handleStringToList(char *v1, Lista *l){
  limpar(l);
  char ns[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
  int ni[10] = { 0, 1,2, 3, 4, 5, 6,7, 8, 9 };
  int chave = 0;
  int i, j;
  for (i = 0; *(v1 + i) != '\0'; i++){

    if( *(v1 + i) != '0' || chave == 1 || *(v1 + i + 1) == '\0' ){
      chave = 1;
      for( j = 0; j < 10; j++ ){
        if(*(v1 + i) == ns[j] ){
          inserir_ultimo(l, ni[j]);
        }
      }
    } 
  }
}

void somar(Lista *a, Lista *b, Lista * lSomar){
  limpar(lSomar);
  int tamA = tamanho(a), tamB = tamanho(b);
  int i, resto = 0, v, soma;
  for (i = 0; i < tamA || i < tamB; i++){
    int A = i < tamA ? ler_pos(a, tamA - 1 - i) : 0;
    int B = i < tamB ? ler_pos(b, tamB - 1 - i) : 0;
    soma = v = A + B + resto;
    if (v >= 10){
      v = v % 10;
      resto = 1;
    }
    else{
      resto = 0;
    }
    inserir_primeiro(lSomar, v);
  }

  if (resto > 0){
    inserir_primeiro(lSomar, 1);
  }

  if (tamA == 0 && tamB == 0){
    inserir_primeiro(lSomar, 0);
  }
}
void multiplicar(Lista *a, Lista *b, Lista * lMult){
  limpar(lMult);
  int tamA = tamanho(a), tamB = tamanho(b), i, j;
  if (tamA == 0 || tamB == 0 || ( tamA == 1 && primeiro(a) == 0 ) || ( tamB == 1 && primeiro(b) == 0 )  ) {
    inserir_primeiro(lMult, 0);
  }else{
    int v, multi, resto = 0;
    for (i = 1; i <= tamA; i++){
    Lista *aux = criar();
    int count = 1;
    //Inserindo os 0
    if(ler_pos(a, tamA - i) != 0 ){
    	while (count != i){
        inserir_primeiro(aux, 0);
        count++;
    	}
      for (j = 1; j <= tamB; j++){
        multi = v = (ler_pos(a, tamA - i) * ler_pos(b, tamB - j)) + resto;
        if (v >= 10){
          v = multi % 10;
          resto = (multi - v) / 10;
        }
        else{
          resto = 0;
        }
      inserir_primeiro(aux, v);
      }		
    }else{
		  inserir_primeiro(aux, 0);
	  }
    
    if (resto > 0){
      inserir_primeiro(aux, resto);
    }
    Lista * auxSoma = criar();
    somar(lMult, aux, auxSoma);
    clonarl(auxSoma, lMult);
    destruir(auxSoma);
    destruir(aux);
    resto = 0;
    }
  }
}
int main(int argc, char *argv[])
{
  int option = menu(), soma, mult;
  char *v1 = malloc(5000), *v2 = malloc(5000);
  Lista *l1 = criar(), *l2 = criar(), *lSoma = criar(), *lMult = criar();
  
  while (option != 5)
  {
    switch (option){
    case 1:{
      system("cls");
      printf("Numero 1 =");
      imprimir(l1);
      printf("Numero 2 = ");
      imprimir(l2);
      printf("\n\n");
      printf(" => ");
      scanf("%s", v1);
      checkingForLetters(v1);
      handleStringToList(v1, l1);
      option = menu();
      break;
    }
    case 2:{
      system("cls");
      printf("Numero 1 =");
      imprimir(l1);
      printf("Numero 2 = ");
      imprimir(l2);
      printf("\n\n");
      printf(" => ");
      scanf("%s", v2);
      checkingForLetters(v2);
      handleStringToList(v2, l2);
      option = menu();
      break;
    }
    case 3:{
      system("cls");
      imprimir(l1);
      printf("+");
      imprimir(l2);
      printf("\n");
      printf("\n => A soma e: ");
      somar(l1, l2, lSoma);
      imprimir(lSoma);
      printf("\n");
      option = menu();
      break;
    }
    case 4:{
      system("cls");
      imprimir(l1);
      printf("x");
      imprimir(l2);
      printf("\n");
      printf("\n => A multiplicacao e: ");
      multiplicar(l1, l2, lMult);
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
