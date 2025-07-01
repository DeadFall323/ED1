#include <stdio.h>
#include <stdlib.h>
#include "../headers/checkin.h"

// Inicializa a fila de check-in
void inicializarFila(Fila *fila) {
    fila->inicio = NULL;
    fila->fim = NULL;
}

// Adiciona um participante real (já cadastrado) na fila
void enfileirar(Fila *fila, Participante *p) {
    NoFila *novo = (NoFila *)malloc(sizeof(NoFila));
    novo->participante = p; // Armazena o ponteiro do participante real
    novo->prox = NULL;

    if (fila->fim == NULL) {
        fila->inicio = novo;
        fila->fim = novo;
    } else {
        fila->fim->prox = novo;
        fila->fim = novo;
    }
}

// Remove o primeiro da fila
void desenfileirar(Fila *fila) {
    if (fila->inicio == NULL) {
        printf("Fila vazia!\n");
        return;
    }

    NoFila *temp = fila->inicio;
    printf("Removendo da fila: %s - %s\n", temp->participante->nome, temp->participante->matricula);

    fila->inicio = fila->inicio->prox;
    if (fila->inicio == NULL) {
        fila->fim = NULL;
    }

    free(temp);
}

// Lista os participantes presentes na fila de check-in
void listarFila(Fila *fila) {
    NoFila *aux = fila->inicio;
    if (aux == NULL) {
        printf("Fila vazia.\n");
        return;
    }

    printf("Fila de check-in:\n");
    while (aux != NULL) {
        printf("Nome: %s | Matrícula: %s | E-mail: %s\n",
               aux->participante->nome,
               aux->participante->matricula,
               aux->participante->email);
        aux = aux->prox;
    }
}
