#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

int intercambio(void *a, void *b, size_t tam){
    void *aux = malloc(tam);
    if(!aux) return 0;
    memmove(aux, a, tam);
    memmove(a, b, tam);
    memmove(b, aux, tam);
    free(aux);
    return 1;
}

int comparar(const void *a, const void *b){
    return *(int*) a - *(int*) b;
}

void *buscarMenor(void *vec, unsigned ce, size_t tam, int (*comparar)(const void *, const void *)){
    void *menor = vec;
    int i;
    for(i = 0; i < (int) ce; i++){
        if(comparar(vec, menor) < 0){
            menor = vec;
        }
        vec += tam;
    }
    return menor;
}

void ordenamientoSeleccion(void *vec, unsigned ce, size_t tam, int (*comparar)(const void *, const void *), int (*intercambio)(void *, void *, size_t)) {
    int i;
    void *menor;
    for(i = 0; i < (int) ce; i++) {
        menor = buscarMenor(vec, ce - i, tam, comparar);
        intercambio(vec, menor, tam);
        vec += tam;
    }
    
}

void mostrarVector(void *vec, unsigned ce, size_t tam, void (*mostrar)(const void *)){
    int i;
    for(i = 0; i < (int) ce; i++){
        mostrar(vec);
        vec += tam;
    }
    printf("\n");
}

void mostrar(const void *elemento){
    printf("%d\t", *(int*)elemento);
}

int main() {
    int vec[] = {32, 14, 1, 7, 2, 100};
    mostrarVector(vec, sizeof(vec) / sizeof(vec[0]), sizeof(int), mostrar);
    ordenamientoSeleccion(vec, sizeof(vec) / sizeof(vec[0]), sizeof(vec[0]), comparar, intercambio);
    mostrarVector(vec, sizeof(vec) / sizeof(vec[0]), sizeof(int), mostrar);
    return 0;
}