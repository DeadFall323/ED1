#ifndef CHECKIN_H
#define CHECKIN_H

#include "participantes.h" // Necessário para usar Participante*
#include "eventos.h"  // para declarar Evento*

// Nó da fila de check-in, armazenando um ponteiro para participante real
typedef struct NoFila {
    Participante *participante;
    struct NoFila *prox;
} NoFila;

// Estrutura da fila com ponteiros para o início e fim
typedef struct {
    NoFila *inicio;
    NoFila *fim;
} Fila;

// Funções da Fila de Check-in
void inicializarFila(Fila *fila);
void enfileirar(Fila *fila, Participante *p);
void desenfileirar(Fila *fila);
void listarFila(Fila *fila);
void realizarCheckin(Fila *fila, Evento *listaEventos);

#endif
