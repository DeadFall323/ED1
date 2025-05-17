#include <stdio.h>

void funcao_recursiva(int n);


int main(void) {
    int n=5;
    funcao_recursiva(n);
    return 0;
}


void funcao_recursiva(int n) {
    if (n > 0){
        printf("numero %d\n",n);
    funcao_recursiva(n -1);
}
    else {
        printf("numero %d\n",n);
    }
}