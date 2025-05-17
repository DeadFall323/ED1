#include <stdio.h>
#include <stdlib.h>


int main(void) {
    //Escreva um programa que leia cinco notas, calcule a media e mostre o
    //resultado.
    //Faça nos três laços de repetição.

    float vetor[5];
    printf("Insira as 5 notas do aluno \n");
    printf("insira a primeira nota: \n");
    for (int i=0;i<5;i++) {
        scanf("%f",vetor[i]);
    }



    return 0;
}
