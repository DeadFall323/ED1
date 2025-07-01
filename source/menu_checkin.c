#include <stdio.h>
#include <string.h>
#include "../headers/checkin.h"
#include "../headers/eventos.h"
#include "../headers/atividades.h"
#include "../headers/participantes.h"

// Função para realizar check-in dos participantes de forma mais clara e interativa
void realizarCheckin(Fila *fila, Evento *listaEventos) {
    if (!listaEventos) {
        printf("Nenhum evento disponível.\n");
        return;
    }

    // === Etapa 1: Listar eventos ===
    printf("\n=== Eventos Disponíveis ===\n");
    Evento *e = listaEventos;
    int i = 1;
    do {
        printf("%d - %s (%s)\n", i++, e->nome, e->data);
        e = e->prox;
    } while (e != listaEventos);

    // === Etapa 2: Escolher evento por número ===
    printf("Digite o número do evento: ");
    int escolhaEvento;
    scanf("%d", &escolhaEvento);
    getchar();

    e = listaEventos;
    for (int j = 1; j < escolhaEvento; j++) e = e->prox;
    Evento *eventoSelecionado = e;

    // === Etapa 3: Listar atividades ===
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

    // === Etapa 4: Escolher atividade ===
    printf("Digite o número da atividade: ");
    int escolhaAtividade;
    scanf("%d", &escolhaAtividade);
    getchar();

    Atividade *atividadeEscolhida = listaAtividades[escolhaAtividade - 1];

    // === Etapa 5: Listar participantes com índice ===
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

    // === Etapa 6: Escolher participantes por número ===
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
        enfileirar(fila, pEscolhido);
        printf("Check-in realizado para %s!\n", pEscolhido->nome);

        printf("Deseja fazer check-in de outro participante? (s/n): ");
        scanf(" %c", &continuar);
        getchar();
    }
}

// Menu interativo do módulo de check-in
void menuCheckin(Fila *filaCheckin, Evento *listaEventos) {
    int opcao;

    do {
        printf("\n==== MENU DE CHECK-IN ====\n");
        printf("1 - Fazer check-in (evento > atividade > participante)\n");
        printf("2 - Listar fila de check-in\n");
        printf("3 - Chamar próximo da fila\n");
        printf("0 - Voltar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // limpa o ENTER do buffer

        switch (opcao) {
            case 1:
                realizarCheckin(filaCheckin, listaEventos);
                break;
            case 2:
                listarFila(filaCheckin);  // Mostra quem está aguardando check-in
                break;
            case 3:
                desenfileirar(filaCheckin);  // Remove o primeiro da fila (ordem de chegada)
                break;
            case 0:
                printf("Voltando ao menu anterior...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);
}
