#ifndef CHECKIN_H
#define CHECKIN_H

#include "participantes.h"
#include "eventos.h"

// Nó da fila
typedef struct NoFila {
    Participante *participante;
    struct NoFila *prox;
} NoFila;

typedef struct {
    NoFila *inicio;
    NoFila *fim;
} Fila;

// Funções da fila
void inicializarFila(Fila *fila);
void enfileirar(Fila *fila, Participante *p);
void desenfileirar(Fila *fila);
void listarFila(Fila *fila);

// Funções de menu e lógica
int participante_ja_na_fila(Fila *fila, Participante *p);
void realizarCheckin(Fila *fila, Evento *listaEventos);
void menuCheckin(Fila *filaCheckin, Evento *listaEventos);

#endif
