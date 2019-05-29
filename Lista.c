#include <stdio.h>
#include <stdlib.h>
#include "Lista.h"

typedef struct no No;

struct lista {
	int tam;
	No * ini, * fim;
};

struct no {
	int info;
	No * prox, * ant;
};

Lista * criar() {
	Lista * l = malloc(sizeof(Lista));	
	l->tam = 0;
	l->ini = malloc(sizeof(No));
	l->fim = malloc(sizeof(No));
	l->ini->ant = NULL;
	l->ini->prox = l->fim;
	l->fim->ant = l->ini;
	l->fim->prox = NULL;
	return l;
}

void destruir(Lista * l) {
	if (l != NULL) {
		limpar(l);
		free(l->ini);
		free(l->fim);
		free(l);
	}
}

void limpar(Lista * l) {
	No * aux = l->ini->prox, * aux2;
	while(aux != l->fim) {
		aux2 = aux;
		aux = aux->prox;
		free(aux2);
	}
	l->ini->prox = l->fim;
	l->fim->ant = l->ini;
	l->tam = 0;
}

int tamanho(Lista * l) {
	return l->tam;	
}

int esta_vazia(Lista * l) {
	return tamanho(l) == 0;	
}

int ler_pos(Lista * l, int p) {
	No * aux; int i;
	
	if (p < 0 || p >= tamanho(l)) {
		
		return -1;
	}
	for (aux = l->ini->prox, i=0; i < p; i++) {
		aux = aux->prox;
	}
	return aux->info;
}

int primeiro(Lista * l) {
	return ler_pos(l, 0);
	// return l->tam != 0 ? l->ini->prox->info : -1;
}

int ultimo(Lista * l) {
	return ler_pos(l, tamanho(l)-1);
	//return l->tam != 0 ? l->fim->ant->info : -1;
}

int buscar(Lista * l, int v) {
	int p = 0;
	No * aux =  l->ini->prox;
	while(aux != l->fim) {
		if (aux->info == v) {
			return p;
		}
		aux = aux->prox;
		p++;
	}
	return -1;
	/* 
	int i;
	for (i=0; i<tamanho(l); i++) {
		if (ler_pos(i) == v) {
			return i;
		}
	}
	return -1;
	*/	
}


void escrever_pos(Lista * l, int p, int v) {
	int i;
	No * aux;
	if (p < 0 || p >= tamanho(l)) {
		return;
	}
	for (aux = l->ini->prox, i=0; i < p; i++) {
		aux = aux->prox;
	}	
	aux->info = v;
}

void inserir_pos(Lista * l, int p, int v) {
	int i, tam = tamanho(l);
	No * aux, * aux2;
	if (p < 0 || p > tam) {
		printf("Posi??o inv?lida!\n");
		return;
	}	
	aux2 = malloc(sizeof(No));
	aux2->info = v;
	for (aux = l->ini, i=0; i < p; i++) {
		aux = aux->prox;
	}	
	aux->prox->ant = aux2;
	aux2->prox = aux->prox;
	aux2->ant = aux;
	aux->prox = aux2;
	l->tam++;
}

void inserir_primeiro(Lista * l, int v) {
	//inserir_pos(l, 0, v);
	No * aux = malloc(sizeof(No));
	aux->info = v;
	aux->prox = l->ini->prox;
	aux->ant = l->ini;
	l->ini->prox = aux;
	aux->prox->ant = aux;
	l->tam++;
}


void inserir_ultimo(Lista * l, int v) {
	//inserir_pos(l, tamanho(l), v);
	No * aux = malloc(sizeof(No));
	aux->info = v;
	aux->prox = l->fim;
	aux->ant = l->fim->ant;
	l->fim->ant = aux;
	aux->ant->prox = aux;
	l->tam++;
}

int remover_pos(Lista * l, int p) {
	int i, v, tam = tamanho(l);
	No * aux = NULL, * aux2;
	if (p < 0 || p >= tam) {
		printf("Posi??o inv?lida!\n");
		return -1;
	}		
	for (aux = l->ini, i=0; i < p; i++) {
		aux = aux->prox;
	}	
	aux2 = aux->prox;
	aux->prox = aux2->prox;
	aux2->prox->ant = aux;
	v = aux2->info;
	free(aux2);
	l->tam--;
	return v;
}

int remover_primeiro(Lista * l) {
	//return remover_pos(l, 0);
	int v;
	No * aux;
	if (l->tam == 0) {
		printf("Lista vazia!\n");
		return -1;
	}		
	aux = l->ini->prox;
	l->ini->prox = aux->prox;
	aux->prox->ant = l->ini;
	v = aux->info;
	free(aux);
	l->tam--;
	return v;
}

int remover_ultimo(Lista * l) {
	//return remover_pos(l, tamanho(l)-1);	
	int i, v;
	No * aux;
	if (l->tam == 0) {
		printf("Lista vazia!\n");
		return -1;
	}		
	aux = l->fim->ant;
	l->fim->ant = aux->ant;
	aux->ant->prox = l->fim;
	v = aux->info;
	free(aux);
	l->tam--;
	return v;
}


void remover(Lista * l, int v) {
	int i, p = 0, tam = tamanho(l);
	No * aux = NULL, * aux2 =  l->ini;
	while(aux2 != NULL) {
		if (aux2->info == v) {
			break;
		}
		aux = aux2;
		aux2 = aux2->prox;
		p++;
	}
	if (aux2 == NULL) {
		return;
	}
	if (p == 0) {
		aux2 = l->ini;
		l->ini = aux2->prox;
	} else {
		for (aux = l->ini, i=0; i < p-1; i++) {
			aux = aux->prox;
		}		
		aux2 = aux->prox;
		aux->prox = aux2->prox;
	}
	if (p == tam-1) {
		l->fim = aux;
	}
	v = aux2->info;
	free(aux2);
	l->tam--;
}

