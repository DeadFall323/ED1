#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Inclusão dos cabeçalhos das estruturas e módulos do sistema
#include "../headers/eventos.h"
#include "../headers/atividades.h"
#include "../headers/checkin.h"
#include "../headers/desfazer.h"
#include "../headers/participantes.h"

// Variáveis globais compartilhadas entre os módulos
extern NoPilha *pilhaDesfazer;       // Pilha global para desfazer ações
extern Evento *inicio;               // Lista circular de eventos (declarada em eventos.c)
NoAtendido *checkinsRealizados = NULL; // Lista de participantes que já fizeram check-in

// Protótipos dos menus de cada funcionalidade
void menu_participantes();
void menu_eventos();
void menuCheckin(Fila *filaCheckin, Evento *listaEventos);
void menu_atividades();

/*
 * Função principal: ponto de entrada do programa
 * Exibe o menu principal e chama os submenus conforme a escolha do usuário
 */
int main() {
    // Inicializa a fila de check-in e a pilha de desfazer
    Fila filaCheckin;
    inicializarFila(&filaCheckin);
    inicializarPilha(&pilhaDesfazer);

    int opcao;
    do {
        // Menu principal com opções do sistema
        printf("\n--- SISTEMA DE EVENTOS ACADÊMICOS ---\n");
        printf("1. Gerenciar Eventos\n");
        printf("2. Gerenciar Atividades\n");
        printf("3. Gerenciar Participantes\n");
        printf("4. Realizar Check-in\n");
        printf("5. Desfazer Remocao\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        while(getchar() != '\n'); // Limpa o buffer do teclado

        // Direciona para o menu apropriado
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

// ------------------------- MENU EVENTOS -------------------------

// Exibe o menu de gerenciamento de eventos
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
        getchar(); // Limpa o buffer

        switch(opcao){
            case 1: cadastrar_evento(); break;
            case 2: listar_eventos(); break;
            case 3: remover_evento(); break;
            case 0: printf("Retornando ao menu principal...\n"); break;
            default: printf("Opcao invalida. Tente novamente.\n");
        }
    } while(opcao != 0);
}

// ------------------------- MENU ATIVIDADES -------------------------

// Permite gerenciar atividades dentro de um evento
void menu_atividades() {
    if (!inicio) {
        printf("Nenhum evento cadastrado. Cadastre um evento primeiro.\n");
        return;
    }
// Lista os eventos existentes para o usuário escolher
	printf("\nEventos Cadastrados:\n");
	Evento *temp = inicio;
	int count = 1;
	Evento *listaEventos[50];
	do {
    	printf("%d. %s - %s\n", count, temp->nome, temp->data);
    	listaEventos[count - 1] = temp;
    	temp = temp->prox;
    	count++;
	} while (temp != inicio && count <= 50);

	// Escolher por número
	printf("Digite o número do evento: ");
	int escolhaEvento;
	scanf("%d", &escolhaEvento);
	getchar();

	Evento *eventoSelecionado = listaEventos[escolhaEvento - 1];

    if (count == 1) {
        printf("Nenhum evento cadastrado.\n");
        return;
    }

    // Usuário escolhe qual evento vai gerenciar
    //int escolhaEvento;
    //printf("Digite o número do evento: ");
    //scanf("%d", &escolhaEvento);
    //getchar();

    if (escolhaEvento < 1 || escolhaEvento >= count) {
        printf("Evento inválido.\n");
        return;
    }

    //Evento *eventoSelecionado = listaEventos[escolhaEvento - 1];

    int opcao;
    char titulo[100];
    int hora;

    // Menu de atividades do evento escolhido
    do {
        printf("\n--- MENU DE ATIVIDADES DO EVENTO: %s ---\n", eventoSelecionado->nome);
        printf("1. Cadastrar Atividade\n");
        printf("2. Listar Atividades\n");
        printf("3. Remover Atividade\n");
        printf("4. Ordenar Atividades por Horário (MergeSort)\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        while(getchar() != '\n');

        switch(opcao) {
            case 1:
                printf("Digite o titulo da atividade: ");
                fgets(titulo, sizeof(titulo), stdin);
                titulo[strcspn(titulo, "\n")] = 0;

                printf("Digite o horario no formato HHMM (Ex: 16:00 fica 1600): ");
                scanf("%d", &hora);
                getchar();

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
                ordenarAtividades(&eventoSelecionado->atividades);
                printf("Atividades ordenadas com sucesso!\n");
                listarAtividades(eventoSelecionado->atividades);
                break;

            case 0:
                printf("Retornando ao menu principal...\n");
                break;

            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while(opcao != 0);
}

// ------------------------- MENU PARTICIPANTES -------------------------

// Gerencia os participantes dentro de uma atividade de um evento
void menu_participantes() {
    if (!inicio) {
        printf("Nenhum evento cadastrado. Cadastre um evento primeiro.\n");
        return;
    }

    // Lista eventos para o usuário selecionar
    Evento *e = inicio;
    Evento *listaEventos[50];
    int totalEventos = 0;
    int i = 1;
    printf("\nEventos Cadastrados:\n");
    do {
        printf("%d. %s - %s\n", i, e->nome, e->data);
        listaEventos[totalEventos++] = e;
        e = e->prox;
        i++;
    } while (e != inicio);

    int escolhaEvento;
    printf("Digite o número do evento: ");
    scanf("%d", &escolhaEvento);
    getchar();
    if (escolhaEvento < 1 || escolhaEvento > totalEventos) {
        printf("Evento inválido!\n");
        return;
    }
    Evento *evento = listaEventos[escolhaEvento - 1];

    // Lista atividades do evento
    Atividade *a = evento->atividades;
    if (!a) {
        printf("Esse evento não possui atividades cadastradas.\n");
        return;
    }

    Atividade *listaAtividades[50];
    int idx = 0;
    printf("\nAtividades do evento %s:\n", evento->nome);
    while (a && idx < 50) {
        printf("%d - %s (%s)\n", idx + 1, a->titulo, a->horario);
        listaAtividades[idx++] = a;
        a = a->prox;
    }

    int escolha;
    printf("Digite o número da atividade: ");
    scanf("%d", &escolha);
    getchar();

    if (escolha < 1 || escolha > idx) {
        printf("Atividade inválida.\n");
        return;
    }
    Atividade *atividade = listaAtividades[escolha - 1];

    Participante **lista_participantes = &atividade->participantes;

    int opcao;
    char nome[100], email[100], matricula[20];

    // Menu de ações com os participantes
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

                printf("Digite a matricula: ");
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
                remover_participante(evento, atividade, matricula); 
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

// ------------------------- CHECK-IN -------------------------

// Verifica se o participante já está na fila para evitar duplicidade
int participante_ja_na_fila(Fila *fila, Participante *p) {
    NoFila *atual = fila->inicio;
    while (atual) {
        if (strcmp(atual->participante->matricula, p->matricula) == 0)
            return 1;
        atual = atual->prox;
    }
    return 0;
}

// Realiza o processo de check-in: evento → atividade → participante
void realizarCheckin(Fila *fila, Evento *listaEventos) {
    if (!listaEventos) {
        printf("Nenhum evento disponível.\n");
        return;
    }

    // Seleção do evento
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

    // Seleção da atividade
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

    // Exibe participantes disponíveis para check-in
    Participante *listaParticipantes[100];
    int total = 0;
    printf("\n=== Participantes Cadastrados ===\n");
    while (p && total < 100) {
        printf("%d - %s | Matrícula: %s\n", total + 1, p->nome, p->matricula);
        listaParticipantes[total++] = p;
        p = p->prox;
    }

    // Usuário escolhe quem fará check-in
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

// Menu principal do check-in: permite enfileirar, listar, chamar e ver histórico
void menuCheckin(Fila *filaCheckin, Evento *listaEventos) {
    int opcao;
    do {
        printf("\n==== MENU DE CHECK-IN ====\n");
        printf("1 - Fazer check-in\n");
        printf("2 - Listar fila de check-in\n");
        printf("3 - Chamar próximo da fila\n");
        printf("4 - Listar participantes que já fizeram check-in\n");
        printf("0 - Voltar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1: realizarCheckin(filaCheckin, listaEventos); break;
            case 2: listarFila(filaCheckin); break;
            case 3: desenfileirar(filaCheckin); break;
            case 4: listarCheckinsRealizados(checkinsRealizados); break;
            case 0: printf("Voltando ao menu anterior...\n"); break;
            default: printf("Opção inválida!\n");
        }
    } while (opcao != 0);
}
