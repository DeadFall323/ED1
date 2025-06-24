//
// Created by kawandias on 17/06/25.
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>     // Para uso de isdigit
#include "../headers/participantes.h"

// Função principal do menu interativo para gerenciar os participantes
void menu_participantes() {
    Participante *lista_participantes = NULL; // Ponteiro para o início da lista de participantes

    int opcao;                                // Armazena a opção do menu escolhida pelo usuário
    char nome[100], email[100], matricula[20]; // Buffers para entrada de dados do usuário

    do {

        printf("\n--- MENU DE PARTICIPANTES ---\n");
        printf("1. Cadastrar Participante em Atividade\n");
        printf("2. Listar Participantes de uma Atividade\n");
        printf("3. Remover Participante\n");
        printf("4. Ordenar Participantes por Nome (BubbleSort)\n");
        printf("0. Voltar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        while (getchar() != '\n');         // Limpa o buffer do teclado

        switch(opcao) {
            case 1:
                // Cadastro de participante
                printf("Digite o nome: ");
                fgets(nome, sizeof(nome), stdin);              // Lê nome com espaços
                nome[strcspn(nome, "\n")] = '\0';             // Remove o '\n'

                printf("Digite o email: ");
                fgets(email, sizeof(email), stdin);
                email[strcspn(email, "\n")] = '\0';

                printf("Digite a matricula (somente numeros): ");
                fgets(matricula, sizeof(matricula), stdin);
                matricula[strcspn(matricula, "\n")] = '\0';

                Participante *novo = criar_participante(nome, email, matricula); // Valida e cria
                if (novo) {
                    inserir_participante(&lista_participantes, novo); // Inserindo na lista
                    printf("Participante cadastrado com sucesso!\n");
                }
                break;

            case 2:
                // Listagem de participantes
                listar_participantes(lista_participantes);
                break;

            case 3:
                // Remoção de participante pela matrícula
                printf("Digite a matricula do participante a remover: ");
                fgets(matricula, sizeof(matricula), stdin);
                matricula[strcspn(matricula, "\n")] = '\0';
                remover_participante(&lista_participantes, matricula);
                break;

            case 4:
                // Ordenação por nome (BubbleSort)
                ordenar_participantes_bubble(&lista_participantes);
                printf("Participantes ordenados por nome.\n");
                break;

            case 0:
                // Voltar ao menu principal
                printf("Voltando ao menu principal...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while(opcao != 0); // Repete até que a opção 0 seja escolhida
}

// Função para criar um novo participante com validação de dados
Participante* criar_participante(const char *nome, const char *email, const char *matricula) {
    // Verifica se email e matrícula são válidos
    if (!validar_email(email) || !validar_matricula(matricula)) {
        printf("Email ou matricula invalidos.\n");
        return NULL; // Retorna NULL se dados inválidos
    }

    Participante *novo = (Participante *) malloc(sizeof(Participante)); // Aloca memória
    if (!novo) return NULL; // Retorna NULL se falhar

    // Copia os dados para os campos da struct
    strcpy(novo->nome, nome);
    strcpy(novo->email, email);
    strcpy(novo->matricula, matricula);
    novo->ant = NULL;
    novo->prox = NULL;

    return novo; // Retorna ponteiro para o novo participante
}

// Insere um participante no início da lista duplamente encadeada
void inserir_participante(Participante **lista, Participante *novo) {
    if (!novo) return; // Verifica se o ponteiro é válido
    novo->prox = *lista; // O próximo do novo será o atual primeiro
    if (*lista) (*lista)->ant = novo; // Atualiza o anterior do antigo primeiro, se existir
    *lista = novo; // Atualiza o início da lista para o novo nó
}

// Lista todos os participantes da lista
void listar_participantes(Participante *lista) {
    Participante *atual = lista; // Começa do início da lista
    printf("\n--- Participantes ---\n");
    while (atual) {
        // Exibe os dados do participante atual
        printf("Nome: %s | Email: %s | Matricula: %s\n",
               atual->nome, atual->email, atual->matricula);
        atual = atual->prox; // Avança para o próximo
    }
}

// Remove um participante da lista baseado na matrícula
void remover_participante(Participante **lista, const char *matricula) {
    Participante *atual = *lista;

    // Percorre até encontrar a matrícula
    while (atual && strcmp(atual->matricula, matricula) != 0)
        atual = atual->prox;

    if (!atual) {
        printf("Participante nao encontrado.\n");
        return;
    }
    printf("Participante %s Removido com sucesso!", atual->nome);
    // ajustando os ponteiros da lista
    if (atual->ant)
        atual->ant->prox = atual->prox;
    else
        *lista = atual->prox;

    if (atual->prox)
        atual->prox->ant = atual->ant;

    free(atual); // liberando a memória do nó removido
    //printf("Participante removido.\n");
}

// Ordena os participantes alfabeticamente por nome usando Bubble Sort
void ordenar_participantes_bubble(Participante **lista) {
    if (!lista || !*lista) return; // Lista vazia ou inexistente

    int trocou;
    do {
        trocou = 0;
        Participante *atual = *lista;
        while (atual && atual->prox) {
            // Compara nomes dos nós consecutivos
            if (strcmp(atual->nome, atual->prox->nome) > 0) {
                // Troca apenas os dados, não os ponteiros
                Participante temp = *atual;
                strcpy(atual->nome, atual->prox->nome);
                strcpy(atual->email, atual->prox->email);
                strcpy(atual->matricula, atual->prox->matricula);

                strcpy(atual->prox->nome, temp.nome);
                strcpy(atual->prox->email, temp.email);
                strcpy(atual->prox->matricula, temp.matricula);
                trocou = 1; // Indica que houve troca
            }
            atual = atual->prox; // Avança na lista
        }
    } while (trocou); // Continua até não haver mais trocas
}

// Validação simples de e-mail (deve conter '@' e '.') usando a funcao pronta de string.h
int validar_email(const char *email) {
    return strchr(email, '@') && strchr(email, '.');
}

// Verifica se a matrícula é composta apenas por números e possui tamanho aceitável
// Essa parte eh modular, para mudar o tamanho da matricula eh so mudar: int tamanho_matricula = 5;
int validar_matricula(const char *matricula) {
    int len = strlen(matricula);
    int tamanho_matricula = 5;
    if (len < tamanho_matricula || len > 20) return 0; // Tamanho inválido
    for (int i = 0; i < len; i++) {
        if (!isdigit(matricula[i])) return 0; // Caracter não numérico v
    }
    return 1; // Matrícula válida
}