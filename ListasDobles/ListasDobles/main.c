//
//  main.c
//  ListasDobles
//
//  Created by Leonardo Alejandro González López on 25/03/21.
//  Copyright © 2021 UASLP. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
    int celular;
    char *nombre;
    char *correo;
    struct nodo *sig;
    struct nodo *ant;
}TNodoD;

typedef struct{
    TNodoD *prim;
    TNodoD *ult;
}TCabD;

//Protos
void Presentacion(void);

void inicializaCabezas(TCabD *cabD);

void capturaDato(int *info);

TNodoD *creaNodo(int info);

int insertaInicio(TCabD *cabD, int info);

int insertaOrdenado(TCabD *cabD, int info);

int eliminaOrdenado(TCabD *cabD, int info);

int eliminaFinal(TCabD **cabD);

void insertaFinal(TCabD *cabD, int info);

void muestra(TNodoD *cab);

//Protos

int main() {
    
    Presentacion();
    
    // profe perdon por enviarlo incompleto, mi situacion este mes no ha sido la mejor
}

//
void Presentacion(){
    char x;
    printf("\t\t     ESTRUCTURAS DE DATOS II \n \t\t Leonardo Alejandro Gonzalez Lopez \n \t\t Programa de la semana 5: Listas Dobles \n \t\t\t\t 25/Marzo/2021 \n \t\t Profesor: Francisco Edgar Castillo Barrera \n \t\t Version 1.0 \n Presione cualquier tecla para continuar :D ");
    gets(&x);
}

//
void inicializaCabezas(TCabD *cabD){
    cabD->prim=NULL;
    cabD->ult=NULL;
}

//
void capturaDato(int *info){
    printf("\n Ingrese el dato x");
    scanf("%d", info);
}

//
TNodoD *creaNodo(int info){
    TNodoD *nuevo;
    nuevo=(TNodoD *)malloc(sizeof(TNodoD));
    if (nuevo) {
        nuevo->sig=NULL;
        nuevo->ant=NULL;
        nuevo->dato=info;
        nuevo->telefono=info;
    }
    return (nuevo);
}

//
int insertaInicio(TCabD *cabD, int info){
    int ret=0;
    TNodoD *nuevo;
    nuevo=creaNodo(info);
    if(nuevo){
        if(cabD->prim==NULL){ //!cabD->prim
            cabD->prim=nuevo;
            cabD->ult=nuevo;
        }else{
            nuevo->sig=cabD->prim;
            cabD->prim->ant=nuevo;
            cabD->prim=nuevo;
        }
        ret++;
    }
    return(ret);
}

void muestra(TNodoD *cab){
    if(cab){
        printf("%d, ", cab->dato);
        muestra(cab->sig);
    }
}

int insertaOrdenadoD(TCabD *cabD, int info){
    int ret=0;
    TNodoD *nuevo, *aux;
    nuevo=creaNodo(info);
    if(nuevo){
        if(!cabD->prim){
            cabD->prim=nuevo;
            cabD->ult=nuevo;
        }else{
            for(aux=cabD->prim;aux&&aux->dato<info;aux=aux->sig);
            if(!aux){
                cabD->ult->sig=nuevo;
                nuevo->ant=cabD->ult;
                cabD->ult=nuevo;
            }else{
                if(aux==cabD->prim){
                    aux->ant=nuevo;
                    nuevo->sig=aux;
                    cabD->prim=nuevo;
                }else{
                    nuevo->sig=aux;
                    nuevo->ant=aux->ant;
                    aux->ant->sig=nuevo;
                    aux->ant=nuevo;
                }
            }
        }ret++;
    }return(ret);
}

int eliminaOrdenadoD(TCabD *cabD, int info){ // 23
    int band=0;
    TNodoD *aux;

    if(cabD->prim){
        for(aux=cabD->prim;aux && aux->dato!=info;aux=aux->sig);
        if(aux!=NULL){
            if(aux==cabD->prim&&aux==cabD->ult){
                cabD->prim=NULL;
                cabD->ult=NULL;
            }else{
                if(aux==cabD->prim){
                    cabD->prim=aux->sig;
                    cabD->prim->ant=NULL;
                }else{
                    if(aux==cabD->ult){
                        cabD->ult=aux->ant;
                        cabD->ult->sig=NULL;
                    }else{
                        aux->ant->sig=aux->sig;
                        aux->sig->ant=aux->ant;
                    }
                }band++;
                free(aux);
            }
        }
    }return(band);
}

int eliminaFinal(TCabD **cab){
    int band=0;
    TNodoD *aux;
    aux = (*cab)->ult;
    if ((*(*cab)).ult) {
        (*cab)->ult= aux->ant;
        free(aux);
        if ((*cab)->ult) {
            (*cab)->ult->sig=NULL;
        }else{
            (*cab)->prim=NULL;
        }
        band++;
    }
    return (band);
}

void insertaFinal(TCabD *cabD, int info){
    TNodoD *nuevo;
    nuevo=creaNodo(info);
    if(nuevo){
        if(cabD->prim){
            cabD->ult->sig=nuevo;
            nuevo->ant=cabD->ult;
            cabD->ult=nuevo;
        }else{
            cabD->prim=nuevo;
            cabD->ult=nuevo;
        }
    }
}

}
