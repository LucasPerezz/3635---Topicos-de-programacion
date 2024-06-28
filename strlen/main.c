#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

size_t strlenRecursivo(char *cadena){
    if(! *cadena){
        return 0;
    }
    return strlenRecursivo(++cadena) + 1;
}

int main(){
    char lote1[] = "Hola mundo";
    printf("%d", (int) strlenRecursivo(lote1));
    return 0;
}