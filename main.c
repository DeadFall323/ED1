//Declaração das bibliotecas essenciais
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Declaração das bibliotecas secundarias
#include "../headers/eventos.h"
#include "../headers/atividades.h"
#include "../headers/checkin.h"
#include "../headers/desfazer.h"
#include "../headers/ordenacao.h"
#include "../headers/participantes.h"

// Declaração dos menus
void menu_participantes();
void menu_eventos();
void menu_ordenacao();
void menu_checkin(Fila *filaCheckin);
void menu_atividades();

int main() {

    // Criar listas
    Fila filaCheckin;
    inicializarFila(&filaCheckin);

    Participante *lista_participantes = NULL;


    int opcao;
    do {
        printf("\n--- SISTEMA DE EVENTOS ACADÊMICOS ---\n");
        printf("1. Gerenciar Eventos\n");
        printf("2. Gerenciar Atividades\n");
        printf("3. Gerenciar Participantes\n");
        printf("4. Realizar Check-in\n");
        printf("5. Desfazer Remocao\n");
        printf("6. Ordenar\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        while(getchar() != '\n');

        switch(opcao) {
            case 1: menu_eventos(); break;
            case 2: menu_atividades(); break;
            case 3: menu_participantes(); break;
            case 4: menu_checkin(&filaCheckin); break;
            case 5: printf("desfazer_remocao()\n"); break;
            case 6: menu_ordenacao(); break;
            case 0: printf("Encerrando...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while(opcao != 0);
    return 0;
}

// 🔹 ATENÇÃO → As funções abaixo NÃO FORAM ALTERADAS, estão exatamente como estavam.

// A função menu_eventos foi alterada

void menu_eventos() {
    int opcao;
    do {
        printf("\n--- MENU DE EVENTOS ---\n");
        printf("1. Cadastrar Evento\n");
        printf("2. Listar Eventos\n");
        printf("3. Remover Evento\n");
        printf("0. Voltar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao) {
            case 1:
                cadastrar_evento();
                break;
            case 2:
                printf("listar_eventos\n");
                break;
            case 3:
                printf("remover_evento\n");
                break;
            case 0:
                printf("Retornando ao menu principal...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while(opcao != 0);
}

void menu_atividades() {
    int opcao;
    do {
        printf("\n--- MENU DE ATIVIDADES ---\n");
        printf("1. Cadastrar Atividade em Evento\n");
        printf("2. Listar Atividades de um Evento\n");
        printf("3. Remover Atividade\n");
        printf("0. Voltar\n");
        scanf("%d", &opcao);
        switch(opcao) {
            case 1: printf(" cadastrar_atividade()\n"); break;
            case 2: printf(" listar_atividades()\n"); break;
            case 3: printf(" remover_atividade() \n"); break;
        }
    } while(opcao != 0);
}

void menu_checkin(Fila *filaCheckin) {
    int opcao;
    char nome[100];
    char matricula[20];

    do {
        printf("\n--- MENU DE CHECK-IN ---\n");
        printf("1. Realizar Check-in de Participante\n");
        printf("2. Listar Fila de Check-in\n");
        printf("3. Chamar próximo da fila (realizar check-in)\n");
        printf("0. Voltar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // Limpa ENTER

        switch(opcao) {
            case 1:
                printf("Nome: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';

                printf("Matrícula: ");
                fgets(matricula, sizeof(matricula), stdin);
                matricula[strcspn(matricula, "\n")] = '\0';

                enfileirar(filaCheckin, nome, matricula);
                printf("Check-in realizado!\n");
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
    } while(opcao != 0);
}

void menu_ordenacao() {
    int opcao;
    do {
        printf("\n--- MENU DE ORDENAÇÃO ---\n");
        printf("1. Ordenar Atividades por Horário (Recursivo)\n");
        printf("2. Ordenar Participantes por Nome (Iterativo)\n");
        printf("0. Voltar\n");
        scanf("%d", &opcao);
        switch(opcao) {
            case 1: printf(" ordenar_atividades()\n"); break;
            case 2: printf(" ordenar_participantes()\n"); break;
        }
    } while(opcao != 0);
}
