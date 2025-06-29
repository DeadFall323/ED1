//
// Created by kawandias on 17/06/25.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../headers/eventos.h"

// Ponteiro global para o início da lista circular de eventos
Evento *inicio = NULL;

void saudacao(){
    printf("\nSistema de Eventos Academicos iniciado com sucesso!\n");
}

// Valida se a data está no formato correto e com valores plausíveis
int validar_data(const char *data){
    
    if(strlen(data) != 10){
        return 0;
    }
    if(data[2] != '/' || data[5] != '/'){
        return 0;
    }

    int d, m, a;
    if(sscanf(data, "%2d/%2d/%4d", &d, &m, &a) != 3){
        return 0;
    }
    if(d < 1 || d > 31 || m < 1 || m > 12 || a < 1900){
        return 0;
    }
    return 1;
}

// Verifica se o nome é válido
int validar_nome(const char *nome){
    if(nome == NULL){
        return 0;
    }
    for(int i = 0; nome[i] != '\0'; i++){
        if(!isspace(nome[i])) return 1;
    }
    return 0;
}

// Cadastra um novo evento e insere na lista circular
void cadastrar_evento(){
    Evento *novo = malloc(sizeof(Evento));
    if(!novo){
        printf("\nErro ao alocar memoria\n");
        return;
    }

    printf("Digite o nome do evento: ");
    fgets(novo->nome, MAX_NOME, stdin);
    novo->nome[strcspn(novo->nome, "\n")] = '\0';

    if(!validar_nome(novo->nome)){
        printf("\nNome invalido!\n");
        free(novo);
        return;
    }

    printf("Digite a data do evento (dd/mm/aaaa): ");
    fgets(novo->data, MAX_DATA, stdin);
    novo->data[strcspn(novo->data, "\n")] = '\0';

    if(!validar_data(novo->data)){
        printf("\nData invalida!\n");
        free(novo);
        return;
    }

    novo->prox = NULL;

    // Inserção na lista circular
    if(!inicio){
        inicio = novo;
        novo->prox = inicio;
    }else{
        Evento *atual = inicio;
        while (atual->prox != inicio)
            atual = atual->prox;

        atual->prox = novo;
        novo->prox = inicio;
    }

    printf("\nEvento cadastrado com sucesso!\n");
}

// Lista todos os eventos cadastrados
void listar_eventos(){
    if(!inicio){
        printf("\nNenhum evento cadastrado\n");
        return;
    }

    Evento *atual = inicio;
    int i = 1;

    printf("\nEventos Cadastrados:\n");
    do{
        printf("%d. %s - %s\n", i++, atual->nome, atual->data);
        atual = atual->prox;
    }while(atual != inicio);
    printf("\n");
}

// Remove um evento da lista circular com base no nome informado
void remover_evento(){
    if(!inicio){
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

    do{
        if(strcmp(atual->nome, nome) == 0){
            if(atual == inicio && atual->prox == inicio){
                free(atual);
                inicio = NULL;
            }else if (atual == inicio){
                Evento *ultimo = inicio;
                while (ultimo->prox != inicio)
                    ultimo = ultimo->prox;
                inicio = atual->prox;
                ultimo->prox = inicio;
                free(atual);
            }else{
                anterior->prox = atual->prox;
                free(atual);
            }

            printf("\nEvento removido com sucesso\n");
            return;
        }
        anterior = atual;
        atual = atual->prox;
    }while(atual != inicio);

    printf("\nEvento nao encontrado\n");
}