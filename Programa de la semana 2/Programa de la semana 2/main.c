//
//  main.c
//  Programa de la semana 2
//
//  Created by Leonardo Alejandro González López on 19/02/21.
//  Copyright © 2021 UASLP. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
//prototipos
void Presentacion(void);

void pideTamano(int *tam);

void pideDatosArreglo(float *Arr, int tam);

void reservaMemoria(float **Arrx,float **Arry, float **Arra, int tam);

void liberaMemoria(float **Arrx, float **Arry, float **Arra);

void intercambiaArreglos(float *Arrx, float *Arry, float *Arra, int tam);

void muestraDatos(float Arrx[], int tam);
//prototipos

int main() {
    Presentacion();
    int tam=0;
    float *Arr = NULL,*Arr2=NULL, *Arrau=NULL;
    pideTamano(&tam);
    reservaMemoria(&Arr, &Arr2, &Arrau, tam);
    printf("\n Primer arreglo: ");
    pideDatosArreglo(Arr, tam);
    printf("\n Segundo arreglo: ");
    pideDatosArreglo(Arr2, tam);
    intercambiaArreglos(Arr, Arr2, Arrau, tam);
    printf("\n Arreglo 1: \n");
    muestraDatos(Arr, tam);
    printf("\n Arreglo 2: \n");
    muestraDatos(Arr2, tam);
    liberaMemoria(&Arr,&Arr2, &Arrau);
}

//
void Presentacion(){
    char x;
    printf("\t\t     ESTRUCTURAS DE DATOS II \n \t\t Leonardo Alejandro Gonzalez Lopez \n \t\t Programa de la semana 2: ARREGLOS DINAMICOS \n \t\t\t\t 19/Febrero/2021 \n \t\t Profesor: Francisco Edgar Castillo Barrera \n \t\t Version 1.0 \n Presione cualquier tecla para continuar :D ");
    gets(&x);
}

//
void pideTamano(int *tam){
    printf("\n Ingrese el tamaño de los arreglos: ");
    scanf("%i", tam);
}

//
void pideDatosArreglo(float *Arrx, int tam){                //En vez de *Arrx podria ser Arrx[]
    int i;
    for (i=0; i<tam; i++) {
        printf("\n Escribe el valor %i de %i \n", i+1, tam);
        scanf("%f", &Arrx[i]);                             //En tal caso en esta linea seri Arrx+i
    }                                                      //Igual en las demas funciones, ejemplo en muestraDatos
}

//
void reservaMemoria(float **Arrx,float **Arry,float **Arra, int tam){
    *Arrx=(float*)malloc(sizeof(float)*tam);
    *Arry=(float*)malloc(sizeof(float)*tam);
    *Arra=(float*)malloc(sizeof(float)*tam);
}

//
void liberaMemoria(float **Arrx, float **Arry, float **Arra){
    free(*Arrx);
    *Arrx=NULL;
    free(*Arry);
    *Arry=NULL;
    free(*Arra);
    *Arra=NULL;
}

void intercambiaArreglos(float *Arrx, float *Arry, float *Arra, int tam){
    float aux;
    int i;
    for (i=0; i<tam; i++) {
        aux=*(Arrx+((tam-1)-i));
        *(Arra+i)=aux;
    }
    for (i=0; i<tam; i++) {
        *(Arrx+i)=*(Arry+((tam-1)-i));
    }
    for (i=0; i<tam; i++) {
        *(Arry+i)=*(Arra+i);
    }
}

//
void muestraDatos(float Arrx[], int tam){
    int i;
    for (i=0; i<tam; i++) {
        printf("\n D[%i]= %f \n", i+1, *(Arrx+i));
    }
}
