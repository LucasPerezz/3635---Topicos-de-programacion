#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

int comparar(const void *elemento1, const void *elemento2){
    return *(int*) elemento1 - *(int*) elemento2;
}


void *mbsearch(const void *clave, const void *base, size_t nmemb, size_t tamanyo, int (*comparar)(const void *, const void *)){
    int cmp;
    size_t indice_mitad;
    void *elemento_mitad;
    void *pbase = (void *) base;

    if(nmemb == 0) return NULL;

    indice_mitad = nmemb / 2;
    elemento_mitad = pbase + (indice_mitad * tamanyo);
    cmp = comparar(clave, elemento_mitad);

    if(cmp == 0){
        return (void*) elemento_mitad;
    }

    if(cmp < 0){
        return mbsearch(clave, pbase, indice_mitad, tamanyo, comparar);
    }

    return mbsearch(clave, elemento_mitad + tamanyo, nmemb - indice_mitad - 1, tamanyo, comparar);
    
}

int main() {
    int vec[] = {1, 2, 4, 7, 8, 10};
    int i;
    for(i = 0; i < 11; i++){
        if(!mbsearch(&i, vec, 6, sizeof(int), comparar)){
            printf("No encontrado\n");
        } else {
            printf("Encontrado\n");
        }
    }


    return 0;
}

