#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/checkin.h"

void inicializarFila(Fila *fila) {
    fila->inicio = NULL;
    fila->fim = NULL;
}

void enfileirar(Fila *fila, char nome[], char matricula[]) {
    NoFila *novo = (NoFila *)malloc(sizeof(NoFila));
    strcpy(novo->nome, nome);
    strcpy(novo->matricula, matricula);
    novo->prox = NULL;

    if (fila->fim == NULL) {
        fila->inicio = novo;
        fila->fim = novo;
    } else {
        fila->fim->prox = novo;
        fila->fim = novo;
    }
}

void desenfileirar(Fila *fila) {
    if (fila->inicio == NULL) {
        printf("Fila vazia!\n");
        return;
    }

    NoFila *temp = fila->inicio;
    printf("Removendo: %s - %s\n", temp->nome, temp->matricula);
    fila->inicio = fila->inicio->prox;

    if (fila->inicio == NULL) {
        fila->fim = NULL;
    }

    free(temp);
}

void listarFila(Fila *fila) {
    NoFila *aux = fila->inicio;
    if (aux == NULL) {
        printf("Fila vazia.\n");
        return;
    }
    printf("Fila de check-in:\n");
    while (aux != NULL) {
        printf("Nome: %s | Matrícula: %s\n", aux->nome, aux->matricula);
        aux = aux->prox;
    }
}
