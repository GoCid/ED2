//
//  main.c
//  TAREA 4
//
//  Created by Leonardo Alejandro González López on 11/03/21.
//  Copyright © 2021 UASLP. All rights reserved.
/*Hacer un programa usando arreglos dinámicos, estructuras y apuntadores genéricos para manejar la venta de boletos en un cine.
 Se debe guardar el número de ticket, número de asiento, la hora, precio según el formato (normal, junior, 4DX, IMAX, Macro)
 y el nombre de la película.
 Existen 2 tipos clientes de clientes: regulares y VIP.  para los clientes regulares el día de su cumpleaños su entrada es al 2x1
 (sólo en salas con formato normal) y pueden tener un cupón de descuento.
 Los clientes VIP su entrada es gratis el día de su cumpleaños mas un bono para comprar en la dulcería del 20% del valor de su boleto.

Se deben declarar las estructuras de datos correspondientes, constantes simbólicas y las siguientes funciones:

1.-Pedir datos

2.-Mostrar datos

3.-Calcular el total a pagar por boleto y el total a pagar por todos los boletos comprados por una sola persona

 4.-Los datos de los precios son asignados previamente en un arreglo que será usado al momento de calcular el pago. Al cliente se le solicita el número del cupón, el título de la película, el formato y si es su cumpleaños (s/n).
 */
#define N 50
#define P 5
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct{
    int   serial;   //
    int   asiento;  //
    int   hora;     //
    int   formato;  //
    int   cliente;  //
    int   cumplea;  //
    char  pelicula[N]; //
}TBoleto;

// aqui se asigna los precios del arreglo
int precios[P] = {45, 50, 110, 65, 70};

//
void Presentacion(void);
void pideDatos(TBoleto *boleto, int tam);
void muestraDatos(TBoleto *boleto, int tam);
void pideT(int *tam);
void ReservaMemoria( void **Arre, int tam );
void LiberaMem(void **Arre);
//

int main() {
    void *boletos;
    int tam;
    Presentacion();
    pideT(&tam);
    ReservaMemoria(&boletos, tam);
    pideDatos(boletos, tam);
    muestraDatos(boletos, tam);
    LiberaMem(&boletos);
    
}

//
void Presentacion(){
    char x;
    printf("\t\t     ESTRUCTURAS DE DATOS II \n \t\t Leonardo Alejandro Gonzalez Lopez \n \t\t Tarea 4 \n \t\t\t\t 11/Marzo/2021 \n \t\t Profesor: Francisco Edgar Castillo Barrera \n \t\t Version 1.0 \n Presione cualquier tecla para continuar :D ");
    gets(&x);
    fflush(stdin);
    fpurge(stdin);
}

//
void pideDatos(TBoleto *boleto, int tam){
    int i, j, serie = 0, pcon =0,control = 0;
    for (i=0; i<tam; i++) {
        boleto[i].serial = serie++ ;
        boleto[i].asiento = serie++ ;
        if (pcon == 0) {
            printf("\n A que funcion quieres ingresar?: 2, 5, 7 ó 10\n");
            scanf("%d", &boleto[i].hora);
            printf("\n Cual es el nombre de la pelicula?\n");
            fflush(stdin);
            fpurge(stdin);
            gets(boleto[i].pelicula);
            fflush(stdin);
            fpurge(stdin);
            printf("\n Que formato deseas ver?\n 1. Normal 2. Junior 3. 4DX 3. IMAX 4. Macro\n");
            scanf("%d", &boleto[i].formato);
            for (j=1; j<tam; j++) {
                boleto[j].hora = boleto[0].hora;
                strcpy(boleto[j].pelicula, boleto[0].pelicula);
                boleto[j].formato = boleto[0].formato;
            }
            pcon = 1;
        }
        if (control == 0) {
            printf("\n Es tu cumpleaños? 1.Si 2. No\n");
            scanf("%d", &control);
            
            if (control == 1) {
                for (j = 1; j<tam; j++) {
                    boleto[j].cumplea = control;
                }
                printf("\n Eres cliente VIP? 1. Si 2. No\n");
                scanf("%d", &boleto[i].cliente);
                for (j = 1; j<tam; j++) {
                    boleto[j].cliente = boleto[0].cliente;
                }
            }else{
                for (j = 0; j<tam; j++) {
                    boleto[j].cumplea = control;
                }
            }
        }
    }
}

//
void muestraDatos(TBoleto *boleto, int tam){
    int i, n, total, bono;
    /*
     char  pelicula[N]; //
     */
    for (i = 0; i<tam; i++) {
        printf("\n Boleto %d de %d \n", i+1, tam);
        printf("\n Asiento #%d\n", boleto[i].asiento);
        printf("\n Funcion de las %d:00", boleto[i].hora);
        printf("\n Formato: ");
        n=boleto[i].formato;
        switch (n) {
            case 1:
                printf("Normal\n");
                if (boleto[i].cumplea == 1) {
                    if (boleto[i].cliente == 1) {
                        total = (precios[n]*tam) - precios[n];
                        bono = (precios[n] * 20) / 100;
                        printf("\n El costo total es de: $ %i con descuento de cumpleaños\n", total);
                        printf("\n Cada boleto cuesta $ %i \n", precios[n]);
                        printf("\n Tienes $ %i de descuento en la dulceria", bono);
                    }else{
                        total = (precios[n]*(tam/2));
                        printf("\n El costo total es de: $ %i con descuento de cumpleaños\n", total);
                        printf("\n Cada boleto cuesta $ %i , se aplico 2x1 por cumpleaños\n", precios[n]);
                    }
                }else{
                    total = (precios[n]*tam);
                    printf("\n El costo total es de: $ %i \n", total);
                    printf("\n Cada boleto cuesta $ %i \n", precios[n]);
                }
                break;
            case 2:
                printf("Junior\n");
                if (boleto[i].cumplea == 1) {
                    if (boleto[i].cliente == 1) {
                        total = (precios[n]*tam) - precios[n];
                        bono = (precios[n] * 20) / 100;
                        printf("\n El costo total es de: $ %i con descuento de cumpleaños\n", total);
                        printf("\n Cada boleto cuesta $ %i \n", precios[n]);
                        printf("\n Tienes $ %i de descuento en la dulceria", bono);
                    }else{
                        total = (precios[n]*(tam/2));
                        printf("\n El costo total es de: $ %i con descuento de cumpleaños\n", total);
                        printf("\n Cada boleto cuesta $ %i , se aplico 2x1 por cumpleaños\n", precios[n]);
                    }
                }else{
                    total = (precios[n]*tam);
                    printf("\n El costo total es de: $ %i \n", total);
                    printf("\n Cada boleto cuesta $ %i \n", precios[n]);
                }
                break;
            case 3:
                printf("4DX\n");
                if (boleto[i].cumplea == 1) {
                    if (boleto[i].cliente == 1) {
                        total = (precios[n]*tam) - precios[n];
                        bono = (precios[n] * 20) / 100;
                        printf("\n El costo total es de: $ %i con descuento de cumpleaños\n", total);
                        printf("\n Cada boleto cuesta $ %i \n", precios[n]);
                        printf("\n Tienes $ %i de descuento en la dulceria", bono);
                    }else{
                        total = (precios[n]*(tam/2));
                        printf("\n El costo total es de: $ %i con descuento de cumpleaños\n", total);
                        printf("\n Cada boleto cuesta $ %i , se aplico 2x1 por cumpleaños\n", precios[n]);
                    }
                }else{
                    total = (precios[n]*tam);
                    printf("\n El costo total es de: $ %i \n", total);
                    printf("\n Cada boleto cuesta $ %i \n", precios[n]);
                }
                break;
            case 4:
                printf("IMAX \n");
                if (boleto[i].cumplea == 1) {
                    if (boleto[i].cliente == 1) {
                        total = (precios[n]*tam) - precios[n];
                        bono = (precios[n] * 20) / 100;
                        printf("\n El costo total es de: $ %i con descuento de cumpleaños\n", total);
                        printf("\n Cada boleto cuesta $ %i \n", precios[n]);
                        printf("\n Tienes $ %i de descuento en la dulceria", bono);
                    }else{
                        total = (precios[n]*(tam/2));
                        printf("\n El costo total es de: $ %i con descuento de cumpleaños\n", total);
                        printf("\n Cada boleto cuesta $ %i , se aplico 2x1 por cumpleaños\n", precios[n]);
                    }
                }else{
                    total = (precios[n]*tam);
                    printf("\n El costo total es de: $ %i \n", total);
                    printf("\n Cada boleto cuesta $ %i \n", precios[n]);
                }
                break;
            case 5:
                printf("Macro \n");
                if (boleto[i].cumplea == 1) {
                    if (boleto[i].cliente == 1) {
                        total = (precios[n]*tam) - precios[n];
                        bono = (precios[n] * 20) / 100;
                        printf("\n El costo total es de: $ %i con descuento de cumpleaños\n", total);
                        printf("\n Cada boleto cuesta $ %i \n", precios[n]);
                        printf("\n Tienes $ %i de descuento en la dulceria", bono);
                    }else{
                        total = (precios[n]*(tam/2));
                        printf("\n El costo total es de: $ %i con descuento de cumpleaños\n", total);
                        printf("\n Cada boleto cuesta $ %i , se aplico 2x1 por cumpleaños\n", precios[n]);
                    }
                }else{
                    total = (precios[n]*tam);
                    printf("\n El costo total es de: $ %i \n", total);
                    printf("\n Cada boleto cuesta $ %i \n", precios[n]);
                }
                break;
        }
        printf("\n La pelicula que veras es: %s\n", boleto[i].pelicula);
    }
}

//
void pideT(int *tam){
    printf("\n Cuantos boletos compraras? \n");
    scanf("%d", tam);
}

//
void ReservaMemoria( void **Arre, int tam ){
    
    *Arre=(TBoleto *) malloc( sizeof(TBoleto) * tam );
    
}

//
void LiberaMem(void **Arre){
    free( *Arre );
    *Arre = NULL;
}
