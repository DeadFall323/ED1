#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/atividades.h"
#include "../headers/desfazer.h"  // Inclusão para permitir o uso da pilha de desfazer

// A pilha de desfazer é declarada externamente para ser compartilhada entre os arquivos
extern NoPilha *pilhaDesfazer;  

/* 
 * Função merge (parte da ordenação por merge sort)
 * Une duas listas de atividades já ordenadas, com base no campo 'hora'
 * Retorna uma nova lista também ordenada
 */
Atividade *merge(Atividade *a, Atividade *b) {
    if (!a) return b;
    if (!b) return a;

    Atividade *resultado = NULL;

    if (a->hora <= b->hora) {
        resultado = a;
        resultado->prox = merge(a->prox, b);
    } else {
        resultado = b;
        resultado->prox = merge(a, b->prox);
    }
    return resultado;
}

/*
 * Função dividir
 * Separa uma lista encadeada em duas metades (parte da ordenação merge sort)
 * 'frente' recebe a primeira metade e 'tras' a segunda
 */
void dividir(Atividade *origem, Atividade **frente, Atividade **tras) {
    if (!origem || !origem->prox) {
        *frente = origem;
        *tras = NULL;
        return;
    }

    Atividade *lento = origem;
    Atividade *rapido = origem->prox;

    // Técnica do ponteiro rápido e lento para encontrar o meio da lista
    while (rapido) {
        rapido = rapido->prox;
        if (rapido) {
            lento = lento->prox;
            rapido = rapido->prox;
        }
    }

    *frente = origem;
    *tras = lento->prox;
    lento->prox = NULL;  // Quebra a lista ao meio
}

/*
 * Função ordenarAtividades
 * Ordena a lista de atividades com base no horário usando merge sort (recursivo)
 */
void ordenarAtividades(Atividade **lista) {
    Atividade *cabeca = *lista;
    if (!cabeca || !cabeca->prox) return;

    Atividade *a;
    Atividade *b;
    dividir(cabeca, &a, &b);
    ordenarAtividades(&a);
    ordenarAtividades(&b);
    *lista = merge(a, b);
}

/*
 * Função criarAtividade
 * Aloca e inicializa uma nova atividade com título e horário
 * O horário é armazenado tanto em formato inteiro (para ordenação/conflitos)
 * quanto em string formatada "HH:MM" (para exibição)
 */
Atividade *criarAtividade(char titulo[], int hora) {
    Atividade *nova = (Atividade *)malloc(sizeof(Atividade));
    if (!nova) {
        printf("Erro de alocação de memória!\n");
        return NULL;
    }

    strcpy(nova->titulo, titulo);
    nova->hora = hora;

    // Converte o inteiro do horário para string formatada (ex: 1330 → "13:30")
    snprintf(nova->horario, sizeof(nova->horario), "%02d:%02d", hora / 100, hora % 100);

    nova->participantes = NULL; 
    nova->prox = NULL;

    return nova;
}

/*
 * Função verificarConflito
 * Percorre a lista de atividades e verifica se já existe uma no mesmo horário
 * Retorna 1 em caso de conflito, 0 caso contrário
 */
int verificarConflito(Atividade *lista, int hora) {
    Atividade *atual = lista;
    while (atual) {
        if (atual->hora == hora) {
            return 1; // Conflito de horário encontrado
        }
        atual = atual->prox;
    }
    return 0; // Nenhum conflito
}

/*
 * Função inserirAtividade
 * Adiciona uma nova atividade no início da lista, após verificar conflitos de horário
 * Caso haja conflito, exibe mensagem de erro e descarta a nova atividade
 */
void inserirAtividade(Atividade **lista, Atividade *nova) {
    if (verificarConflito(*lista, nova->hora)) {
        printf("Conflito de horário! Já existe uma atividade às %02d:%02d.\n", nova->hora / 100, nova->hora % 100);
        free(nova); // Libera a memória da atividade não inserida
        return;
    }

    // Inserção no início da lista encadeada
    nova->prox = *lista;
    *lista = nova;
    printf(" Atividade '%s' cadastrada com sucesso!\n", nova->titulo);
}

/*
 * Função listarAtividades
 * Exibe todas as atividades cadastradas em um evento
 */
void listarAtividades(Atividade *lista) {
    if (!lista) {
        printf("Nenhuma atividade cadastrada neste evento.\n");
        return;
    }

    printf("\n--- Lista de Atividades ---\n");
    Atividade *atual = lista;
    while (atual) {
        printf("  - Titulo: %s | Horario: %02d:%02dhrs\n", atual->titulo, atual->hora / 100, atual->hora % 100);
        atual = atual->prox;
    }
}

/*
 * Função removerAtividade
 * Remove uma atividade de um evento e registra essa ação na pilha de desfazer
 * Requer ponteiro para o evento, pois a pilha armazena o nome do evento original
 */
void removerAtividade(Evento *evento, Atividade **lista, char titulo[]) {
    Atividade *atual = *lista;
    Atividade *anterior = NULL;

    // Procura a atividade pelo título na lista encadeada
    while (atual && strcmp(atual->titulo, titulo) != 0) {
        anterior = atual;
        atual = atual->prox;
    }

    if (!atual) {
        printf("Atividade com o título '%s' não encontrada.\n", titulo);
        return;
    }

    // Registra a operação de remoção na pilha de desfazer
    char horario_str[10];
    sprintf(horario_str, "%d", atual->hora);  // Converte o horário inteiro em string
    empilhar(&pilhaDesfazer, "atividade", atual->titulo, "-", horario_str, "-", evento->nome);

    // Remove a atividade da lista
    if (anterior) {
        anterior->prox = atual->prox;
    } else {
        *lista = atual->prox;
    }

    free(atual);  // Libera a memória do nó removido
    printf("Atividade '%s' removida com sucesso.\n", titulo);
}
