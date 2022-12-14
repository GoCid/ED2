//
//  main.c
//  ArbolesB
//
//  Created by Leonardo Alejandro González López on 31/05/21.
//  Copyright © 2021 UASLP. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>

#define R 1     // Raiz
#define I 2     // Nodo intermedio
#define H 3     // Hoja
#define PH 4    // Padre Hijo si se queda con el minimo de datos

typedef struct pagina{
    int *claves;          // Arreglo con los datos, tama;o maximo 2*D
    int nElementos;       // Numero de elementos totales
    int ocupa;            // Numero de casilleros ocupados
    int tipo;             // Si es pagina hoja, intermedio, raiz o los 2
    struct pagina **ptrs; // Cantidad de apuntadores 2*D+1
    struct pagina *anterior;
}TNodoArbolB;

//protos
TNodoArbolB  *creaNodoB(int orden);

void insertaDatoAB(TNodoArbolB *cab, int dato);

void ordenaDatos(TNodoArbolB *cab);

TNodoArbolB* divideNodo(TNodoArbolB *nodo, int dato, TNodoArbolB *aux);
//protos

int main() {
    TNodoArbolB *cab = NULL;
    int orden;
    printf("\n Ingresa el orden de los nodos: \n");
    scanf("%i", &orden);
    cab=creaNodoB(orden);
}

//
TNodoArbolB  *creaNodoB(int orden){
    TNodoArbolB *nuevo;
    int i;
    nuevo=(TNodoArbolB*)malloc(sizeof(TNodoArbolB));
    nuevo->claves= (int*)malloc(sizeof(int)*2*orden);
    nuevo->nElementos=orden*2;
    nuevo->ocupa=0;
    nuevo->ptrs=(TNodoArbolB**)malloc(sizeof(TNodoArbolB)*2*orden+1);
    nuevo->anterior=NULL;
    
    for (i=0; i<(orden*2+1); i++) {
        *(nuevo->ptrs +1) = NULL;
    }
    
    return (nuevo);
}

//
void insertaDatoAB(TNodoArbolB *cab, int dato){
    
    if (cab->ocupa==0) {   //caso 1: Arbol vacio
        cab->tipo=R;
        cab->claves[0]= dato;
       
    }else if(cab->tipo == R && cab->ptrs[0] == NULL){      // caso 2: Raiz sin hijos
        if (cab->ocupa<cab->nElementos) {         // si tiene lugares dispobnibles
            cab->claves[cab->ocupa-1] = dato;     // coloca el dato en el ultimo casillero
            ordenaDatos(cab);                     // ordena los datos
        }else{                                    // si NO tiene lugares disponibles
            TNodoArbolB *aux;
            aux=divideNodo(cab, dato, NULL);
            aux->tipo=H;
        }
    }else if (cab->tipo==H){                 // caso 3 si es una hoja
        
    }
}

//
void ordenaDatos(TNodoArbolB *cab){
    
    int i, j, aux;
    for (j=0; j<cab->ocupa; j++) {
        for (i=0; i<cab->ocupa; i++) {
             if (cab->claves[i] > cab->claves[i+1]) { // dato menor
                 aux = cab->claves[i];
                 cab->claves[i] = cab->claves[i+1];
                 cab->claves[i+1] = aux;
             }
        }
        ordenaDatos(cab);
    }
    
}

//divide segun sea el caso mas no dice que tipo de nodo es R H I PH
TNodoArbolB* divideNodo(TNodoArbolB *nodo, int dato, TNodoArbolB *aux){
    int i, ocu, sube;
    if (nodo->ptrs[0]==NULL && nodo->tipo==R) {                                  // si el nodo no tiene hijos, (raiz u hoja)
        
        TNodoArbolB *nodizq, *nodder;
            nodizq = creaNodoB(nodo->nElementos/2);
            nodder = creaNodoB(nodo->nElementos/2);
            
            if (dato < ((nodo->nElementos/2)+1) && dato > (nodo->nElementos/2)) {   // si el dato va al centro sube el mismo dato
                
                ocu=0;
                for (i = 0; i < (nodo->nElementos/2) ; i++) {                       // los datos menores a la clave se van a nodizq
                    insertaDatoAB(nodizq, nodo->claves[i]);
                    ocu++;
                    nodizq->ocupa=ocu;
                }
                ocu=0;
                for (i = ((nodo->nElementos/2)+1); i<nodo->nElementos; i++) {       // los datos mayores a la clave se van a nodder
                    insertaDatoAB(nodder, nodo->claves[i]);
                    ocu++;
                    nodder->ocupa=ocu;
                }
                nodizq->anterior=nodo;
                nodder->anterior=nodo;
                nodo->claves[0]=dato;                                               // El dato se va a la posicion 1 del nodo original
                nodo->ocupa=1;                                                      // Ocupa de nodo vuelve a ser 1
                nodo->ptrs[0]=nodizq;
                nodo->ptrs[1]=nodder;
                return NULL;
                
            }else if (dato<(nodo->nElementos/2)){           // si el dato va a la izquierda sube el dato claves[nElementos/2]
                
                sube = nodo->claves[nodo->nElementos/2];
                nodo->claves[nodo->nElementos/2]= dato;
                ocu=0;
                for (i=0; i<nodo->nElementos/2; i++) {
                    insertaDatoAB(nodizq, nodo->claves[i]);
                    ocu++;
                    nodizq->ocupa=ocu;
                }
                ocu=0;
                for (i = ((nodo->nElementos/2)+1); i<nodo->nElementos; i++) {
                    insertaDatoAB(nodder, nodo->claves[i]);
                    ocu++;
                    nodder->ocupa= ocu;
                }
                nodizq->anterior=nodo;
                nodder->anterior=nodo;
                nodo->claves[0]=sube;
                nodo->ocupa=1;
                nodo->ptrs[0]=nodizq;
                nodo->ptrs[1]=nodder;
                return NULL;
            }else{                                          // si el dato va a la derecha sube el dato claves[(nElementos/2)+1]
                sube = nodo->claves[(nodo->nElementos/2)+1];
                nodo->claves[(nodo->nElementos/2)+1]= dato;
                ocu = 0;
                for (i=0; i<nodo->nElementos/2; i++) {
                    insertaDatoAB(nodizq, nodo->claves[i]);
                    ocu++;
                    nodizq->ocupa=ocu;
                }
                ocu=0;
                for (i = ((nodo->nElementos/2)+1); i<nodo->nElementos; i++) {
                    insertaDatoAB(nodder, nodo->claves[i]);
                    ocu++;
                    nodder->ocupa= ocu;
                }
                nodizq->anterior=nodo;
                nodder->anterior=nodo;
                nodo->claves[0]=sube;
                nodo->ocupa=1;
                nodo->ptrs[nodo->ocupa-1]=nodizq;
                nodo->ptrs[nodo->ocupa]=nodder;
                return NULL;
            }
        }else if(nodo->ptrs[0]!= NULL){                                          // si el nodo a dividir ya tiene hijos
            if (nodo->tipo==H) {                        // si el nodo es Hoja
                TNodoArbolB *nodder;
                nodder = creaNodoB(nodo->nElementos/2);
                
                if (dato < ((nodo->nElementos/2)+1) && dato > (nodo->nElementos/2)) { // Si el dato va al centro sube el mismo dato
                    insertaDatoAB(nodo->anterior, dato);
                    ocu=0;
                    for (i = ((nodo->nElementos/2)+1); i<nodo->nElementos; i++) {       // los datos mayores a la clave se van a nodder
                        insertaDatoAB(nodder, nodo->claves[i]);
                        ocu++;
                        nodder->ocupa=ocu;
                    }
                    nodo->ocupa=nodo->nElementos/2;
                    for (i=0; i<nodo->nElementos+1; i++) {                              // mientras sea menor al numero de apuntadores
                        if (nodo->anterior->ptrs[i]==NULL) {                            // si el apuntador de nodo anterior es null
                            nodo->anterior->ptrs[i]=nodder;                             // escribe en nodo anterior el nuevo nodo derecho
                        }else{
                            return nodder;
                        }
                    }
                }else if (dato<(nodo->nElementos/2)){                                 // si el dato va a la izquierda sube el dato claves[nElementos/2]
                    sube = nodo->claves[nodo->nElementos/2];
                    nodo->claves[nodo->nElementos/2]= dato;
                    insertaDatoAB(nodo->anterior, sube);
                    ocu=0;
                    for (i = ((nodo->nElementos/2)+1); i<nodo->nElementos; i++) {
                        insertaDatoAB(nodder, nodo->claves[i]);
                        ocu++;
                        nodder->ocupa= ocu;
                    }
                    nodo->ocupa=nodo->nElementos/2;
                    for (i=0; i<nodo->nElementos+1; i++) {                              // mientras sea menor al numero de apuntadores
                        if (nodo->anterior->ptrs[i]==NULL) {                            // si el apuntador de nodo anterior es null
                            nodo->anterior->ptrs[i]=nodder;                             // escribe en nodo anterior el nuevo nodo derecho
                        }else{
                            return nodder;
                        }
                    }
                }else{                                                                // si el dato va a la derecha sube el dato claves[(nElementos/2)+1]
                    sube = nodo->claves[(nodo->nElementos/2)+1];
                    nodo->claves[(nodo->nElementos/2)+1]= dato;
                    insertaDatoAB(nodo->anterior, sube);
                    ocu = 0;
                    for (i = ((nodo->nElementos/2)+1); i<nodo->nElementos; i++) {
                        insertaDatoAB(nodder, nodo->claves[i]);
                        ocu++;
                        nodder->ocupa= ocu;
                    }
                    nodo->ocupa=nodo->nElementos/2;
                    for (i=0; i<nodo->nElementos+1; i++) {                              // mientras sea menor al numero de apuntadores
                        if (nodo->anterior->ptrs[i]==NULL) {                            // si el apuntador de nodo anterior es null
                            nodo->anterior->ptrs[i]=nodder;                             // escribe en nodo anterior el nuevo nodo derecho
                        }else{
                            return nodder;
                        }
                    }
                }
            }else if (nodo->tipo == I){                                                 // si es un nodo intermedio
                TNodoArbolB *nodizq, *nodder;
                nodizq = creaNodoB(nodo->nElementos/2);
                nodder = creaNodoB(nodo->nElementos/2);
                if (dato < ((nodo->nElementos/2)+1) && dato > (nodo->nElementos/2)) {   // si va en el centro sube el mismo dato
                    
                    insertaDatoAB(nodo->anterior, dato);
                    ocu=0;
                    for (i = 0; i < (nodo->nElementos/2) ; i++) {                       // los datos menores a la clave se van a nodizq
                        insertaDatoAB(nodizq, nodo->claves[i]);
                        ocu++;
                        nodizq->ocupa=ocu;
                    }
                    ocu=0;
                    for (i = ((nodo->nElementos/2)+1); i<nodo->nElementos; i++) {       // los datos mayores a la clave se van a nodder
                        insertaDatoAB(nodder, nodo->claves[i]);
                        ocu++;
                        nodder->ocupa=ocu;
                    }
                    nodo->ocupa=0;
                    insertaDatoAB(nodo->anterior, dato);                                // sube el dato a anterior
                    for (i =0; i<(nodo->nElementos/2); i++) {                           // le pasa los apuntadores a la izquierda
                        nodizq->ptrs[i]=nodo->ptrs[i];
                    }
                    ordenaDatos(nodo->anterior);
                    nodder->ptrs[0]=aux;                                                // el aux que se regreso con la division anterior se va al 0
                    for (i=((nodo->nElementos/2)+1); i<nodo->nElementos; i++) {         // le pasa los apuntadores a la derecha
                        nodder->ptrs[i]=nodo->ptrs[i];
                    }
                    nodo->anterior->ptrs[nodo->anterior->ocupa-1]=nodizq;
                    nodo->anterior->ptrs[nodo->anterior->ocupa]=nodder;
                    free(nodo);                                                   // libera el nodo con el que se trabajo despues de hacer la division
                    return NULL ;
                }else if (dato<(nodo->nElementos/2)){                                 // si el dato va a la izquierda sube el dato claves[nElementos/2]
                    
                    sube = nodo->claves[nodo->nElementos/2];
                    nodo->claves[nodo->nElementos/2]= dato;
                    ocu=0;
                    for (i=0; i<nodo->nElementos/2; i++) {
                        insertaDatoAB(nodizq, nodo->claves[i]);
                        ocu++;
                        nodizq->ocupa=ocu;
                    }
                    ocu=0;
                    for (i = ((nodo->nElementos/2)+1); i<nodo->nElementos; i++) {
                        insertaDatoAB(nodder, nodo->claves[i]);
                        ocu++;
                        nodder->ocupa= ocu;
                    }
                    insertaDatoAB(nodo->anterior, dato);                                // sube el dato a anterior
                    for (i =0; i<(nodo->nElementos/2); i++) {                           // le pasa los apuntadores a la izquierda
                        nodizq->ptrs[i]=nodo->ptrs[i];
                    }
                    ordenaDatos(nodo->anterior);
                    nodder->ptrs[0]=aux;                                                // el aux que se regreso con la division anterior se va al 0
                    for (i=((nodo->nElementos/2)+1); i<nodo->nElementos; i++) {         // le pasa los apuntadores a la derecha
                        nodder->ptrs[i]=nodo->ptrs[i];
                    }
                    nodo->anterior->ptrs[nodo->anterior->ocupa-1]=nodizq;
                    nodo->anterior->ptrs[nodo->anterior->ocupa]=nodder;
                    free(nodo);                                                       // libera el nodo con el que se trabajo despues de hacer la division
                    return NULL ;
                    
                }else{                                                                // si el dato va a la derecha sube el dato claves[(nElementos/2)+1]
                sube = nodo->claves[(nodo->nElementos/2)+1];
                  nodo->claves[nodo->nElementos/2]= dato;
                    ocu=0;
                    for (i=0; i<nodo->nElementos/2; i++) {
                        insertaDatoAB(nodizq, nodo->claves[i]);
                        ocu++;
                        nodizq->ocupa=ocu;
                    }
                    ocu=0;
                    for (i = ((nodo->nElementos/2)+1); i<nodo->nElementos; i++) {
                        insertaDatoAB(nodder, nodo->claves[i]);
                        ocu++;
                        nodder->ocupa= ocu;
                    }
                    insertaDatoAB(nodo->anterior, dato);                                // sube el dato a anterior
                    for (i =0; i<(nodo->nElementos/2); i++) {                           // le pasa los apuntadores a la izquierda
                        nodizq->ptrs[i]=nodo->ptrs[i];
                    }
                    ordenaDatos(nodo->anterior);
                    nodder->ptrs[0]=aux;                                                // el aux que se regreso con la division anterior se va al 0
                    for (i=((nodo->nElementos/2)+1); i<nodo->nElementos; i++) {         // le pasa los apuntadores a la derecha
                        nodder->ptrs[i]=nodo->ptrs[i];
                    }
                    nodo->anterior->ptrs[nodo->anterior->ocupa-1]=nodizq;
                    nodo->anterior->ptrs[nodo->anterior->ocupa]=nodder;
                    free(nodo);                                                       // libera el nodo con el que se trabajo despues de hacer la division
                    return NULL ;
                }
            }
        }else{                                                          // se divide la raiz
            printf("no hice el codigo para dividir la raiz :C es muy confuso");
            return NULL;
        }
    return NULL;
}

