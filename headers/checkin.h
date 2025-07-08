#ifndef CHECKIN_H
#define CHECKIN_H

#include "participantes.h"
#include "eventos.h"

// ---------------------
// Estruturas de Dados
// ---------------------

// Nó da fila de check-in
// Cada nó aponta para um participante e para o próximo da fila
typedef struct NoFila {
    Participante *participante;  // Participante que está aguardando na fila
    struct NoFila *prox;         // Próximo da fila
} NoFila;

// Estrutura da fila de check-in
// Controla o início e o fim da fila
typedef struct {
    NoFila *inicio;  // Primeiro participante da fila (o próximo a ser atendido)
    NoFila *fim;     // Último participante da fila (o mais recente a entrar)
} Fila;

// Lista de participantes que já fizeram check-in
// Utilizada para registrar um histórico separado dos participantes atendidos
typedef struct NoAtendido {
    Participante *participante;     // Participante que já foi atendido
    struct NoAtendido *prox;        // Próximo da lista de atendidos
} NoAtendido;

// ---------------------
// Funções da Fila
// ---------------------

// Inicializa a fila com ponteiros nulos (fila vazia)
void inicializarFila(Fila *fila);

// Insere um participante no fim da fila de check-in
void enfileirar(Fila *fila, Participante *p);

// Remove o participante do início da fila (o primeiro a ser atendido)
void desenfileirar(Fila *fila);

// Exibe todos os participantes que estão na fila, em ordem de chegada
void listarFila(Fila *fila);

// ---------------------
// Funções do Histórico
// ---------------------

// Adiciona um participante à lista de check-ins realizados
void adicionarAoHistorico(NoAtendido **lista, Participante *p);

// Lista todos os participantes que já passaram pelo check-in
void listarCheckinsRealizados(NoAtendido *lista);

#endif
