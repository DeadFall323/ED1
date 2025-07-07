#ifndef PARTICIPANTES_H
#define PARTICIPANTES_H

#define MAX_NOME 100
#define MAX_EMAIL 100
#define MAX_MATRICULA 20

// Declarações antecipadas para evitar erro de tipo desconhecido
// Permite usar ponteiros para Evento e Atividade mesmo sem incluí-los aqui
struct Evento;
struct Atividade;

// Estrutura: Participante
// Utiliza lista duplamente encadeada para permitir remoções eficientes
// Cada participante possui nome, e-mail e matrícula
typedef struct Participante {
    char nome[MAX_NOME];                // Nome completo do participante
    char email[MAX_EMAIL];              // E-mail institucional ou pessoal
    char matricula[MAX_MATRICULA];      // Identificação única (ex: matrícula universitária)
    struct Participante *ant;           // Ponteiro para o anterior na lista
    struct Participante *prox;          // Ponteiro para o próximo na lista
} Participante;

// Funções de gerenciamento de participantes

// Cria um novo participante com os dados informados
Participante* criar_participante(const char *nome, const char *email, const char *matricula);

// Insere um participante na lista duplamente encadeada
void inserir_participante(Participante **lista, Participante *novo);

// Lista todos os participantes de uma determinada atividade
void listar_participantes(Participante *lista);

// Remove um participante da lista, com base na matrícula
// Recebe ponteiro para evento e atividade para uso na pilha de desfazer
void remover_participante(struct Evento *evento, struct Atividade *atividade, const char *matricula);

// Ordena a lista de participantes por nome usando algoritmo Bubble Sort (iterativo)
void ordenar_participantes_bubble(Participante **lista);

// Funções auxiliares de validação

// Verifica se o e-mail está em um formato válido
int validar_email(const char *email);

// Verifica se a matrícula tem um formato aceitável
int validar_matricula(const char *matricula);

// Menu interativo de participantes (chamado pelas atividades)
void menu_participantes();

#endif // PARTICIPANTES_H
