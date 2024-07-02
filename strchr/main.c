#include <stdio.h>
#include <stdlib.h>

char *strchr_recursivo(char *cadena, char bus){
    if(*cadena == bus){
        return cadena;
    }
    return strchr_recursivo(++cadena, bus);
}


int main(){
    char lote[] = "abcdefghijklmnopqrstuvwxyz";
    printf("%s", strchr_recursivo(lote, 'd'));
    return 0;
}