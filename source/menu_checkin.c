#include <stdio.h>
#include <string.h>
#include "../headers/checkin.h"
#include "../headers/eventos.h"
#include "../headers/atividades.h"
#include "../headers/participantes.h"

// Função para fazer check-in baseado nos participantes já cadastrados
void realizarCheckin(Fila *fila, Evento *listaEventos) {
    Evento *evento = selecionarEvento(listaEventos); // Você já deve ter essa função em eventos.c
    if (evento == NULL || evento->atividades == NULL) {
        printf("Evento inválido ou sem atividades cadastradas.\n");
        return;
    }

    Atividade *atividade = evento->atividades;
    while (atividade != NULL) {
        Participante *p = atividade->participantes;
        while (p != NULL) {
            printf("\nParticipante: %s | Matrícula: %s\n", p->nome, p->matricula);
            printf("Deseja realizar check-in para este participante? (s/n): ");
            char opcao;
            scanf(" %c", &opcao);

            if (opcao == 's' || opcao == 'S') {
                enfileirar(fila, p);
                printf("Check-in realizado para %s!\n", p->nome);
            }

            p = p->prox;
        }
        atividade = atividade->prox;
    }
}

// Menu de check-in atualizado
void menuCheckin(Fila *fila, Evento *listaEventos) {
    int opcao;

    do {
        printf("\n==== MENU DE CHECK-IN ====\n");
        printf("1 - Fazer check-in (selecionar evento > participantes)\n");
        printf("2 - Listar fila\n");
        printf("3 - Chamar próximo da fila (realizar check-in)\n");
        printf("0 - Voltar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o ENTER do buffer

        switch (opcao) {
            case 1:
                realizarCheckin(fila, listaEventos);
                break;

            case 2:
                listarFila(fila);
                break;

            case 3:
                desenfileirar(fila);
                break;

            case 0:
                printf("Voltando ao menu anterior...\n");
                break;

            default:
                printf("Opção inválida. Tente novamente.\n");
        }

    } while (opcao != 0);
}
