#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/atividades.h"
#include "../headers/desfazer.h"  // Adicionado para usar a pilha de desfazer

extern Pilha *pilhaDesfazer;  // Declara a pilha usada em todo o sistema

Atividade *merge(Atividade *a, Atividade *b) {
    if (!a) return b;
    if (!b) return a;

    Atividade *resultado = NULL;

    if (a->hora <= b->hora) {
        resultado = a;
        resultado->prox = merge(a->prox, b);
    } else {
        resultado = b;
        resultado->prox = merge(a, b->prox);
    }
    return resultado;
}


// Divide uma lista encadeada em duas metades.
// a função implementa a etapa de Divisão
// origem é A lista original a ser dividida.
// frente é o Ponteiro para a primeira metade da lista.
// tras Ponteiro para a segunda metade da lista.

void dividir(Atividade *origem, Atividade **frente, Atividade **tras) {
    if (!origem || !origem->prox) {
        *frente = origem;
        *tras = NULL;
        return;
    }

    Atividade *lento = origem;
    Atividade *rapido = origem->prox;

    // O ponteiro 'rapido' avança dois nós por vez, enquanto 'lento' avança um.
    // Quando 'rapido' chegar ao fim, 'lento' estará no meio.
    while (rapido) {
        rapido = rapido->prox;
        if (rapido) {
            lento = lento->prox;
            rapido = rapido->prox;
        }
    }

    *frente = origem;
    *tras = lento->prox;
    lento->prox = NULL;
}

void ordenarAtividades(Atividade **lista) {
    Atividade *cabeca = *lista;
    if (!cabeca || !cabeca->prox) return;

    Atividade *a;
    Atividade *b;
    dividir(cabeca, &a, &b);
    ordenarAtividades(&a);
    ordenarAtividades(&b);
    *lista = merge(a, b);
}


//Cria um novo nó de atividade, preenchendo os dois campos de horário.
Atividade *criarAtividade(char titulo[], int hora) {
    Atividade *nova = (Atividade *)malloc(sizeof(Atividade));
    if (!nova) {
        printf("Erro de alocação de memória!\n");
        return NULL;
    }
    strcpy(nova->titulo, titulo);


    // Preenche o  campo 'int hora' p/ ajudar a ordenação.
    nova->hora = hora;

    // converte e preenche o campo 'char horario[]' de kawan.
    // A função snprintf formata o inteiro como "HH:MM".
    snprintf(nova->horario, sizeof(nova->horario), "%02d:%02d", hora / 100, hora % 100);

    // Inicializa os ponteiros
    nova->participantes = NULL; 
    nova->prox = NULL;

    return nova;
}



int verificarConflito(Atividade *lista, int hora) {
    Atividade *atual = lista;
    while (atual) {
        if (atual->hora == hora) {
            return 1; // Conflito encontrado
        }
        atual = atual->prox;
    }
    return 0; // Sem conflito
}

void inserirAtividade(Atividade **lista, Atividade *nova) {
    if (verificarConflito(*lista, nova->hora)) {
        printf("Conflito de horário! Já existe uma atividade às %02d:%02d.\n", nova->hora / 100, nova->hora % 100);
        free(nova); // Libera a memória da atividade não inserida
        return;
    }
    // Insere no início da lista
    nova->prox = *lista;
    *lista = nova;
    printf(" Atividade '%s' cadastrada com sucesso!\n", nova->titulo);
}

void listarAtividades(Atividade *lista) {
    if (!lista) {
        printf("Nenhuma atividade cadastrada neste evento.\n");
        return;
    }
    printf("\n--- Lista de Atividades ---\n");
    Atividade *atual = lista;
    while (atual) {
        printf("  - Titulo: %s | Horario: %02d:%02dhrs\n", atual->titulo, atual->hora / 100, atual->hora % 100);
        atual = atual->prox;
    }
}

// Atualizada para empilhar antes de remover a atividade
void removerAtividade(Atividade **lista, char titulo[]) {
    Atividade *atual = *lista;
    Atividade *anterior = NULL;

    // Procura a atividade na lista
    while (atual && strcmp(atual->titulo, titulo) != 0) {
        anterior = atual;
        atual = atual->prox;
    }

    if (!atual) {
        printf("Atividade com o título '%s' não encontrada.\n", titulo);
        return;
    }

    // Empilha a operação de remoção na pilha de desfazer
    empilhar(pilhaDesfazer, "atividade", atual->titulo, atual->horario);

    // Remove o nó da lista
    if (anterior) {
        anterior->prox = atual->prox;
    } else {
        *lista = atual->prox;
    }

    free(atual);
    printf("Atividade '%s' removida com sucesso.\n", titulo);
}
