//
// Created by kawandias on 17/06/25.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../headers/eventos.h"

// Ponteiro global para o início da lista circular de eventos
Evento *inicio = NULL;

// Mensagem de boas-vindas ao iniciar o sistema
void saudacao(){
    printf("\nSistema de Eventos Academicos iniciado com sucesso!\n");
}

// Valida se a data está no formato correto e com valores plausíveis (dd/mm/aaaa)
int validar_data(const char *data){
    if(strlen(data) != 10) return 0; // Verifica se tem exatamente 10 caracteres (ex: "01/01/2025")
    if(data[2] != '/' || data[5] != '/') return 0; // Verifica se os separadores '/' estão nas posições corretas

    int d, m, a;
    if(sscanf(data, "%2d/%2d/%4d", &d, &m, &a) != 3) return 0; // Lê os valores de dia, mês e ano
    if(d < 1 || d > 31 || m < 1 || m > 12 || a < 1900) return 0; // Verifica se os valores extraídos são válidos

    return 1; // Se tudo estiver correto, retorna 1 (válido)
}

// Verifica se o nome digitado tem pelo menos um caractere não vazio
int validar_nome(const char *nome){
    if(nome == NULL) return 0; // Verifica se é nulo
    // Percorre a string para ver se há algum caractere diferente de espaço
    for(int i = 0; nome[i] != '\0'; i++){
        if(!isspace(nome[i])) return 1; // Retorna 1 se encontrar algum caractere que não seja espaço
    }
    return 0;
}

// Cadastra um novo evento e insere na lista circular
void cadastrar_evento(){
    Evento *novo = malloc(sizeof(Evento)); // Aloca memória para o novo evento
    if(!novo){
        printf("\nErro ao alocar memoria\n");
        return; // Encerra se falhar a alocação
    }
    
    // Lê o nome do evento
    printf("Digite o nome do evento: ");
    fgets(novo->nome, MAX_NOME, stdin); // Lê do teclado com proteção de tamanho
    novo->nome[strcspn(novo->nome, "\n")] = '\0'; // Remove o '\n' do final


    if(!validar_nome(novo->nome)){ // Valida o nome
        printf("\nNome invalido!\n");
        free(novo); // Libera memória alocada se inválido
        return;
    }

    // Lê a data do evento
    printf("Digite a data do evento (dd/mm/aaaa): ");
    fgets(novo->data, MAX_DATA, stdin);
    novo->data[strcspn(novo->data, "\n")] = '\0'; // Remove o '\n'

    if(!validar_data(novo->data)){ // Valida a data
        printf("\nData invalida!\n");
        free(novo);
        return;
    }

    novo->atividades = NULL; // Inicializa lista de atividades do evento
    novo->prox = NULL; // Inicializa o ponteiro para o próximo evento

    // Inserção na lista circular de eventos
    if(!inicio){ // Se a lista estiver vazia
        inicio = novo; // Caso seja o primeiro evento
        novo->prox = inicio; // Aponta para si mesmo
    }else{
        Evento *atual = inicio;
        while (atual->prox != inicio) // Percorre até o último nó
            atual = atual->prox;
        atual->prox = novo; // Insere o novo evento no final
        novo->prox = inicio; // Fecha o ciclo da lista circular
    }

    printf("\nEvento cadastrado com sucesso!\n");
}

// Lista todos os eventos cadastrados
void listar_eventos(){
    if(!inicio){
        printf("\nNenhum evento cadastrado\n");
        return;
    }

    Evento *atual = inicio;
    int i = 1;

    printf("\nEventos Cadastrados:\n");
    do{
        printf("%d. %s - %s\n", i++, atual->nome, atual->data); // Imprime número, nome e data
        atual = atual->prox; // Avança na lista
    }while(atual != inicio); // Até voltar ao início (lista circular)
    printf("\n");
}

// Remove um evento da lista circular com base no nome informado
void remover_evento(){
    if(!inicio){
        printf("\nNenhum evento para remover\n");
        return;
    }

    listar_eventos(); // Mostra os eventos para o usuário
    printf("Digite o nome do evento a ser removido: ");
    char nome[MAX_NOME];
    fgets(nome, MAX_NOME, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    Evento *atual = inicio;
    Evento *anterior = NULL;

    // Percorre a lista circular
    do{
        // Compara o nome informado com o nome do evento atual
        if(strcmp(atual->nome, nome) == 0){ // Evento encontrado
            if(atual == inicio && atual->prox == inicio){
                // Único evento na lista
                free(atual);
                inicio = NULL;
            }else if(atual == inicio){
                // Evento no início, com outros elementos
                Evento *ultimo = inicio;
                while (ultimo->prox != inicio)
                    ultimo = ultimo->prox;
                inicio = atual->prox;
                ultimo->prox = inicio;
                free(atual);
            }else{
                // Evento no meio ou fim
                anterior->prox = atual->prox;
                free(atual);
            }

            printf("\nEvento removido com sucesso\n");
            return;
        }
        anterior = atual; // Guarda o anterior
        atual = atual->prox; // Avança na lista
    }while(atual != inicio); // Percorre toda a lista até voltar ao início

    printf("\nEvento nao encontrado\n");
}

// Busca um evento pelo nome
Evento *buscar_evento(const char *nome){
    if(!inicio) return NULL;

    Evento *atual = inicio;
    // Percorre lista circular procurando nome igual
    do{
        if(strcmp(atual->nome, nome) == 0){
            return atual; // Retorna o evento se o nome bater
        }
        atual = atual->prox;
    }while(atual != inicio); // Percorre até voltar ao início

    return NULL;
}

// Permite ao usuário selecionar um evento pela posição (usado no menu de check-in)
Evento* selecionarEvento(Evento *listaEventos) {
    if (listaEventos == NULL) {
        printf("Nenhum evento cadastrado.\n");
        return NULL;
    }

    Evento *atual = listaEventos;
    int contador = 1;

    printf("\n=== Lista de Eventos ===\n");
    do {
        printf("%d - %s (%s)\n", contador, atual->nome, atual->data);
        atual = atual->prox;
        contador++;
    } while (atual != listaEventos);

    int escolha;
    printf("Digite o numero do evento desejado: ");
    scanf("%d", &escolha);
    getchar(); // limpa o ENTER do buffer

    if (escolha <= 0 || escolha >= contador) {
        printf("Opcao invalida.\n");
        return NULL;
    }

    atual = listaEventos;
    for (int i = 1; i < escolha; i++) {
        atual = atual->prox;
    }

    return atual;
}