#ifndef DESFAZER_H
#define DESFAZER_H

typedef struct NoPilha {
    char tipo[20]; // "atividade" ou "participante"
    char nome[100];
    char infoExtra[100]; // Pode ser matrícula ou horário
    struct NoPilha *prox;
} NoPilha;

// Funções da Pilha de Desfazer
void inicializarPilha(NoPilha **topo);
void empilhar(NoPilha **topo, char tipo[], char nome[], char infoExtra[]);
void desempilhar(NoPilha **topo);
void listarPilha(NoPilha *topo);

#endif
