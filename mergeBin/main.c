#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct
{
    unsigned long long dni;
    unsigned long long fechaDeInscripcion;
    char nombreYApellido[30];
    float promedio;
}tEstudiantes;

int abrirArchivo(FILE **pf, char *nombre, char *modo){
    *pf = fopen(nombre, modo);
    return pf ? 1 : 0;
}

int compararEnteros(const void *a, const void *b){
    tEstudiantes *aux1 = (tEstudiantes*) a;
    tEstudiantes *aux2 = (tEstudiantes*) b;
    return aux1->fechaDeInscripcion - aux2->fechaDeInscripcion;
}


int mergeArchivos(FILE *pf1, FILE *pf2, FILE *pOut, size_t tam, int (*comparar)(const void *, const void *)){
    void *buffer1 = malloc(tam);
    if(!buffer1) return 0;
    void *buffer2 = malloc(tam);
    if(!buffer2){
        free(buffer1);
        return 0;
    }
    fread(buffer1, tam, 1, pf1);
    fread(buffer2, tam, 1, pf2);
    while(!feof(pf1) && !feof(pf2)){
        if(comparar(buffer1, buffer2) == 0){
            fwrite(buffer1, tam, 1, pOut);
            fread(buffer1, tam, 1, pf1);
            fread(buffer2, tam, 1, pf2);
        } else if (comparar(buffer1, buffer2) < 0) {
            fwrite(buffer1, tam, 1, pOut);
            fread(buffer1, tam, 1, pf1);
        } else {
            fwrite(buffer2, tam, 1, pOut);
            fread(buffer2, tam, 1, pf2);
        }
    }
    while(!feof(pf1)){
        fwrite(buffer1, tam, 1, pOut);
        fread(buffer1, tam, 1, pf1);
    }

    while(!feof(pf2)){
        fwrite(buffer2, tam, 1, pOut);
        fread(buffer2, tam, 1, pf2);
    }
    free(buffer1);
    free(buffer2);
    return 1;
}

void mostrar(const void *elemento){
    tEstudiantes *aux = (tEstudiantes*) elemento;
    printf("%I64d\t %I64d\t %s\t %f\n", aux->dni, aux->fechaDeInscripcion, aux->nombreYApellido, aux->promedio);
}

int mostrarArchivo(FILE *pf, size_t tam, void (*mostrar)(const void *)){
    rewind(pf);
    void *buffer = malloc(tam);
    if(!buffer) return 0;
    fread(buffer, tam, 1, pf);
    while(!feof(pf)){
        mostrar(buffer);
        fread(buffer, tam, 1, pf);
    }
    free(buffer);
    return 1;
}



int main(){
    FILE *pf1, *pf2, *pfOut; 
    if(!abrirArchivo(&pf1, "estudiantes1.dat", "rb"))
        return 0;
    if(!abrirArchivo(&pf2, "estudiantes2.dat", "rb")){
        fclose(pf1);
        return 0;
    }
    if(!abrirArchivo(&pfOut, "estudiantes_final.dat", "w+b")){
        fclose(pf1);
        fclose(pf2);
        return 0;
    }

    mergeArchivos(pf1, pf2, pfOut, sizeof(tEstudiantes), compararEnteros);
    mostrarArchivo(pfOut, sizeof(tEstudiantes), mostrar);
    fclose(pf1);
    fclose(pf2);
    fclose(pfOut);
    return 0;
}