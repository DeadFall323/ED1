#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/desfazer.h"

void inicializarPilha(NoPilha **topo) {
    *topo = NULL;
}

void empilhar(NoPilha **topo, char tipo[], char nome[], char infoExtra[]) {
    NoPilha *novo = (NoPilha *)malloc(sizeof(NoPilha));
    strcpy(novo->tipo, tipo);
    strcpy(novo->nome, nome);
    strcpy(novo->infoExtra, infoExtra);
    novo->prox = *topo;
    *topo = novo;
}

void desempilhar(NoPilha **topo) {
    if (*topo == NULL) {
        printf("Pilha vazia, nada para desfazer.\n");
        return;
    }

    NoPilha *temp = *topo;
    printf("Desfazendo remoção de %s: %s\n", temp->tipo, temp->nome);
    *topo = temp->prox;
    free(temp);
}

void listarPilha(NoPilha *topo) {
    if (topo == NULL) {
        printf("Pilha vazia.\n");
        return;
    }
    printf("Pilha de operações:\n");
    NoPilha *aux = topo;
    while (aux != NULL) {
        printf("[%s] Nome: %s | Info Extra: %s\n", aux->tipo, aux->nome, aux->infoExtra);
        aux = aux->prox;
    }
}
