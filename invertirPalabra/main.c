#include <stdio.h>
#include <stdlib.h>
#define ES_LETRA(x)((x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z') ? 1 : 0)

char *invertirPalabra(char *cadena){
    char *inicio = cadena;
    char *fin;
    char aux;
    while(*inicio)
        inicio++;
    fin = inicio - 1;
    inicio = cadena;
    while(inicio < fin){
        aux = *inicio;
        *inicio = *fin;
        *fin = aux;
        inicio++;
        fin--;
    }
    return cadena;
}


int main(){
    char lote[] = "hola mundo .";
    printf("%s\n", invertirPalabra(lote));
    return 0;
}