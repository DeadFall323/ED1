#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/atividades.h"
#include "../headers/desfazer.h"  // Adicionado para usar a pilha de desfazer

extern NoPilha *pilhaDesfazer;  // Declara a pilha usada em todo o sistema

// '*a' e '*b' sao ponteiros q apontam pra o incio de cada lista ordenda.
Atividade *merge(Atividade *a, Atividade *b) {
    if (!a) return b; // Caso base da recursão: se a primeira lista (a) for nula, o resultado é a segunda lista (b).
    if (!b) return a; //  // Caso base da recursão: se a segunda lista (b) for nula, o resultado é a primeira lista (a).

    Atividade *resultado = NULL;    // Ponteiro para armazenar o nó inicial da lista combinada.

    if (a->hora <= b->hora) {
        resultado = a; // Se a atividade da lista 'a' tem horário menor ou igual, ela se torna o início do resultado.
        resultado->prox = merge(a->prox, b); // O próximo elemento da lista resultado é definido recursivamente, combinando
        // o resto da lista 'a' (a->prox) com a lista 'b' inteira.

    } else {
        resultado = b;   // Se a atividade da lista 'b' tem horário menor, ela se torna o início do resultado.
        resultado->prox = merge(a, b->prox);// O próximo elemento é definido recursivamente, combinando a lista 'a' inteira
        // com o resto da lista 'b' (b->prox).


    }
    return resultado; // Retorna o ponteiro para o início da lista recém-combinada e ordenada.
}



// 'origem' é a lista original a ser dividida.
// frente é o Ponteiro p/ a primeira metade da lista.
// tras é ponteiro p/ a segunda metade da lista.
// Divide uma lista encadeada em duas metades.
void dividir(Atividade *origem, Atividade **frente, Atividade **tras) {
    if (!origem || !origem->prox) { // Caso base: se a lista está vazia ou tem apenas um elemento, não há como dividir.
        *frente = origem;  // A 'frente' se torna a própria lista e a 'tras' se torna nula.
        *tras = NULL;
        return;
    }

    Atividade *lento = origem;   // Inicializa o ponteiro 'lento' no primeiro nó.
    Atividade *rapido = origem->prox;  // Inicializa o ponteiro 'rapido' no segundo nó.

    // O ponteiro 'rapido' avança dois nós por vez, enquanto 'lento' avança um.
    // Quando 'rapido' chegar ao fim, 'lento' estará no meio.
    while (rapido) {
        rapido = rapido->prox;  // O ponteiro 'rapido' avança um passo.
        if (rapido) { // Se 'rapido' não for nulo após o primeiro passo, significa que ainda há nós à frente.
            lento = lento->prox; // 'lento' avança um passo.
            rapido = rapido->prox;   // 'rapido' avança o segundo passo
        }
    }

    *frente = origem;   // A primeira metade ('frente') começa no nó de origem da lista original.
    *tras = lento->prox;  // A segunda metade ('tras')comeca no nó seguinte ao 'lento', que é o ponto médio.
    lento->prox = NULL;    // a conexao entre as duas metades é rompida e transforma o fim da primeira metade em NULL e cria duas listas distintas.
}

// divide a lista e chama a si mesma, e depois usa a função merge para juntar os pedaços.
void ordenarAtividades(Atividade **lista) {
    // 'cabeca' recebe o ponteiro para o primeiro nó da lista.
    Atividade *cabeca = *lista;
     //se a lista estiver vazia ou tiver apenas um elemento,retorna sem modificar, pq ja ta ordenada.
    if (!cabeca || !cabeca->prox) return;
    
    // Declara dois ponteiros para atividades, 'a' e 'b', que receberão s duas metades da lista após a divisão.
    Atividade *a;
    Atividade *b;
    // a função 'dividir' pega a lista original ('cabeca') e a divide em duas sub-listas, 'a' e 'b'.
    dividir(cabeca, &a, &b);
    // A função chama a si mesma para ordenar a primeira metade da lista ('a')
    ordenarAtividades(&a);
    // A função chama a si mesma novamente para ordenar a segunda metade da lista ('b').
    ordenarAtividades(&b);
    // a função 'merge' é chamada para combiná-las em uma única lista final ordenada.
    *lista = merge(a, b);
    // O ponteiro original da '*lista' é atualizado para apontar para o
    // início da nova lista combinada e ordenada.
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


// verifica se ja exista alguma atividade no msm horario
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
    // *lista é o ponteiro para o primeiro nó da lista de atividades a ser listada
void listarAtividades(Atividade *lista) {
    // Verifica se o ponteiro para a lista é nulo, o que significa que não há atividades
    if (!lista) {
        printf("Nenhuma atividade cadastrada neste evento.\n");
        return;
    }
    printf("\n--- Lista de Atividades ---\n");
    // Cria um ponteiro auxiliar 'atual' que começa apontando para o início da lista.
    Atividade *atual = lista;
    // enquanto 'atual' n for nulo continuar percorrendo e imprimindo a lista.
    while (atual) {
        printf("  - Titulo: %s | Horario: %02d:%02dhrs\n", atual->titulo, atual->hora / 100, atual->hora % 100);
        atual = atual->prox;
    }
}

// remove uma atividade de um evento e registra na pilha de desfazer
// recebe também o ponteiro para o evento, para que possamos registrar corretamente onde ela estava
void removerAtividade(Evento *evento, Atividade **lista, char titulo[]) {
    Atividade *atual = *lista;
    Atividade *anterior = NULL;

    // Procura a atividade pelo título
    while (atual && strcmp(atual->titulo, titulo) != 0) {
        anterior = atual;
        atual = atual->prox;
    }

    if (!atual) {
        printf("Atividade com o título '%s' não encontrada.\n", titulo);
        return;
    }

    // Empilha a operação de remoção na pilha de desfazer

char horario_str[10]; // cria buffer para armazenar o horário em formato de string
sprintf(horario_str, "%d", atual->hora); // converte o horário int para string (ex: 1430 → "1430")

empilhar(&pilhaDesfazer, "atividade", atual->titulo, "-", horario_str, "-", evento->nome);

    // Remove o nó da lista encadeada de atividades
    if (anterior) {
        anterior->prox = atual->prox;
    } else {
        *lista = atual->prox;
    }

    free(atual);
    printf("Atividade '%s' removida com sucesso.\n", titulo);
}

