#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/desfazer.h"
#include "../headers/eventos.h"       // Para buscar evento
#include "../headers/atividades.h"    // Para buscar atividade
#include "../headers/participantes.h" // Para recriar participante

NoPilha *pilhaDesfazer;  // Pilha global usada para armazenar remoções

// Inicializa a pilha definindo topo como NULL
void inicializarPilha(NoPilha **topo) {
    *topo = NULL;
}

// Empilha uma remoção: pode ser de participante ou atividade
void empilhar(NoPilha **topo, char tipo[], char nome[], char infoExtra[], char atividade[], char evento[]) {
    NoPilha *novo = (NoPilha *)malloc(sizeof(NoPilha));
    if (!novo) {
        printf("Erro ao alocar memória para a pilha.\n");
        return;
    }

    strcpy(novo->tipo, tipo);
    strcpy(novo->nome, nome);
    strcpy(novo->infoExtra, infoExtra);
    strcpy(novo->atividade_titulo, atividade);
    strcpy(novo->evento_nome, evento);

    novo->prox = *topo;
    *topo = novo;
}

// Lista todos os elementos da pilha
void listarPilha(NoPilha *topo) {
    if (topo == NULL) {
        printf("Pilha vazia.\n");
        return;
    }

    printf("Pilha de operações:\n");
    NoPilha *aux = topo;
    while (aux != NULL) {
        printf("[%s] Nome: %s | Info Extra: %s\n", aux->tipo, aux->nome, aux->infoExtra);
        aux = aux->prox;
    }
}

// Função principal chamada no menu para desfazer a última remoção
// suporta desfazer tanto participantes quanto atividades
void desfazer_remocao() {
    if (pilhaDesfazer == NULL) {
        printf("Pilha vazia, nada para desfazer.\n");
        return;
    }

    NoPilha *temp = pilhaDesfazer;

    // DESFAZER REMOÇÃO DE PARTICIPANTE
    
    if (strcmp(temp->tipo, "participante") == 0) {
        // Busca o evento salvo na pilha
        Evento *evento = buscar_evento(temp->evento_nome);
        if (!evento) {
            printf("Evento '%s' não encontrado ao desfazer.\n", temp->evento_nome);
            return;
        }

        // Busca a atividade dentro do evento
        Atividade *atividade = evento->atividades;
        while (atividade && strcmp(atividade->titulo, temp->atividade_titulo) != 0)
            atividade = atividade->prox;

        if (!atividade) {
            printf("Atividade '%s' não encontrada ao desfazer.\n", temp->atividade_titulo);
            return;
        }

        // Recria o participante com email genérico (já que não armazenamos o original)
        Participante *restaurado = criar_participante(temp->nome, "email@restaurado.com", temp->infoExtra);
        if (!restaurado) {
            printf("Erro ao recriar participante.\n");
            return;
        }

        // Reinsere o participante na lista original
        inserir_participante(&atividade->participantes, restaurado);
        printf("Desfazer realizado: participante '%s' foi restaurado na atividade '%s' do evento '%s'.\n",
               temp->nome, temp->atividade_titulo, temp->evento_nome);
    }

    // DESFAZER REMOÇÃO DE ATIVIDADE

    else if (strcmp(temp->tipo, "atividade") == 0) {
        // Busca o evento onde a atividade foi originalmente cadastrada
        Evento *evento = buscar_evento(temp->evento_nome);
        if (!evento) {
            printf("Evento '%s' não encontrado ao desfazer.\n", temp->evento_nome);
            return;
        }

        // Converte o horário salvo como string para inteiro
        int hora;
        sscanf(temp->infoExtra, "%d", &hora);

        // Recria a atividade com base nos dados salvos
        Atividade *nova = criarAtividade(temp->nome, hora);
        if (!nova) {
            printf("Erro ao recriar atividade.\n");
            return;
        }

        // Reinsere a atividade na lista do evento
        inserirAtividade(&evento->atividades, nova);
        printf("Desfazer realizado: atividade '%s' foi restaurada no evento '%s'.\n",
               temp->nome, temp->evento_nome);
    }

    // Finaliza: remove o topo da pilha
    pilhaDesfazer = temp->prox;
    free(temp);
}
