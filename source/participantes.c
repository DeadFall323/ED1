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
#include "../headers/desfazer.h" // Adiciona para usar a pilha de desfazer

extern Evento *inicio;
extern NoPilha *pilhaDesfazer; // Declara a pilha de desfazer compartilhada com main

// Função para criar um novo participante com validação de dados
Participante* criar_participante(const char *nome, const char *email, const char *matricula) {
    // Verifica se email e matrícula são válidos
    if (!validar_email(email) || !validar_matricula(matricula)) {
        printf("Email ou matricula invalidos.\n");
        return NULL; // Retorna NULL se dados inválidos
    }

    Participante *novo = (Participante *) malloc(sizeof(Participante)); // Aloca memória
    if (!novo) return NULL; // Retorna NULL se falhar

    // Copia os dados para os campos da struct
    strcpy(novo->nome, nome);
    strcpy(novo->email, email);
    strcpy(novo->matricula, matricula);
    novo->ant = NULL;
    novo->prox = NULL;

    return novo; // Retorna ponteiro para o novo participante
}

// Insere um participante no início da lista duplamente encadeada
void inserir_participante(Participante **lista, Participante *novo) {
    if (!novo) return; // Verifica se o ponteiro é válido
    novo->prox = *lista; // O próximo do novo será o atual primeiro
    if (*lista) (*lista)->ant = novo; // Atualiza o anterior do antigo primeiro, se existir
    *lista = novo; // Atualiza o início da lista para o novo nó
}

// Lista todos os participantes da lista
void listar_participantes(Participante *lista) {
    Participante *atual = lista; // Começa do início da lista
    printf("\n--- Participantes ---\n");
    while (atual) {
        // Exibe os dados do participante atual
        printf("Nome: %s | Email: %s | Matricula: %s\n",
               atual->nome, atual->email, atual->matricula);
        atual = atual->prox; // Avança para o próximo
    }
}

// Remove um participante de uma atividade, com suporte à pilha de desfazer
// Recebe ponteiros para o evento e para a atividade, além da matrícula do participante a ser removido
void remover_participante(Evento *evento, Atividade *atividade, const char *matricula) {
    Participante *atual = atividade->participantes;

    // Procura o participante pela matrícula na lista da atividade
    while (atual && strcmp(atual->matricula, matricula) != 0)
        atual = atual->prox;

    if (!atual) {
        printf("Participante nao encontrado.\n");
        return;
    }

    // Empilha os dados da remoção para permitir desfazer depois
    empilhar(&pilhaDesfazer, "participante", atual->nome, atual->email, atual->matricula, atividade->titulo, evento->nome);

    printf("Participante %s removido com sucesso!\n", atual->nome);

    // Ajusta os ponteiros da lista duplamente encadeada da atividade
    if (atual->ant)
        atual->ant->prox = atual->prox;
    else
        atividade->participantes = atual->prox;

    if (atual->prox)
        atual->prox->ant = atual->ant;

    // Libera a memória do participante removido
    free(atual);
}


// Ordena os participantes alfabeticamente por nome usando Bubble Sort
void ordenar_participantes_bubble(Participante **lista) {
    if (!lista || !*lista) return; // Lista vazia ou inexistente

    int trocou;
    do {
        trocou = 0;
        Participante *atual = *lista;
        while (atual && atual->prox) {
            // Compara nomes dos nós consecutivos
            if (strcmp(atual->nome, atual->prox->nome) > 0) {
                // Troca apenas os dados, não os ponteiros
                Participante temp = *atual;
                strcpy(atual->nome, atual->prox->nome);
                strcpy(atual->email, atual->prox->email);
                strcpy(atual->matricula, atual->prox->matricula);

                strcpy(atual->prox->nome, temp.nome);
                strcpy(atual->prox->email, temp.email);
                strcpy(atual->prox->matricula, temp.matricula);
                trocou = 1; // Indica que houve troca
            }
            atual = atual->prox; // Avança na lista
        }
    } while (trocou); // Continua até não haver mais trocas
}

// Validação simples de e-mail (deve conter '@' e '.') usando a funcao pronta de string.h
int validar_email(const char *email) {
    return strchr(email, '@') && strchr(email, '.');
}

// Verifica se a matrícula é composta apenas por números e possui tamanho aceitável
// Essa parte eh modular, para mudar o tamanho da matricula eh so mudar: int tamanho_matricula = 5;
int validar_matricula(const char *matricula) {
    int len = strlen(matricula);
    int tamanho_matricula = 5;
    if (len < tamanho_matricula || len > 20) return 0; // Tamanho inválido
    for (int i = 0; i < len; i++) {
        if (!isdigit(matricula[i])) return 0; // Caracter não numérico
    }
    return 1; // Matrícula válida
}
