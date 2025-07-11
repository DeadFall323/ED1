#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/desfazer.h"
#include "../headers/eventos.h"       // Necessário para localizar eventos
#include "../headers/atividades.h"    // Necessário para criar atividades
#include "../headers/participantes.h" // Necessário para criar participantes

// Pilha global utilizada para armazenar operações de remoção
NoPilha *pilhaDesfazer;

// ---------------------------------------------
// Função: inicializarPilha
// Objetivo: Inicializa a pilha de desfazer (define topo como NULL)
// ---------------------------------------------
void inicializarPilha(NoPilha **topo) {
    *topo = NULL;
}

// ---------------------------------------------
// Função: empilhar
// Objetivo: Armazena uma nova operação de remoção na pilha
// Parâmetros:
// - tipo: "participante" ou "atividade"
// - nome, email, infoExtra, atividade, evento: informações para restauração
// ---------------------------------------------
void empilhar(NoPilha **topo, char tipo[], char nome[], char email[], char infoExtra[], char atividade[], char evento[]) {
    NoPilha *novo = (NoPilha *)malloc(sizeof(NoPilha));
    if (!novo) {
        printf("Erro ao alocar memória para a pilha.\n");
        return;
    }

    // Copia os dados para o novo nó
    strcpy(novo->tipo, tipo);
    strcpy(novo->nome, nome);
    strcpy(novo->email, email);
    strcpy(novo->infoExtra, infoExtra);
    strcpy(novo->atividade_titulo, atividade);
    strcpy(novo->evento_nome, evento);

    // Insere no topo da pilha
    novo->prox = *topo;
    *topo = novo;
}

// ---------------------------------------------
// Função: listarPilha
// Objetivo: Exibe todos os itens empilhados (para debug ou visualização)
// ---------------------------------------------
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

// ---------------------------------------------
// Função: desfazer_remocao
// Objetivo: Reverte a última operação de remoção registrada na pilha
// Suporta dois tipos: participante e atividade
// ---------------------------------------------
void desfazer_remocao() {
    if (pilhaDesfazer == NULL) {
        printf("Pilha vazia, nada para desfazer.\n");
        return;
    }

    NoPilha *temp = pilhaDesfazer;

    // ---------- Desfazer Remoção de Participante ----------
    if (strcmp(temp->tipo, "participante") == 0) {
        // Localiza o evento onde o participante estava
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

        // Recria o participante usando os dados armazenados
        Participante *restaurado = criar_participante(temp->nome, temp->email, temp->infoExtra);
        if (!restaurado) {
            printf("Erro ao recriar participante.\n");
            return;
        }

        // Reinsere o participante na lista original
        inserir_participante(&atividade->participantes, restaurado);

        printf("Desfazer realizado: participante '%s' foi restaurado na atividade '%s' do evento '%s'.\n",
               temp->nome, temp->atividade_titulo, temp->evento_nome);
    }

    // ---------- Desfazer Remoção de Atividade ----------
    else if (strcmp(temp->tipo, "atividade") == 0) {
        // Localiza o evento onde a atividade foi removida
        Evento *evento = buscar_evento(temp->evento_nome);
        if (!evento) {
            printf("Evento '%s' não encontrado ao desfazer.\n", temp->evento_nome);
            return;
        }

        // Converte o horário salvo (string) de volta para inteiro
        int hora;
        sscanf(temp->infoExtra, "%d", &hora);

        // Recria a atividade com os dados salvos
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

    // ---------- Remoção do topo da pilha ----------
    pilhaDesfazer = temp->prox;
    free(temp);  // Libera memória do item restaurado
}
