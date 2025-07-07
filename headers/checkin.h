#ifndef CHECKIN_H
#define CHECKIN_H

#include "participantes.h"
#include "eventos.h"

// Estrutura de nó da fila de check-in
// Cada nó armazena um ponteiro para um participante e aponta para o próximo da fila
typedef struct NoFila {
    Participante *participante;  // Participante associado ao nó da fila
    struct NoFila *prox;         // Próximo nó da fila
} NoFila;

// Estrutura da fila propriamente dita
// Contém ponteiros para o início e o fim da fila
typedef struct {
    NoFila *inicio;  // Primeiro participante da fila (o próximo a ser atendido)
    NoFila *fim;     // Último participante da fila
} Fila;

// ---------- Funções básicas da fila ----------

// Inicializa a fila com ponteiros nulos
void inicializarFila(Fila *fila);

// Insere um participante no final da fila de check-in
void enfileirar(Fila *fila, Participante *p);

// Remove o participante que está no início da fila (o próximo da vez)
void desenfileirar(Fila *fila);

// Lista todos os participantes atualmente na fila de check-in
void listarFila(Fila *fila);

// ---------- Funções auxiliares e de menu ----------

// Verifica se um participante já está na fila para evitar duplicidade
// Retorna 1 se estiver, 0 se não estiver
int participante_ja_na_fila(Fila *fila, Participante *p);

// Realiza o processo de check-in:
// - Seleciona o evento
// - Lista participantes
// - Permite escolher quem deve ser enfileirado
void realizarCheckin(Fila *fila, Evento *listaEventos);

// Exibe o menu de check-in no terminal
void menuCheckin(Fila *filaCheckin, Evento *listaEventos);

#endif
