#ifndef DESFAZER_H
#define DESFAZER_H

// --------------------------------------------
// Estrutura de um nó da pilha de desfazer
// Cada nó armazena os dados necessários para reverter uma remoção
// Pode representar uma atividade ou um participante
// --------------------------------------------
typedef struct NoPilha {
    char tipo[20];               // Tipo da entidade removida: "participante" ou "atividade"
    char nome[100];              // Nome do participante ou da atividade
    char email[100];             // E-mail original (apenas para participante)
    char infoExtra[100];         // Matrícula (para participante) ou horário (para atividade)
    char atividade_titulo[100];  // Título da atividade (para desfazer participante removido)
    char evento_nome[100];       // Nome do evento ao qual a entidade pertencia
    struct NoPilha *prox;        // Ponteiro para o próximo elemento da pilha
} NoPilha;

// --------------------------------------------
// Inicializa a pilha de desfazer (define topo como NULL)
// Deve ser chamada no início do programa
// --------------------------------------------
void inicializarPilha(NoPilha **topo);

// --------------------------------------------
// Empilha uma nova operação de remoção
// Armazena todas as informações necessárias para reverter a ação depois
// --------------------------------------------
void empilhar(NoPilha **topo, char tipo[], char nome[], char email[], char infoExtra[], char atividade[], char evento[]);

// --------------------------------------------
// Desempilha o último item da pilha e reverte a remoção
// Reinsere a atividade ou o participante no local original
// --------------------------------------------
void desempilhar(NoPilha **topo);

// --------------------------------------------
// Lista o conteúdo da pilha de desfazer (opcional para debug ou exibição)
// --------------------------------------------
void listarPilha(NoPilha *topo);

// --------------------------------------------
// Função principal a ser chamada no menu do sistema
// Encapsula o processo de desfazer a última ação
// --------------------------------------------
void desfazer_remocao();

// Pilha de desfazer global usada pelo sistema inteiro
extern NoPilha *pilhaDesfazer;

#endif
