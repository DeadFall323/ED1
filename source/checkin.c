#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/checkin.h"
#include "../headers/eventos.h"
#include "../headers/atividades.h"
#include "../headers/participantes.h"

// ------------------
// Estrutura da fila
// ------------------

void inicializarFila(Fila *fila) {
    fila->inicio = NULL;
    fila->fim = NULL;
}

void enfileirar(Fila *fila, Participante *p) {
    NoFila *novo = (NoFila *)malloc(sizeof(NoFila));
    novo->participante = p;
    novo->prox = NULL;

    if (fila->fim == NULL) {
        fila->inicio = novo;
        fila->fim = novo;
    } else {
        fila->fim->prox = novo;
        fila->fim = novo;
    }
}

void desenfileirar(Fila *fila) {
    if (fila->inicio == NULL) {
        printf("Fila vazia!\n");
        return;
    }

    NoFila *temp = fila->inicio;
    printf("Removendo da fila: %s - %s\n", temp->participante->nome, temp->participante->matricula);

    fila->inicio = fila->inicio->prox;
    if (fila->inicio == NULL) {
        fila->fim = NULL;
    }

    free(temp);
}

void listarFila(Fila *fila) {
    NoFila *aux = fila->inicio;
    if (aux == NULL) {
        printf("Fila vazia.\n");
        return;
    }

    printf("Fila de check-in:\n");
    while (aux != NULL) {
        printf("Nome: %s | Matrícula: %s | E-mail: %s\n",
               aux->participante->nome,
               aux->participante->matricula,
               aux->participante->email);
        aux = aux->prox;
    }
}

// --------------------------------
// Funções interativas do check-in
// --------------------------------

int participante_ja_na_fila(Fila *fila, Participante *p) {
    NoFila *atual = fila->inicio;
    while (atual) {
        if (strcmp(atual->participante->matricula, p->matricula) == 0)
            return 1;
        atual = atual->prox;
    }
    return 0;
}

void realizarCheckin(Fila *fila, Evento *listaEventos) {
    if (!listaEventos) {
        printf("Nenhum evento disponível.\n");
        return;
    }

    printf("\n=== Eventos Disponíveis ===\n");
    Evento *e = listaEventos;
    int i = 1;
    do {
        printf("%d - %s (%s)\n", i++, e->nome, e->data);
        e = e->prox;
    } while (e != listaEventos);

    printf("Digite o número do evento: ");
    int escolhaEvento;
    scanf("%d", &escolhaEvento);
    getchar();

    e = listaEventos;
    for (int j = 1; j < escolhaEvento; j++) e = e->prox;
    Evento *eventoSelecionado = e;

    Atividade *a = eventoSelecionado->atividades;
    if (!a) {
        printf("Este evento não possui atividades.\n");
        return;
    }

    printf("\n=== Atividades do Evento ===\n");
    Atividade *listaAtividades[20];
    int idx = 0;
    while (a && idx < 20) {
        printf("%d - %s (%s)\n", idx + 1, a->titulo, a->horario);
        listaAtividades[idx++] = a;
        a = a->prox;
    }

    printf("Digite o número da atividade: ");
    int escolhaAtividade;
    scanf("%d", &escolhaAtividade);
    getchar();

    Atividade *atividadeEscolhida = listaAtividades[escolhaAtividade - 1];
    Participante *p = atividadeEscolhida->participantes;

    if (!p) {
        printf("Nenhum participante cadastrado nesta atividade.\n");
        return;
    }

    Participante *listaParticipantes[100];
    int total = 0;
    printf("\n=== Participantes Cadastrados ===\n");
    while (p && total < 100) {
        printf("%d - %s | Matrícula: %s\n", total + 1, p->nome, p->matricula);
        listaParticipantes[total++] = p;
        p = p->prox;
    }

    char continuar = 's';
    while (continuar == 's' || continuar == 'S') {
        printf("Digite o número do participante que chegou (0 para sair): ");
        int escolha;
        scanf("%d", &escolha);
        getchar();

        if (escolha == 0) break;

        if (escolha < 1 || escolha > total) {
            printf("Número inválido.\n");
            continue;
        }

        Participante *pEscolhido = listaParticipantes[escolha - 1];
        if (!participante_ja_na_fila(fila, pEscolhido)) {
            enfileirar(fila, pEscolhido);
            printf("Check-in realizado para %s!\n", pEscolhido->nome);
        } else {
            printf("%s já está na fila de check-in.\n", pEscolhido->nome);
        }

        printf("Deseja fazer check-in de outro participante? (s/n): ");
        scanf(" %c", &continuar);
        getchar();
    }
}

void menuCheckin(Fila *filaCheckin, Evento *listaEventos) {
    int opcao;
    do {
        printf("\n==== MENU DE CHECK-IN ====\n");
        printf("1 - Fazer check-in\n");
        printf("2 - Listar fila de check-in\n");
        printf("3 - Chamar próximo da fila\n");
        printf("0 - Voltar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                realizarCheckin(filaCheckin, listaEventos);
                break;
            case 2:
                listarFila(filaCheckin);
                break;
            case 3:
                desenfileirar(filaCheckin);
                break;
            case 0:
                printf("Voltando ao menu anterior...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);
}
