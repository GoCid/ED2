//
//  main.c
//  metroGrafo
//
//  Created by Leonardo Alejandro González López on 30/04/21.
//  Copyright © 2021 UASLP. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct nodoArista{
    
    struct nodoArista *sig;
    struct nodo *origen;
    struct nodo *destino;
    
}TArista;

typedef struct nodo{
    int dato;
    struct nodo *sig;
    TArista *arista;
}TVertice;

//protos
TVertice *buscaVertice( TVertice *vr, int vertice);

TArista *creaArista(TVertice *origen, TVertice *destino);

int insertaArista(TVertice **cab, int ori, int dest);

int insertaVertice(TVertice **cab, int vertice);
//protos
int main() {
    
}

//
TVertice *buscaVertice( TVertice *vr, int vertice){
    
    TVertice *aux;
    
    for (aux = vr; aux && aux->dato != vertice; aux = aux->sig) {
    }
    return aux;
}

TArista *creaArista(TVertice *origen, TVertice *destino){
    TArista *nuevo;
    nuevo = (TArista*)malloc(sizeof(TArista));
    if (nuevo) {
        nuevo->sig=NULL;
        nuevo->origen = origen;
        nuevo->destino = destino;
    }
    return (nuevo);
}

int insertaArista(TVertice **cab, int ori, int dest){
    TVertice *origen, *destino;
    TArista *nuevo;
    int band=0;
    
    origen = buscaVertice(*cab, ori);
    destino = buscaVertice(*cab, dest);
    if (origen!= NULL && destino != NULL) {
        nuevo = creaArista(ori, dest);
        if (nuevo) {
            nuevo->sig = origen->arista;
            origen->arista = nuevo;
            band++;
        }
    }
    return (band);
}

int insertaVertice(TVertice **cab, int vertice){
    TVertice *aux;
    int bandd = 0;
    aux = buscaVertice(*cab, vertice);
    if (aux == NULL) {
        bandd++;
    }
    return bandd;
}
