//
// Created by kawandias on 17/06/25.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../headers/participantes.h"
#include "../headers/eventos.h"
#include "../headers/atividades.h"
#include "../headers/desfazer.h" // Necessário para registrar operações na pilha de desfazer

// Ponteiros globais
extern Evento *inicio;
extern NoPilha *pilhaDesfazer; // Pilha compartilhada entre os módulos

// ------------------------------------------------------------
// Cria e inicializa um novo participante com nome, email e matrícula
// Realiza validação de email e matrícula antes de alocar memória
// ------------------------------------------------------------
Participante* criar_participante(const char *nome, const char *email, const char *matricula) {
    if (!validar_email(email) || !validar_matricula(matricula)) {
        printf("Email ou matricula invalidos.\n");
        return NULL;
    }

    Participante *novo = (Participante *) malloc(sizeof(Participante));
    if (!novo) return NULL;

    strcpy(novo->nome, nome);
    strcpy(novo->email, email);
    strcpy(novo->matricula, matricula);
    novo->ant = NULL;
    novo->prox = NULL;

    return novo;
}
// Insere um participante no início da lista duplamente encadeada
// Atualiza os ponteiros corretamente para manter a estrutura
void inserir_participante(Participante **lista, Participante *novo) {
    if (!novo) return;

    novo->prox = *lista;
    if (*lista)
        (*lista)->ant = novo;

    *lista = novo;
}

// Lista todos os participantes presentes na lista
void listar_participantes(Participante *lista) {
    Participante *atual = lista;

    printf("\n--- Participantes ---\n");
    while (atual) {
        printf("Nome: %s | Email: %s | Matricula: %s\n",
               atual->nome, atual->email, atual->matricula);
        atual = atual->prox;
    }
}

// Remove um participante de uma atividade com base na matrícula
// Também registra a operação na pilha de desfazer
void remover_participante(Evento *evento, Atividade *atividade, const char *matricula) {
    Participante *atual = atividade->participantes;

    // Busca o participante com a matrícula correspondente
    while (atual && strcmp(atual->matricula, matricula) != 0)
        atual = atual->prox;

    if (!atual) {
        printf("Participante nao encontrado.\n");
        return;
    }

    // Empilha os dados da remoção
    empilhar(&pilhaDesfazer, "participante", atual->nome, atual->email,
             atual->matricula, atividade->titulo, evento->nome);

    printf("Participante %s removido com sucesso!\n", atual->nome);

    // Remove o participante da lista duplamente encadeada
    if (atual->ant)
        atual->ant->prox = atual->prox;
    else
        atividade->participantes = atual->prox;

    if (atual->prox)
        atual->prox->ant = atual->ant;

    free(atual);
}

// Ordena a lista de participantes por nome (ordem alfabética)
// Utiliza o algoritmo Bubble Sort (troca apenas os dados, não os ponteiros)
void ordenar_participantes_bubble(Participante **lista) {
    if (!lista || !*lista) return;

    int trocou;
    do {
        trocou = 0;
        Participante *atual = *lista;
        while (atual && atual->prox) {
            if (strcmp(atual->nome, atual->prox->nome) > 0) {
                // Troca apenas os dados (shallow swap)
                Participante temp = *atual;
                strcpy(atual->nome, atual->prox->nome);
                strcpy(atual->email, atual->prox->email);
                strcpy(atual->matricula, atual->prox->matricula);

                strcpy(atual->prox->nome, temp.nome);
                strcpy(atual->prox->email, temp.email);
                strcpy(atual->prox->matricula, temp.matricula);
                trocou = 1;
            }
            atual = atual->prox;
        }
    } while (trocou);
}

// Valida se o e-mail tem '@' e '.' presentes
// Simples, porém suficiente para evitar erros básicos
int validar_email(const char *email) {
    return strchr(email, '@') && strchr(email, '.');
}

// Verifica se a matrícula contém apenas números e tem tamanho aceitável
// O tamanho mínimo pode ser ajustado alterando a variável abaixo
int validar_matricula(const char *matricula) {
    int len = strlen(matricula);
    int tamanho_matricula = 5;

    if (len < tamanho_matricula || len > 20)
        return 0;

    for (int i = 0; i < len; i++) {
        if (!isdigit(matricula[i]))
            return 0;
    }
    return 1;
}
