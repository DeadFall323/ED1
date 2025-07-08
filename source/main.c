
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Bibliotecas do sistema

#include "../headers/eventos.h"
#include "../headers/atividades.h"
#include "../headers/checkin.h"
#include "../headers/desfazer.h"
#include "../headers/ordenacao.h"
#include "../headers/participantes.h"

// Variáveis globais externas
extern NoPilha *pilhaDesfazer;
extern Evento *inicio; // Declarada em eventos.c

// Protótipos de menus
void menu_participantes();
void menu_eventos();
void menuCheckin(Fila *filaCheckin, Evento *listaEventos);
void menu_atividades();

// Função principal
int main() {
    // Criação das estruturas principais
    Fila filaCheckin;
    inicializarFila(&filaCheckin);

    inicializarPilha(&pilhaDesfazer); // Inicializa a pilha global de desfazer

    int opcao;
    do {
        // Menu principal do sistema
        printf("\n--- SISTEMA DE EVENTOS ACADÊMICOS ---\n");
        printf("1. Gerenciar Eventos\n");
        printf("2. Gerenciar Atividades\n");
        printf("3. Gerenciar Participantes\n");
        printf("4. Realizar Check-in\n");
        printf("5. Desfazer Remocao\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        while(getchar() != '\n'); // Limpa o buffer

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

// Menu para gerenciamento de eventos
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
            case 1: cadastrar_evento(); break;
            case 2: listar_eventos(); break;
            case 3: remover_evento(); break;
            case 0: printf("Retornando ao menu principal...\n"); break;
            default: printf("Opcao invalida. Tente novamente.\n");
        }
    } while(opcao != 0);
}

// Menu para gerenciamento de atividades de um evento
void menu_atividades() {
    if (!inicio) {
        printf("Nenhum evento cadastrado. Cadastre um evento primeiro.\n");
        return;
    }

    char nome_evento[100];
    printf("Selecione o Evento a ser editado:\n");
    listar_eventos();
    printf("Digite o nome do evento para gerenciar as atividades: ");
    fgets(nome_evento, sizeof(nome_evento), stdin);
    nome_evento[strcspn(nome_evento, "\n")] = 0;

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

// Menu para gerenciamento de participantes em uma atividade
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

// Verifica se o participante já está na fila de check-in
int participante_ja_na_fila(Fila *fila, Participante *p) {
    NoFila *atual = fila->inicio;
    while (atual) {
        if (strcmp(atual->participante->matricula, p->matricula) == 0)
            return 1;
        atual = atual->prox;
    }
    return 0;
}

// Realiza o processo de check-in por evento e atividade
// Usuário escolhe qual participante enfileirar
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

// Menu de ações relacionadas ao check-in
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
            case 1: realizarCheckin(filaCheckin, listaEventos); break;
            case 2: listarFila(filaCheckin); break;
            case 3: desenfileirar(filaCheckin); break;
            case 0: printf("Voltando ao menu anterior...\n"); break;
            default: printf("Opção inválida!\n");
        }
    } while (opcao != 0);
}
