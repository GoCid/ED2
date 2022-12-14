//
//  main.c
//  arboles
//
//  Created by Leonardo Alejandro González López on 13/05/21.
//  Copyright © 2021 UASLP. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct nodo{
    int dato;
    struct nodo *der;
    struct nodo *izq;
    struct nodo *padre;
}TNodoAB;

//Proto
void presentacion(void);

void menu(void);

TNodoAB *creaNodo(int dato, TNodoAB *padre);

void inserta(TNodoAB **arbol, int d, TNodoAB *padre);

void preOrden(TNodoAB *arbol);

void inOrder(TNodoAB *arbol);

void postOrder(TNodoAB *arbol);

void eliminaNodoABB(TNodoAB *arbol, int nodo);

void elimina(TNodoAB *nodoElimina);

TNodoAB *minimo(TNodoAB *arbol);

void reemplazar(TNodoAB *arbol, TNodoAB *reemplazo);

void destruirNodo(TNodoAB *nodo);
//Protos


int main() {
    presentacion();
    int aux = 0, info = 0;
    TNodoAB *arbol = NULL;
    do {
        printf("\n\t\t\t-----Menu Principal-----\n");
        printf(" Elige una opcion:\n 1. Insertar Nodo\n 2. Elimina Nodo\n 3. PreOrden\n 4. PostOrden\n 5. InOrden\n 6. Salir\n");
        scanf("%i", &aux);
        switch (aux) {
            case 1:
                    printf("\n Ingresa el dato:\n");
                    scanf("%i", &info);
                    inserta(&arbol, info, NULL);
                break;
            case 2:
                printf("\n Ingresa el dato a eliminar:\n");
                scanf("%i", &info);
                eliminaNodoABB(arbol, info);
                break;
            case 3:
                if (arbol == NULL) {
                    printf("\n Aun no se ingresan datos\n");
                }else{
                    preOrden(arbol);
                }
                break;
            case 4:
                if (arbol == NULL) {
                    printf("\n Aun no se ingresan datos\n");
                }else{
                    postOrder(arbol);
                }
                break;
            case 5:
                if (arbol == NULL) {
                    printf("\n Aun no se ingresan datos\n");
                }else{
                    inOrder(arbol);
                }
                break;
            default:
                printf("\n :D\n");
                break;
        }
    } while (aux != 6);
}

//
void presentacion(void){
        char x;
        printf("\t\t     ESTRUCTURAS DE DATOS II \n \t\t Leonardo Alejandro Gonzalez Lopez \n \t\t Programa de la semana 13: Arboles Binarios de Busqueda \n \t\t\t\t 13/Mayo/2021 \n \t\t Profesor: Francisco Edgar Castillo Barrera \n \t\t Version 1.0 \n Presione cualquier tecla para continuar :D \n");
        gets(&x);
}

//
TNodoAB *creaNodo(int dato, TNodoAB *padre){
    TNodoAB *nuevoNodo = NULL;
    
    nuevoNodo= (TNodoAB*)malloc(sizeof(TNodoAB));
    nuevoNodo->dato = dato;
    nuevoNodo->der = NULL;
    nuevoNodo->izq = NULL;
    nuevoNodo->padre = padre;
    
    return nuevoNodo;
}

//
void inserta(TNodoAB **arbol, int info, TNodoAB *padre){
    if (*arbol == NULL) {
        TNodoAB nuevoNodo = *creaNodo(info, padre);
        *arbol = &nuevoNodo;
    }else{
        if (info<(*arbol)->dato) {
            inserta(&(*arbol)->izq, info, *arbol);
        }else{
            if (info != (*arbol)->dato) {
                inserta(&(*arbol)->der, info, *arbol);
            }
        }
    }
}

//
void preOrden(TNodoAB *arbol){
    if (arbol!=NULL) {
        printf("%i", arbol->dato);
        preOrden(arbol->izq);
        preOrden(arbol->der);
    }
}

//
void inOrder(TNodoAB *arbol){
    if (arbol!=NULL) {
        inOrder(arbol->izq);
        printf("%i", arbol->dato);
        inOrder(arbol->der);
    }
}

//
void postOrder(TNodoAB *arbol){
    if(arbol!=NULL){
        postOrder(arbol->izq);
        postOrder(arbol->der);
        printf("%i", arbol->dato);
    }
}

//
void eliminaNodoABB(TNodoAB *arbol, int nodo){
    if (arbol == NULL) {
        return;
    }else{
        if (nodo < arbol->dato) {
            eliminaNodoABB(arbol->izq, nodo);
        }else{
            if (nodo > arbol->dato) {
                eliminaNodoABB(arbol->der, nodo);
            }
            else{
                elimina(arbol);
            }
        }
    }
}

//
TNodoAB *minimo(TNodoAB *arbol){
    if (arbol == NULL) {
        return NULL;
    }
    if (arbol->izq) {
        return minimo(arbol->izq);
    }else{
        return arbol;
    }
}

//
void reemplazar(TNodoAB *arbol, TNodoAB *reemplazo){
    if (arbol->padre) {
        if (arbol->dato == arbol->padre->izq->dato) {
            arbol->padre->izq = reemplazo;
        }else if (arbol->dato == arbol->padre->der->dato){
            arbol->padre->der = reemplazo;
        }
    }
    if (reemplazo) {
        reemplazo->padre = arbol->padre;
    }
}

//
void elimina(TNodoAB *nodoElimina){
    if (nodoElimina->izq && nodoElimina ->der) {
        TNodoAB *menor = minimo(nodoElimina->der);
        nodoElimina->dato = menor->dato;
        elimina(menor);
    }else if (nodoElimina->izq){
        reemplazar(nodoElimina, nodoElimina->izq);
        destruirNodo(nodoElimina);
    }else if (nodoElimina->der){
        reemplazar(nodoElimina, nodoElimina->der);
        destruirNodo(nodoElimina);
    }else{
        reemplazar(nodoElimina, NULL);
        destruirNodo(nodoElimina);
    }
}

//
void destruirNodo(TNodoAB *nodo){
    nodo->izq = NULL;
    nodo->der = NULL;
    free(nodo);
}
