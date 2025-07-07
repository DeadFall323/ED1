#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/checkin.h"
#include "../headers/eventos.h"
#include "../headers/atividades.h"
#include "../headers/participantes.h"

// --------------------------------------
// Função: inicializarFila
// Objetivo: Inicializa a fila de check-in, definindo início e fim como NULL
// --------------------------------------
void inicializarFila(Fila *fila) {
    fila->inicio = NULL;
    fila->fim = NULL;
}

// --------------------------------------
// Função: enfileirar
// Objetivo: Insere um participante no final da fila de check-in
// --------------------------------------
void enfileirar(Fila *fila, Participante *p) {
    NoFila *novo = (NoFila *)malloc(sizeof(NoFila));
    novo->participante = p;
    novo->prox = NULL;

    if (fila->fim == NULL) {
        // Fila vazia: o novo nó será o primeiro
        fila->inicio = novo;
        fila->fim = novo;
    } else {
        // Fila já tem elementos: adiciona ao final
        fila->fim->prox = novo;
        fila->fim = novo;
    }
}

// --------------------------------------
// Função: desenfileirar
// Objetivo: Remove o participante que está no início da fila
// --------------------------------------
void desenfileirar(Fila *fila) {
    if (fila->inicio == NULL) {
        printf("Fila vazia!\n");
        return;
    }

    NoFila *temp = fila->inicio;

    // Exibe quem está sendo removido da fila
    printf("Removendo da fila: %s - %s\n", temp->participante->nome, temp->participante->matricula);

    // Atualiza o ponteiro de início para o próximo da fila
    fila->inicio = fila->inicio->prox;

    // Se a fila ficou vazia após a remoção, zera o fim também
    if (fila->inicio == NULL) {
        fila->fim = NULL;
    }

    free(temp);  // Libera memória do nó removido
}

// --------------------------------------
// Função: listarFila
// Objetivo: Mostra todos os participantes atualmente na fila
// --------------------------------------
void listarFila(Fila *fila) {
    NoFila *aux = fila->inicio;

    if (aux == NULL) {
        printf("Fila vazia.\n");
        return;
    }

    printf("Fila de check-in:\n");

    // Percorre a fila e exibe os dados de cada participante
    while (aux != NULL) {
        printf("Nome: %s | Matrícula: %s | E-mail: %s\n",
               aux->participante->nome,
               aux->participante->matricula,
               aux->participante->email);
        aux = aux->prox;
    }
}
