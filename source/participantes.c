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
#include "../headers/desfazer.h" // ADICIONADO para acessar a pilha

extern Evento *inicio;
extern Pilha *pilhaDesfazer; // ADICIONADO para usar a pilha global

// Função principal do menu interativo para gerenciar os participantes
void menu_participantes() {
    if (!inicio) {
        printf("Nenhum evento cadastrado. Cadastre um evento primeiro.\n");
        return;
    }

    char nome_evento[100], titulo_atividade[100];

    listar_eventos();
    printf("Digite o nome do evento: ");
    fgets(nome_evento, sizeof(nome_evento), stdin);
    nome_evento[strcspn(nome_evento, "\n")] = '\0';

    Evento *evento = buscar_evento(nome_evento);
    if (!evento) {
        printf("Evento não encontrado!\n");
        return;
    }

    printf("Digite o título da atividade: ");
    fgets(titulo_atividade, sizeof(titulo_atividade), stdin);
    titulo_atividade[strcspn(titulo_atividade, "\n")] = '\0';

    Atividade *atividade = evento->atividades;
    while (atividade && strcmp(atividade->titulo, titulo_atividade) != 0)
        atividade = atividade->prox;

    if (!atividade) {
        printf("Atividade não encontrada!\n");
        return;
    }

    Participante **lista_participantes = &atividade->participantes;

    int opcao;
    char nome[100], email[100], matricula[20];

    do {
        printf("\n--- MENU DE PARTICIPANTES DA ATIVIDADE '%s' ---\n", atividade->titulo);
        printf("1. Cadastrar Participante\n");
        printf("2. Listar Participantes\n");
        printf("3. Remover Participante\n");
        printf("4. Ordenar Participantes por Nome (BubbleSort)\n");
        printf("0. Voltar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        while (getchar() != '\n');

        switch(opcao) {
            case 1:
                printf("Digite o nome: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';

                printf("Digite o email: ");
                fgets(email, sizeof(email), stdin);
                email[strcspn(email, "\n")] = '\0';

                printf("Digite a matricula (somente numeros): ");
                fgets(matricula, sizeof(matricula), stdin);
                matricula[strcspn(matricula, "\n")] = '\0';

                Participante *novo = criar_participante(nome, email, matricula);
                if (novo) {
                    inserir_participante(lista_participantes, novo);
                    printf("Participante cadastrado com sucesso!\n");
                }
                break;

            case 2:
                listar_participantes(*lista_participantes);
                break;

            case 3:
                printf("Digite a matricula do participante a remover: ");
                fgets(matricula, sizeof(matricula), stdin);
                matricula[strcspn(matricula, "\n")] = '\0';
                remover_participante(lista_participantes, matricula);
                break;

            case 4:
                ordenar_participantes_bubble(lista_participantes);
                printf("Participantes ordenados por nome.\n");
                break;

            case 0:
                printf("Voltando...\n");
                break;

            default:
                printf("Opção inválida!\n");
        }

    } while(opcao != 0);
}

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

void inserir_participante(Participante **lista, Participante *novo) {
    if (!novo) return;
    novo->prox = *lista;
    if (*lista) (*lista)->ant = novo;
    *lista = novo;
}

void listar_participantes(Participante *lista) {
    Participante *atual = lista;
    printf("\n--- Participantes ---\n");
    while (atual) {
        printf("Nome: %s | Email: %s | Matricula: %s\n",
               atual->nome, atual->email, atual->matricula);
        atual = atual->prox;
    }
}

// 🔁 ESTA É A ÚNICA FUNÇÃO MODIFICADA
void remover_participante(Participante **lista, const char *matricula) {
    Participante *atual = *lista;

    while (atual && strcmp(atual->matricula, matricula) != 0)
        atual = atual->prox;

    if (!atual) {
        printf("Participante nao encontrado.\n");
        return;
    }

    // ✅ REGISTRA NA PILHA ANTES DE APAGAR
    empilhar(pilhaDesfazer, "participante", atual->nome, atual->matricula);

    printf("Participante %s Removido com sucesso!\n", atual->nome);

    if (atual->ant)
        atual->ant->prox = atual->prox;
    else
        *lista = atual->prox;

    if (atual->prox)
        atual->prox->ant = atual->ant;

    free(atual);
}

void ordenar_participantes_bubble(Participante **lista) {
    if (!lista || !*lista) return;

    int trocou;
    do {
        trocou = 0;
        Participante *atual = *lista;
        while (atual && atual->prox) {
            if (strcmp(atual->nome, atual->prox->nome) > 0) {
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

int validar_email(const char *email) {
    return strchr(email, '@') && strchr(email, '.');
}

int validar_matricula(const char *matricula) {
    int len = strlen(matricula);
    int tamanho_matricula = 5;
    if (len < tamanho_matricula || len > 20) return 0;
    for (int i = 0; i < len; i++) {
        if (!isdigit(matricula[i])) return 0;
    }
    return 1;
}
