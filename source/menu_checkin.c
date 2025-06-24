#include <stdio.h>
#include <string.h>
#include "../headers/checkin.h"

void menuCheckin(Fila *fila) {
    int opcao;
    char nome[100];
    char matricula[20];

    do {
        printf("\n==== MENU DE CHECK-IN ====\n");
        printf("1 - Fazer check-in (entrar na fila)\n");
        printf("2 - Listar fila\n");
        printf("3 - Chamar próximo da fila (realizar check-in)\n");
        printf("0 - Voltar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o ENTER que fica no buffer

        switch (opcao) {
            case 1:
                printf("Nome: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0'; // Remove ENTER

                printf("Matrícula: ");
                fgets(matricula, sizeof(matricula), stdin);
                matricula[strcspn(matricula, "\n")] = '\0';

                enfileirar(fila, nome, matricula);
                printf("Check-in realizado!\n");
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
