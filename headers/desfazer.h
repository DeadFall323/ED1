#ifndef DESFAZER_H
#define DESFAZER_H

// Estrutura de um nó da pilha de desfazer
typedef struct NoPilha {
    char tipo[20];             // "participante" ou "atividade"
    char nome[100];            // nome do participante ou atividade
    char infoExtra[100];       // matrícula (para participante) ou horário (para atividade)
    char atividade_titulo[100]; // título da atividade (somente para participante)
    char evento_nome[100];      // nome do evento
    struct NoPilha *prox;
} NoPilha;

// Inicializa a pilha (define topo como NULL)
void inicializarPilha(NoPilha **topo);

// Empilha uma operação de remoção
void empilhar(NoPilha **topo, char tipo[], char nome[], char infoExtra[], char atividade[], char evento[]);

// Desempilha e executa a ação de desfazer (exibe o que seria restaurado)
void desempilhar(NoPilha **topo);

// Lista todas as operações empilhadas (para debug ou visualização)
void listarPilha(NoPilha *topo);

// Função principal chamada no menu para desfazer a última remoção
void desfazer_remocao();

#endif
