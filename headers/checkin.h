#ifndef CHECKIN_H
#define CHECKIN_H

typedef struct NoFila {
    char nome[100];
    char matricula[20];
    struct NoFila *prox;
} NoFila;

typedef struct {
    NoFila *inicio;
    NoFila *fim;
} Fila;

// Funções da Fila de Check-in
void inicializarFila(Fila *fila);
void enfileirar(Fila *fila, char nome[], char matricula[]);
void desenfileirar(Fila *fila);
void listarFila(Fila *fila);

#endif
