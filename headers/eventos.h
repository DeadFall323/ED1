//
// Created by kawandias on 17/06/25.
//

#ifndef EVENTOS_H
#define EVENTOS_H

#define MAX_NOME 100
#define MAX_DATA 11

// Declaração antecipada da struct Atividade, que será definida em outro módulo
struct Atividade;

// Estrutura de Evento (lista encadeada circular)
typedef struct Evento{
    char nome[MAX_NOME]; // Nome do evento
    char data[MAX_DATA]; // Data no formato "dd/mm/aaaa"
    struct Evento *prox; // Ponteiro para o próximo evento (lista circular)
    struct Atividade *atividades; // Ponteiro para a lista de atividades do evento
}Evento;

// Funções principais do módulo de eventos
void saudacao(); // Exibe mensagem de boas-vindas

void cadastrar_evento(); // Cadastra novo evento
void listar_eventos(); // Lista todos os eventos cadastrados
void remover_evento(); // Remove um evento com base no nome

#endif // EVENTOS_H