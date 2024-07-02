#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define A_MAYUSCULA(x)((x >= 'a' && x <= 'z') ? x - 32 : x)

int palindromoRecursivo(char *inicio, char *fin){
    if(inicio > fin) {
        return 1;
    }

    while(*inicio == ' '){
        inicio++;
    }

    while(*fin == ' '){
        fin--;
    }

    if(A_MAYUSCULA(*inicio) != A_MAYUSCULA(*fin)){
        return 0;
    } else {
        return palindromoRecursivo(++inicio, --fin);
    }
}

int esPalindromo(char *cadena){
    char *inicio = cadena;
    char *fin;
    while(*inicio){
        inicio++;
    }
    fin = inicio - 1;
    inicio = cadena;
    return palindromoRecursivo(inicio, fin);
}

int main(){
    char lote[] = "  aNita   lava la tinA";
    if(!esPalindromo(lote)){
        printf("No es palindromo\n");
    } else {
        printf("Es palindromo\n");
    }
    return 0;
}

