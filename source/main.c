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
 
NoPilha *pilhaDesfazer = NULL; // pilha global usada no desfazer
extern Evento *inicio; // declaracao externa pra usar variavel de eventos.c


// Declaração dos menus
void menu_participantes();
void menu_eventos();
void menuCheckin(Fila *filaCheckin, Evento *listaEventos);
void menu_atividades();

int main() {
    //saudacao();
    // Criar listas
    Fila filaCheckin;
    inicializarFila(&filaCheckin);
    
    extern NoPilha *pilhaDesfazer;
    inicializarPilha(&pilhaDesfazer); // ← inicializa a pilha global

    Participante *lista_participantes = NULL;


    int opcao;
    do {
        printf("\n--- SISTEMA DE EVENTOS ACADÊMICOS ---\n");
        printf("1. Gerenciar Eventos\n");
        printf("2. Gerenciar Atividades\n");
        printf("3. Gerenciar Participantes\n");
        printf("4. Realizar Check-in\n");
        printf("5. Desfazer Remocao\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        while(getchar() != '\n');

        switch(opcao) {
            case 1: menu_eventos(); break;
            case 2: menu_atividades(); break;
            case 3: menu_participantes(); break;
            case 4: menuCheckin(&filaCheckin, inicio); break;
            case 5: desfazer_remocao(); break;
            case 0: printf("Encerrando...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while(opcao != 0);
    return 0;
}

void menu_eventos(){
    int opcao;
    do{
        printf("\n--- MENU DE EVENTOS ---\n");
        printf("1. Cadastrar Evento\n");
        printf("2. Listar Eventos\n");
        printf("3. Remover Evento\n");
        printf("0. Voltar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao){
            case 1:
                cadastrar_evento();
                break;
            case 2:
                listar_eventos();
                break;
            case 3:
                remover_evento();
                break;
            case 0:
                printf("Retornando ao menu principal...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    }while(opcao != 0);
}

// menu de atividades adicionado
void menu_atividades() {
    if (!inicio) {
        printf("Nenhum evento cadastrado. Cadastre um evento primeiro.\n");
        return;
    }

    char nome_evento[100];
    printf("Digite o nome do evento para gerenciar as atividades: ");
    fgets(nome_evento, sizeof(nome_evento), stdin);
    nome_evento[strcspn(nome_evento, "\n")] = 0; // Remove o '\n'

    //adicionado para buscar evento
    Evento *eventoSelecionado = buscar_evento(nome_evento);


    if (!eventoSelecionado) {
        printf("Evento '%s' nao encontrado.\n", nome_evento);
        return;
    }

    int opcao;
    char titulo[100];
    int hora;

    do { 
        printf("\n--- MENU DE ATIVIDADES DO EVENTO: %s ---\n", eventoSelecionado->nome);
        printf("1. Cadastrar Atividade\n");
        printf("2. Listar Atividades\n");
        printf("3. Remover Atividade\n");
        printf("4. Ordenar Atividades por Horário (MergeSort)\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        while(getchar() != '\n'); // limpar buffer

        switch(opcao) {
            case 1:
               printf("Digite o titulo da atividade: ");
               fgets(titulo, sizeof(titulo), stdin);
               titulo[strcspn(titulo, "\n")] = 0;


                printf("Digite o horario (formato HHMM, ex: 1430 para 14:30): ");
                scanf("%d", &hora);

                // Chama a função para inserir a atividade na lista do evento selecionado
                inserirAtividade(&eventoSelecionado->atividades, criarAtividade(titulo, hora));
                break;

            case 2:
                listarAtividades(eventoSelecionado->atividades);
                break;

            case 3:
                printf("Digite o titulo da atividade a ser removida: ");
                fgets(titulo, sizeof(titulo), stdin);
                titulo[strcspn(titulo, "\n")] = 0;

                removerAtividade(eventoSelecionado, &eventoSelecionado->atividades, titulo);
                break;

            case 4:
                // Chama a função de ordenação recursiva
                ordenarAtividades(&eventoSelecionado->atividades);
                printf("Atividades ordenadas por horario com sucesso!\n");
                listarAtividades(eventoSelecionado->atividades); // Mostra a lista ordenada
                break;

            case 0:
                printf("Retornando ao menu principal...\n");
                break;

            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while(opcao != 0);
}

void menu_checkin(Fila *filaCheckin) {
    int opcao;

    do {
        printf("\n--- MENU DE CHECK-IN ---\n");
        printf("1. Realizar Check-in de Participante\n");
        printf("2. Listar Fila de Check-in\n");
        printf("3. Chamar proximo da fila (realizar check-in)\n");
        printf("0. Voltar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpa ENTER

        switch(opcao) {
            case 1:
                // Aqui chama o que está em menu_checkin.c
                realizarCheckin(filaCheckin, inicio);
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
                printf("Opcao invalida!\n");
        }
    } while(opcao != 0);
}
