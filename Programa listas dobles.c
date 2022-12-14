#include <stdio.h>
#include <stdlib.h>
#include <curse.h>

typedef struct nodo{
    int dato;            // #define MAXNOM 45
    char  *nombre; // nombre[MAXNOM]
    long  telefono;
    struct nodo *sig;
    struct nodo *ant;
}TNodoD;

typedef struct{
    TNodoD *prim;
    TNodoD *ult;
}TCabD;

void presentacion(void);
void inicializaCabezas(TCabD *cabD);
void capturaDato(int *info);
TNodoD *creaNodo(int info);
void creaNodo(TCabD *cabD, int info);
int insertaInicio(TCabD *cabD, int info);
int insertaOrdenadoD(TCabD *cabD, int info);
int eliminaOrdenadoD(TCabD *cabD, int info);
int eliminaFinal(TCabD *cabD);
void insertaFinal(TCabD *cabD, int info);
void muestra(TNodoD *cab);

int main(){
   int Op, dato, Res;
   TCabD cabD;

    presentacion();
    inicializaCabezas(&cabD);
    do{
        printf("\n\nOPCIONES LISTAS DOBLES:\n\n");
        printf(" 1.-Insertar al inicio\n 2.-Insertar al final\n 3.-Insertar ordenado\n 4.-Eliminar ordenado\n 5.-Muestra lista\n 6.-Salir\n");
        scanf("%d", &Op);
        switch(Op){
            case 1: capturaDato(&dato);
                    Res=insertaInicio(&cabD, dato);
                    if( Res == 0)
                      printf("No se pudo insertar");
                    break;
            case 2:insertaFinal(&cabD,dato);
                    break;
            case 3:Res=insertaOrdenadoD(&cabD,dato);
                    break;
            case 4:Res=eliminaOrdenadoD(&cabD,dato);
                    break;
            case 5:muestra(cabD.prim);
                    break;
            default:printf("ERROR: Seleccion NO valida");
                    break;
        }
    }while(Op!=6);
    return(0);
}

void presentacion(void){

}

void inicializaCabezas(TCabD *cabD){
    cabD->prim=NULL;
    cabD->ult=NULL;
}

void capturaDato(int *info){
    printf("Ingrese por favor el dato de la lista: ");
    scanf("%d", info);
}

TNodoD *creaNodo(int info){
    TNodoD *nuevo;
    nuevo=(TNodoD*)malloc(sizeof(TNodoD));
    if(nuevo){
        nuevo->sig=NULL;
        nuevo->ant=NULL;
        nuevo->dato=info;
        nuevo->telefono=0;

    }
    return(nuevo);
}

/* Funcion que reserva memoria para un
   nuevo nodo.
   Parametros: in info, inout cabD
*/
void creaNodo(TCabD *cabD, int info){

}

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

int eliminaFinal(TCabD *cabD){

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
