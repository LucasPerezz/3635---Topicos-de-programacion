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

int pasajeArchivoBin_txt(FILE *pfbin, FILE *pftxt, size_t tam, void (*accion)(FILE *, const void *)){
    void *buffer = malloc(tam);
    if(!buffer) return 0;
    fread(buffer, tam, 1, pfbin);
    while(!feof(pfbin)){
        accion(pftxt, buffer);
        fread(buffer, tam, 1, pfbin);
    }
    free(buffer);
    return 1;
}

void pasaje(FILE *pf, const void *elemento){
    tEstudiantes *aux = (tEstudiantes*) elemento;
    fprintf(pf, "%I64d;%I64d;%s;%f\n", aux->dni, aux->fechaDeInscripcion, aux->nombreYApellido, aux->promedio);
    return;
}

void pasajeArchivotxt_bin(FILE *pftxt, FILE *pfbin, size_t tam){
    tEstudiantes aux;
    while(fscanf(pftxt, "%I64d;%I64d;%s;%f\n", &aux.dni, &aux.fechaDeInscripcion, aux.nombreYApellido, &aux.promedio) != -1){
        fwrite(&aux, tam, 1, pfbin);
    }
    return;
}

int mostrarArchivo(FILE *pf, size_t tam, void (*mostrar)(const void *)){
    rewind(pf);
    void *buffer = malloc(tam);
    if(!buffer) return 0;
    fread(buffer, tam, 1, pf);
    while(!feof(pf)){
        mostrar(buffer);
        fread(buffer, 1, tam, pf);
    }
    free(buffer);
    return 1;
}

void mostrar(const void *elemento){
    tEstudiantes *aux = (tEstudiantes*) elemento;
    printf("%I64d\t%I64d\t%s\t%f\n", aux->dni, aux->fechaDeInscripcion, aux->nombreYApellido, aux->promedio);
    return;
}



int main(){
    FILE *pfbin, *pftxt, *pfbin2;
    if(!abrirArchivo(&pfbin, "estudiantes2.dat", "rb")){
        return 0;
    }
    if(!abrirArchivo(&pftxt, "estudiantes.txt", "wt")){
        fclose(pfbin);
        return 0;
    }
    if(!abrirArchivo(&pfbin2, "estudiantes2_1.dat", "w+b")){
        fclose(pfbin);
        fclose(pftxt);
        return 0;
    }
    pasajeArchivoBin_txt(pfbin, pftxt, sizeof(tEstudiantes), pasaje);
    pasajeArchivotxt_bin(pftxt, pfbin2, sizeof(tEstudiantes));
    mostrarArchivo(pfbin2, sizeof(tEstudiantes), mostrar);
    fclose(pfbin);
    fclose(pftxt);
    fclose(pfbin2);
    return 0;
}

