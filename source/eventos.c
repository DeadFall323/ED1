//
// Created by kawandias on 17/06/25.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../headers/eventos.h"

Evento *inicio = NULL;

void saudacao(){
    printf("Sistema de Eventos Academicos iniciado com sucesso!\n");
}

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

int validar_nome(const char *nome){
    return strlen(nome) > 0;
}

void cadastrar_evento(){
    Evento *novo = malloc(sizeof(Evento));
    if(!novo){
        printf("Erro ao alocar memoria\n");
        return;
    }

    printf("Digite o nome do evento: ");
    fgets(novo->nome, MAX_NOME, stdin);
    novo->nome[strcspn(novo->nome, "\n")] = '\0';

    if(!validar_nome(novo->nome)){
        printf("Nome invalido\n");
        free(novo);
        return;
    }

    printf("Digite a data do evento (dd/mm/aaaa): ");
    fgets(novo->data, MAX_DATA, stdin);
    novo->data[strcspn(novo->data, "\n")] = '\0';

    if(!validar_data(novo->data)){
        printf("Data invalida\n");
        free(novo);
        return;
    }

    novo->prox = NULL;

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