#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int **crearMatriz(unsigned cf, unsigned cc){
    int **matriz;
    int i;
    matriz = (int**) malloc(cf * sizeof(int*));
    if(!matriz) return NULL;
    for(i = 0; i < (int) cc; i++){
        matriz[i] = (int*) malloc(cc * sizeof(int));
        if(!matriz[i]){
            for(i = i; i == 0; i--){
                free(matriz[i]);
            }
        }
    }
    return matriz;
}

int destruirVector(int **matriz, unsigned cf){
    int i;
    if(!matriz) return 0;
    for(i = 0; i < (int) cf; i++){
        free(matriz[i]);
    }
    return 1;
}

int mostrarMatriz(int **matriz, unsigned cf, unsigned cc){
    int i, j;
    if(!matriz) return 0;
    for(i = 0; i < (int) cf; i++){
        for(j = 0; j < (int) cc; j++){
            printf("%d\t", matriz[i][j]);
        }
        printf("\n");
    }
    return 1;
}

int inicializarMatriz(int **matriz, unsigned cf, unsigned cc){
    int i, j;
    if(!matriz) return 0;
    for(i = 0; i < (int) cf; i++){
        for(j = 0; j < (int) cc; j++){
            matriz[i][j] = j;
        }
    }
    return 1;
}



int main(){
    int **mat = NULL;
    unsigned cf = 2, cc = 2;
    mat = crearMatriz(cf, cc);
    inicializarMatriz(mat, cf, cc);
    mostrarMatriz(mat, cf, cc);
    destruirVector(mat, cf);
    return 0;
}

