//
// Created by kawandias on 17/06/25.
//

#ifndef EVENTOS_H
#define EVENTOS_H

#define MAX_NOME 100
#define MAX_DATA 11

struct Atividade;

typedef struct Evento{
    char nome[MAX_NOME];
    char data[MAX_DATA];
    struct Evento *prox;
    struct Atividade *atividades;
}Evento;

void saudacao();

void cadastrar_evento();
void listar_eventos();
void remover_evento();

#endif // EVENTOS_H