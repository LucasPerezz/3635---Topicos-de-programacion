#include <stdio.h>
#include <stdlib.h>

char *strrchr_rec(char *inicio, char *fin, char bus){
    if(*fin == bus){
        return fin;
    }
    if(inicio == fin){
        return NULL;
    }
    return strrchr_rec(inicio, --fin, bus);
}

char *strrchr_recursivo(char *cadena, char bus){
    char *inicio = cadena;
    char *fin;
    while(*inicio){
        inicio++;
    }
    fin = inicio - 1;
    return strrchr_rec(cadena, fin, bus);
}

int main(){
    char lote[] = "abcdefghijklmnopqrstuvwxyz";
    printf("%c", *strrchr_recursivo(lote, 'x'));

    return 0;
}