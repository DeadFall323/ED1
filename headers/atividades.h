#ifndef ATIVIDADES_H
#define ATIVIDADES_H

#include "participantes.h"
#include "eventos.h" // Necessário para que o tipo Evento seja reconhecido neste cabeçalho

// Estrutura que representa uma atividade em um evento
typedef struct Atividade {
    char titulo[100];                 // Título da atividade
    char horario[6];                  // Horário no formato "HH:MM" (apenas para exibição)
    int  hora;                        // Horário em inteiro (ex: 1330 para 13:30) — usado para ordenação e conflitos
    Participante *participantes;     // Ponteiro para a lista duplamente encadeada de participantes
    struct Atividade *prox;          // Ponteiro para a próxima atividade (lista encadeada simples)
} Atividade;

// Cria uma nova atividade com título e horário especificados
Atividade *criarAtividade(char titulo[], int hora);

// Insere uma atividade na lista de atividades do evento
void inserirAtividade(Atividade **lista, Atividade *nova);

// Lista todas as atividades cadastradas
void listarAtividades(Atividade *lista);

// Remove uma atividade da lista, dado seu título
// Requer o ponteiro do evento para atualizar corretamente a estrutura
void removerAtividade(Evento *evento, Atividade **lista, char titulo[]);

// Ordena a lista de atividades com base no horário (algoritmo iterativo ou recursivo, a depender da implementação)
void ordenarAtividades(Atividade **lista);

// Verifica se há conflito de horário entre a nova atividade e as já existentes
// Retorna 1 se houver conflito, 0 caso contrário
int verificarConflito(Atividade *lista, int hora);

#endif // ATIVIDADES_H
