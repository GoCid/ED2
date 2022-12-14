//
//  main.c
//  listasLigadas
//
//  Created by Leonardo Alejandro González López on 23/03/21.
//  Copyright © 2021 UASLP. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
typedef struct nodo{
    int dato;
    struct nodo *sig;
}TNodo;

//Prototipos
void Presentacion(void);

void pideDatos(int *numero);

TNodo *creaNodo(int info);

int insertaInicio(TNodo **Cab, int dato);

void insertaFinal(TNodo **cab, int dato);

void cabezaFin(TNodo *cab);

void finCabeza(TNodo *cab);

TNodo *borrarNodo(TNodo *cab, int dato);

void borrarToutNod(TNodo *cab);

void borraPrimero(TNodo **Cab);
//Prototipos

int main() {
    TNodo *Cabeza = NULL, *auxi;
    auxi = Cabeza;
    int numero = 0, aux;
    Presentacion();
    while (1) {
        printf("\t\t\t -----MENU PRINCIPAL-----");
        printf("\n Escoge una opcion:\n 1. Insertar al final \n 2. Imprimir de cabeza a fin \n 3. Imprimir de fin a cabeza \n 4. Eliminar nodo especifico \n 5. Eliminar todos los nodos\n 6. Salir");
        printf("\n");
        scanf("%i", &aux);
        switch (aux) {
            case 1:
                pideDatos(&numero);
                insertaFinal(&Cabeza, numero);
                printf("\n Nodo creado\n");
                break;
            case 2:
                cabezaFin(Cabeza);
                break;
            case 3:
                finCabeza(Cabeza);
                break;
            case 4:
                pideDatos(&numero);
                borrarNodo(Cabeza, numero);
                break;
            case 5:
                borrarToutNod(Cabeza);
                //borraPrimero(&Cabeza);
                break;
            case 6:
                borrarToutNod(Cabeza);
                //borraPrimero(&Cabeza);

                exit(0);
            case '\n':
                printf("\n No se ingreso instruccion\n");
            default:
                printf("\n Comando desconocido \n");
                break;
        }
    }
}

//
void Presentacion(){
    char x;
    printf("\t\t     ESTRUCTURAS DE DATOS II \n \t\t Leonardo Alejandro Gonzalez Lopez \n \t\t Programa de la semana 5: Listas Ligadas Recursivas \n \t\t\t\t 23/Marzo/2021 \n \t\t Profesor: Francisco Edgar Castillo Barrera \n \t\t Version 1.5 \n Presione cualquier tecla para continuar :D ");
    gets(&x);
}

//
void pideDatos(int *numero){
    printf("\n Escribe el dato: ");
    scanf("%d", numero);
}
//
TNodo *creaNodo(int info){
    TNodo *nuevo = NULL;
    
    nuevo = (TNodo *)malloc(sizeof(TNodo));
    nuevo-> dato = info;
    nuevo-> sig = NULL;
    return nuevo;
}

//
int insertaInicio(TNodo **Cab, int dato){
    int band = 0;
    TNodo *nuevo;
    nuevo = creaNodo(dato);
    if (nuevo != NULL) {
        nuevo-> sig = *Cab;
        band++;
        return band;
    }
    return band;
}

//
void insertaFinal(TNodo **cab, int dato){
    if (*cab == NULL)
    {
        TNodo *nuevo = creaNodo(dato);
        nuevo->sig=*cab;
        *cab=nuevo;
    }
    else if((*cab)->sig != NULL)
    {
        insertaFinal(&(*cab)->sig,dato);
    }
    else
    {
        TNodo *nuevo= creaNodo(dato);
        (*cab)->sig=nuevo;

    }
}
//
void cabezaFin(TNodo *cab){
    if (cab != NULL) {
        printf("%d\n", cab->dato);
        cabezaFin(cab->sig);
    }
}

//tengo dudas sobre esta pero estoy bastante seguro que si es asi
void finCabeza(TNodo *cab){
    if (cab != NULL) {
        cabezaFin(cab->sig);
        printf("%d\n", cab->dato);
    }
}

//busca dato y borra ese nodo
TNodo *borrarNodo(TNodo *cab, int dato){
    TNodo *borrador = NULL;
    if (cab != NULL) {
        if (cab->dato == dato) {
            borrador = cab;
            cab = cab->sig;
            free(borrador);
        }else{
            cab->sig=borrarNodo(cab->sig, dato);
        }
    }
    return cab;
}

//intente hacerla recursiva a ver si sirve :p en teoria si
void borrarToutNod(TNodo *cab){
    if(cab->sig != NULL)
    {
        borrarToutNod(cab->sig);
        free(cab->sig);
        cab->sig=NULL;
    }
    cab=NULL;
}
//Funciona borrar recursivo pero el primer dato permanece, es decir si pongo 6 como primer dato ese no se elimina
void borraPrimero(TNodo **Cab){
    TNodo *aux;
    aux = *Cab;
    free(aux);
}
