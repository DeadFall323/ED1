#include <stdio.h>
#include <string.h>



int main(void) {
  int valor =0, contador =0;
    char palavra[] = "Universidade";
    int tamanho = strlen(palavra);
    valor = contador_vogais(palavra, tamanho, &contador);
    printf("Valor = %d\n",valor);
    return 0;
}

int contador_vogais(char palavra[], int tamanho, int *contador){

      if(tamanho !=0){
          if (palavra[tamanho-1] == 'a' || palavra[tamanho-1] == 'e'|| palavra[tamanho-1] == 'i'|| palavra[tamanho-1] == 'o'
          || palavra[tamanho-1] == 'u'){
              contador ++;
              printf("vogais: %d", *contador);
          }
          contador += contador_vogais(palavra,tamanho-1, contador ++);
        }
    return contador;
    }