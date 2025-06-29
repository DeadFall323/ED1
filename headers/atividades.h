#ifndef ATIVIDADES_H
#define ATIVIDADES_H

#include "participantes.h"

typedef struct Atividade {
    char titulo[100];
    char horario[6];
    int  hora;     
    Participante *participantes; // lista duplamente encadeada
    struct Atividade *prox;
} Atividade;

// FUNCOES DE ATIVIDADES
Atividade *criarAtividade(char titulo[], int hora);
void inserirAtividade(Atividade **lista, Atividade *nova);
void listarAtividades(Atividade *lista);
void removerAtividade(Atividade **lista, char titulo[]);
void ordenarAtividades(Atividade **lista);
int verificarConflito(Atividade *lista, int hora);

#endif //ATIVIDADES_H
