#ifndef DESFAZER_H
#define DESFAZER_H

// Estrutura de um nó da pilha de desfazer
typedef struct NoPilha {
    char tipo[20];               // "participante" ou "atividade"
    char nome[100];              // nome do participante ou atividade
    char email[100];             // e-mail original do participante
    char infoExtra[100];         // matrícula (para participante) ou horário (para atividade)
    char atividade_titulo[100];  // título da atividade (para participante)
    char evento_nome[100];       // nome do evento
    struct NoPilha *prox;        // ponteiro para o próximo da pilha
} NoPilha;

// Inicializa a pilha (define topo como NULL)
void inicializarPilha(NoPilha **topo);

// Empilha uma operação de remoção (participante ou atividade)
void empilhar(NoPilha **topo, char tipo[], char nome[], char email[], char infoExtra[], char atividade[], char evento[]);

// Desempilha e executa a ação de desfazer (realmente reverte a remoção)
void desempilhar(NoPilha **topo);

// Lista todas as operações empilhadas (opcional para debug)
void listarPilha(NoPilha *topo);

// Função principal chamada no menu para desfazer a última remoção
void desfazer_remocao();

extern NoPilha *pilhaDesfazer; 

#endif
