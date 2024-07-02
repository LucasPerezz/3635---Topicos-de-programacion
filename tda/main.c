#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

typedef struct
{
    unsigned ce;
    size_t tam;
    void *vec;
}tVector;

int crearVector(tVector *vec, unsigned ce, size_t tam){
    vec->vec = malloc(ce * tam);
    if(!vec->vec) return 0;
    vec->ce = ce;
    vec->tam = tam;
    return 1;
}

int inicializar(tVector *vec)
{
    int i;
    int vec_num[] = {1, 2, 1, 4, 1, 1, 6, 1};
    if(!vec->vec) return 0;
    for(i = 0; i < (int) vec->ce; i++)
    {
        memcpy(vec->vec + vec->tam * i, vec_num + i, vec->tam);
    }
    return 1;
}

int destruirVector(tVector *vec){
    if(!vec->vec) return 0;
    vec->ce = 0;
    vec->tam = 0;
    free(vec->vec);
    return 1;
}

void mostrar(const void *elemento){
    int *num = (int*) elemento;
    printf("%d\t", *num);
    return;
}

int mostrarVector(tVector *vec, void (*mostrar)(const void *)){
    int i;
    if(!vec->vec) return 0;
    for(i = 0; i < (int) vec->ce; i++){
        mostrar(vec->vec + vec->tam * i);
    }
    printf("\n");
    return 1;
}

int filter(const void *elemento){
    int *num = (int*) elemento;
    if(*num == 4){
        return 1;
    }
    return 0;
}

int tda_filter(tVector *vec, int (*filter)(const void *)){
    int cont = 0;
    if(!vec->vec) return 0;
    void *pl = vec->vec;
    void *pe = vec->vec;
    while(pe != vec->vec + (vec->tam * vec->ce)){
        if(filter(pe)){
            pe += vec->tam;
            pl += vec->tam;
        }
        else{
            while(!filter(pl) && pl != vec->vec + (vec->tam * vec->ce)){
                pl += vec->tam;
                cont++;
            }
            memcpy(pe, pl, vec->tam);
            pe += vec->tam;
        }
    }
    printf("%d\n", cont);
    vec->ce -= cont;
    return 1;
}


int main(){
    tVector vec;
    int vec_nums[] = {1, 4, 4, 7, 6, 4, 1, 5};
    crearVector(&vec, sizeof(vec_nums) / sizeof(vec_nums[0]), sizeof(vec_nums[0]));
    inicializar(&vec);
    mostrarVector(&vec, mostrar);
    tda_filter(&vec, filter);
    mostrarVector(&vec, mostrar);
    destruirVector(&vec);
    return 0;
}



