//
// Created by kawandias on 17/06/25.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../headers/eventos.h"

// Ponteiro global que aponta para o início da lista circular de eventos
Evento *inicio = NULL;

// ------------------------------------------------------------
// Exibe mensagem de saudação ao iniciar o programa
// ------------------------------------------------------------
void saudacao(){
    printf("\nSistema de Eventos Academicos iniciado com sucesso!\n");
}

// ------------------------------------------------------------
// Valida se a data fornecida está no formato correto (dd/mm/aaaa)
// e se os valores de dia, mês e ano são plausíveis
// ------------------------------------------------------------
int validar_data(const char *data){
    if (strlen(data) != 10) return 0;                    // Verifica tamanho da string
    if (data[2] != '/' || data[5] != '/') return 0;      // Verifica os separadores

    int d, m, a;
    if (sscanf(data, "%2d/%2d/%4d", &d, &m, &a) != 3) return 0;  // Extrai os valores numéricos
    if (d < 1 || d > 31 || m < 1 || m > 12 || a < 1900) return 0;

    return 1;
}

// ------------------------------------------------------------
// Verifica se o nome digitado não está vazio ou apenas com espaços
// ------------------------------------------------------------
int validar_nome(const char *nome){
    if (nome == NULL) return 0;
    for (int i = 0; nome[i] != '\0'; i++) {
        if (!isspace(nome[i])) return 1;  // Retorna 1 se achar algum caractere visível
    }
    return 0;
}

// ------------------------------------------------------------
// Cadastra um novo evento e o insere na lista circular
// ------------------------------------------------------------
void cadastrar_evento(){
    Evento *novo = malloc(sizeof(Evento));
    if (!novo) {
        printf("\nErro ao alocar memoria\n");
        return;
    }

    // Leitura do nome do evento
    printf("Digite o nome do evento: ");
    fgets(novo->nome, MAX_NOME, stdin);
    novo->nome[strcspn(novo->nome, "\n")] = '\0';  // Remove o '\n' final

    if (!validar_nome(novo->nome)) {
        printf("\nNome invalido!\n");
        free(novo);
        return;
    }

    // Leitura da data
    printf("Digite a data do evento (dd/mm/aaaa): ");
    fgets(novo->data, MAX_DATA, stdin);
    novo->data[strcspn(novo->data, "\n")] = '\0';

    if (!validar_data(novo->data)) {
        printf("\nData invalida!\n");
        free(novo);
        return;
    }

    novo->atividades = NULL;
    novo->prox = NULL;

    // Inserção na lista circular
    if (!inicio) {
        // Lista vazia: novo é o primeiro e aponta para si mesmo
        inicio = novo;
        novo->prox = inicio;
    } else {
        // Lista já tem eventos: inserir no final
        Evento *atual = inicio;
        while (atual->prox != inicio)
            atual = atual->prox;

        atual->prox = novo;
        novo->prox = inicio;
    }

    printf("\nEvento cadastrado com sucesso!\n");
}

// ------------------------------------------------------------
// Lista todos os eventos cadastrados na lista circular
// ------------------------------------------------------------
void listar_eventos(){
    if (!inicio) {
        printf("\nNenhum evento cadastrado\n");
        return;
    }

    Evento *atual = inicio;
    int i = 1;

    printf("\nEventos Cadastrados:\n");
    do {
        printf("%d. %s - %s\n", i++, atual->nome, atual->data);
        atual = atual->prox;
    } while (atual != inicio);
    printf("\n");
}

// ------------------------------------------------------------
// Remove um evento da lista circular com base no nome informado
// ------------------------------------------------------------
void remover_evento(){
    if (!inicio) {
        printf("\nNenhum evento para remover\n");
        return;
    }

    listar_eventos();
    printf("Digite o nome do evento a ser removido: ");
    char nome[MAX_NOME];
    fgets(nome, MAX_NOME, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    Evento *atual = inicio;
    Evento *anterior = NULL;

    do {
        if (strcmp(atual->nome, nome) == 0) {
            if (atual == inicio && atual->prox == inicio) {
                // Único evento na lista
                free(atual);
                inicio = NULL;
            } else if (atual == inicio) {
                // Evento é o primeiro da lista
                Evento *ultimo = inicio;
                while (ultimo->prox != inicio)
                    ultimo = ultimo->prox;
                inicio = atual->prox;
                ultimo->prox = inicio;
                free(atual);
            } else {
                // Evento está no meio ou fim
                anterior->prox = atual->prox;
                free(atual);
            }

            printf("\nEvento removido com sucesso\n");
            return;
        }

        anterior = atual;
        atual = atual->prox;
    } while (atual != inicio);

    printf("\nEvento nao encontrado\n");
}

// ------------------------------------------------------------
// Busca um evento na lista circular pelo nome
// Retorna ponteiro para o evento, ou NULL se não encontrado
// ------------------------------------------------------------
Evento *buscar_evento(const char *nome){
    if (!inicio) return NULL;

    Evento *atual = inicio;
    do {
        if (strcmp(atual->nome, nome) == 0)
            return atual;
        atual = atual->prox;
    } while (atual != inicio);

    return NULL;
}

// ------------------------------------------------------------
// Permite ao usuário escolher um evento pelo número da lista
// Usado, por exemplo, no menu de check-in
// ------------------------------------------------------------
Evento* selecionarEvento(Evento *listaEventos) {
    if (listaEventos == NULL) {
        printf("Nenhum evento cadastrado.\n");
        return NULL;
    }

    Evento *atual = listaEventos;
    int contador = 1;

    printf("\n=== Lista de Eventos ===\n");
    do {
        printf("%d - %s (%s)\n", contador, atual->nome, atual->data);
        atual = atual->prox;
        contador++;
    } while (atual != listaEventos);

    int escolha;
    printf("Digite o numero do evento desejado: ");
    scanf("%d", &escolha);
    getchar(); // Limpa o ENTER do buffer

    if (escolha <= 0 || escolha >= contador) {
        printf("Opcao invalida.\n");
        return NULL;
    }

    atual = listaEventos;
    for (int i = 1; i < escolha; i++)
        atual = atual->prox;

    return atual;
}
