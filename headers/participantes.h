#ifndef PARTICIPANTES_H
#define PARTICIPANTES_H

#define MAX_NOME 100
#define MAX_EMAIL 100
#define MAX_MATRICULA 20

// Declarações antecipadas para evitar erro de tipo desconhecido
struct Evento;
struct Atividade;

// Estrutura do participante (lista duplamente encadeada)
typedef struct Participante {
    char nome[MAX_NOME];
    char email[MAX_EMAIL];
    char matricula[MAX_MATRICULA];
    struct Participante *ant;
    struct Participante *prox;
} Participante;

// Funções de gerenciamento de participantes
Participante* criar_participante(const char *nome, const char *email, const char *matricula);
void inserir_participante(Participante **lista, Participante *novo);
void listar_participantes(Participante *lista);
void remover_participante(struct Evento *evento, struct Atividade *atividade, const char *matricula);
void ordenar_participantes_bubble(Participante **lista);

// Validações
int validar_email(const char *email);
int validar_matricula(const char *matricula);

// Menu interativo (já integrado a atividades)
void menu_participantes();

#endif // PARTICIPANTES_H
