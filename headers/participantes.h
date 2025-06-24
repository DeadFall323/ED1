//
// Created by kawandias on 17/06/25.
//

#ifndef PARTICIPANTES_H
#define PARTICIPANTES_H

typedef struct Participante {
    char nome[100];
    char email[100];
    char matricula[20];
    struct Participante *ant;
    struct Participante *prox;
} Participante;

void menu_participantes();
Participante* criar_participante(const char *nome, const char *email, const char *matricula);
void inserir_participante(Participante **lista, Participante *novo);
void listar_participantes(Participante *lista);
void remover_participante(Participante **lista, const char *matricula);
void ordenar_participantes_bubble(Participante **lista);
int validar_email(const char *email);
int validar_matricula(const char *matricula);

#endif
