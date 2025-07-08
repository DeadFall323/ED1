#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/checkin.h"
#include "../headers/eventos.h"
#include "../headers/atividades.h"
#include "../headers/participantes.h"

// Lista global que armazena participantes que já passaram pelo check-in
extern NoAtendido *checkinsRealizados;

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
        // Caso a fila esteja vazia, o novo nó será o primeiro
        fila->inicio = novo;
        fila->fim = novo;
    } else {
        // Caso já existam participantes, adiciona ao final da fila
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
    Participante *atendido = temp->participante;

    printf("Removendo da fila: %s - %s\n", atendido->nome, atendido->matricula);

    // Atualiza o início da fila para o próximo participante
    fila->inicio = fila->inicio->prox;

    // Se a fila ficar vazia após a remoção, zera o fim também
    if (fila->inicio == NULL) {
        fila->fim = NULL;
    }

    // Adiciona o participante removido ao histórico de check-ins
    adicionarAoHistorico(&checkinsRealizados, atendido);

    // Libera apenas o nó da fila (não o participante, pois ele ainda será usado)
    free(temp);
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

// --------------------------------------
// Função: adicionarAoHistorico
// Objetivo: Armazena um participante na lista de check-ins realizados
// --------------------------------------
void adicionarAoHistorico(NoAtendido **lista, Participante *p) {
    NoAtendido *novo = (NoAtendido *)malloc(sizeof(NoAtendido));
    if (!novo) return;

    novo->participante = p;
    novo->prox = *lista;  // Insere no início da lista
    *lista = novo;
}

// --------------------------------------
// Função: listarCheckinsRealizados
// Objetivo: Exibe todos os participantes que já realizaram o check-in
// --------------------------------------
void listarCheckinsRealizados(NoAtendido *lista) {
    if (!lista) {
        printf("Nenhum participante foi atendido ainda.\n");
        return;
    }

    printf("\n--- Participantes que já fizeram check-in ---\n");
    NoAtendido *atual = lista;
    while (atual) {
        printf("Nome: %s | Matrícula: %s | Email: %s\n",
               atual->participante->nome,
               atual->participante->matricula,
               atual->participante->email);
        atual = atual->prox;
    }
}
