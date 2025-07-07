//
// Created by kawandias on 17/06/25.
//

#ifndef EVENTOS_H
#define EVENTOS_H

#define MAX_NOME 100
#define MAX_DATA 11

// ----------------------------------------------------------
// Declaração antecipada da struct Atividade
// Isso permite usar ponteiros para Atividade dentro da struct Evento,
// mesmo que a definição de Atividade esteja em outro arquivo.
// ----------------------------------------------------------
struct Atividade;

// ----------------------------------------------------------
// Estrutura: Evento
// Representa um evento acadêmico
// Utiliza uma lista encadeada circular para armazenar os eventos
// Cada evento contém um nome, uma data e uma lista de atividades
// ----------------------------------------------------------
typedef struct Evento {
    char nome[MAX_NOME];             // Nome do evento (ex: "Semana da Computação")
    char data[MAX_DATA];            // Data do evento no formato "dd/mm/aaaa"
    struct Evento *prox;            // Ponteiro para o próximo evento (lista circular)
    struct Atividade *atividades;   // Ponteiro para a lista de atividades deste evento
} Evento;

// ----------------------------------------------------------
// Funções públicas do módulo de eventos
// ----------------------------------------------------------

// Exibe uma mensagem de boas-vindas ao usuário (logo que o programa inicia)
void saudacao();

// Cadastra um novo evento, pedindo nome e data ao usuário
void cadastrar_evento();

// Lista todos os eventos cadastrados (nome e data)
void listar_eventos();

// Remove um evento com base no nome fornecido pelo usuário
// Também libera todas as atividades associadas a ele
void remover_evento();

// Busca e retorna um ponteiro para o evento com o nome especificado
// Retorna NULL se não encontrar
Evento *buscar_evento(const char *nome);

// Permite ao usuário selecionar um evento dentre os disponíveis
// Retorna ponteiro para o evento escolhido
Evento *selecionarEvento(Evento *listaEventos);

#endif // EVENTOS_H
