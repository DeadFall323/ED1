//
// Created by kawandias on 17/06/25.
//

#ifndef ATIVIDADES_H
#define ATIVIDADES_H

#include "participantes.h"

typedef struct Atividade {
    char titulo[100];
    char horario[6];
    Participante *participantes; // lista duplamente encadeada
    struct Atividade *prox;
} Atividade;


#endif //ATIVIDADES_H
