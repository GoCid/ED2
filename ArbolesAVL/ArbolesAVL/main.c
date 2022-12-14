//
//  main.c
//  ArbolesAVL
//
//  Created by Leonardo Alejandro González López on 12/06/21.
//  Copyright © 2021 UASLP. All rights reserved.
//

#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include <time.h>

typedef struct nod{
    int info;
    struct nod *izq, *der;
    int FE;
}TNodoABa;
//protos
TNodoABa *creaNodoABa(int x);
int inserta(TNodoABa **nodo, int dato);
int elimina(TNodoABa **nodo, TNodoABa **aux, int x);
int buscaInmediato(TNodoABa **nodo,TNodoABa **aux);
void inorder(TNodoABa *nodo);
void preOrder(TNodoABa *nodo);
void postOrder(TNodoABa *nodo);
void menu(void);
//protos

int main()
{
    TNodoABa *aux, *raiz=NULL;
    int i, n, bus, op, cd, ins;
    do{
    menu();
    scanf("%d", &op);
    switch(op)
    {
        case 1:
            printf("\nInsertar datos o inicializar con arbol predeterminado(1 predeterminado, 2 insertat datos): ");
            scanf("%d",&ins);
            if(ins==1)
            {
                printf("\nArbol predeterminado: ");
                int n2[17]={58, 43, 75, 86, 65, 70,67,73,93,69,25,66,68,47,62,10,60};
                for(i=0; i<17; i++)
                {
                    inserta(&raiz, n2[i]);
                    preOrder(raiz);
                }
            }

            if(ins==2)
            {
                printf("Cuantos datos quieres insertar? ");
                scanf("%d", &cd);
                TNodoABa *raiz = NULL;
                for(i=0; i<cd; i++)
                {
                    printf("nodo %d: ", i+1);
                    scanf("%d", &n);
                    inserta(&raiz, n);
                }
                printf("\nArbol ingresado\n");
                preOrder(raiz);
                printf("\n");
                }


            break;

        case 2:
            printf("\n Inorder");
            inorder(raiz);
            break;

        case 3:
            printf("\n Preorder");
            preOrder(raiz);
            break;
        case 4:
            printf("\n Postorder");
            postOrder(raiz);
            break;

        case 5:
            printf("Que dato deseas eliminar? ");
            scanf("%d", &bus);
            elimina(&raiz, &aux, bus);
            printf("\nArbol:\n");
            preOrder(raiz);
            printf("\n");
            break;
    }
    }while(op != 6);
    
}

//
void menu()
{
    printf("\n 1)Insertar\n 2)Inorder\n 3)Preorder\n 4)Postorder\n 5)Elimina nodo\n 6)Salir\t\n Opcion: ");
}

//
TNodoABa *creaNodoABa(int x)
{
    TNodoABa *aux;
    aux =(TNodoABa*)malloc(sizeof(TNodoABa));
    aux->info=x;
    aux->izq=aux->der=NULL;
    aux->FE=0;
    return(aux);
}

//
void inorder(TNodoABa *nodo)
{
    if(nodo != NULL){
        inorder(nodo->izq);
        printf(" %d[%d]", nodo->info, nodo->FE);
        inorder(nodo->der);
    }
}

//
void preOrder(TNodoABa *nodo)
{
    if(nodo != NULL){
        printf(" %d[%d]", nodo->info, nodo->FE);
        preOrder(nodo->izq);
        preOrder(nodo->der);
    }
}

void postOrder(TNodoABa *nodo)
{
    if(nodo != NULL){
        postOrder(nodo->izq);
        postOrder(nodo->der);
        printf(" %d[%d]", nodo->info, nodo->FE);
    }
}

//
int inserta(TNodoABa **nodo, int dato)
{
    int band = 0;
    TNodoABa *nodo1, *nodo2;

    if(*nodo == NULL)
    {
        (*nodo) = creaNodoABa(dato);
        band = 1;
    }

    else
        if(dato < (*nodo)->info)
        {
            band = inserta(&((*nodo)->izq), dato); //izq FE -1
            if(band == 1)
            {
                switch((*nodo)->FE)
                {
                    case 1: (*nodo)->FE = 0;
                            band = 0;
                            break;
                    case 0: (*nodo)->FE= -1;
                            break;
                    case -1: nodo1= (*nodo)->izq;
                            if(nodo1->FE <= 0)//rotacion II
                            {
                                (*nodo)->izq = nodo1->der;
                                nodo1->der = (*nodo);
                                (*nodo)->FE = 0;
                                (*nodo) = nodo1;
                                (*nodo)->FE = 0;
                            }
                            else //rotacion ID
                            {
                                nodo2 = nodo1->der;
                                nodo1->der = nodo2->izq;
                                nodo2->izq = nodo1;
                                (*nodo)->izq = nodo2->der;
                                nodo2->der = (*nodo);
                                switch(nodo2->FE)
                                {
                                    case 1: (*nodo)->FE = 0;
                                             nodo1->FE = 1;
                                             nodo2->FE = 0;
                                             break;
                                    case 0:  (*nodo)->FE = 0;
                                             nodo1->FE = 0;
                                             nodo2->FE = 0;
                                             break;
                                    case -1:  (*nodo)->FE = -1;
                                             nodo1->FE = 0;
                                             nodo2->FE = 0;
                                             break;
                                }
                                (*nodo) = nodo2;
                            }
                            band =0;
                            break;
                }
            }

        }

        else
            if(dato > (*nodo)->info)
            {
                band = inserta(&((*nodo)->der), dato);
                if(band == 1)
                {
                    switch((*nodo)->FE) // der FE *1
                    {
                        case -1: (*nodo)->FE = 0;
                                band = 0;
                                break;
                        case 0: (*nodo)->FE= 1;
                                break;
                        case 1: nodo1= (*nodo)->der;
                            if(nodo1->FE >= 0)//rotacion DD
                            {
                                (*nodo)->der = nodo1->izq;
                                nodo1->izq = (*nodo);
                                (*nodo)->FE = 0;
                                (*nodo) = nodo1;
                                (*nodo)->FE = 0;
                            }
                            else //rotacion ID
                            {
                                nodo2 = nodo1->izq;
                                nodo1->izq = nodo2->der;
                                nodo2->der = nodo1;
                                (*nodo)->der = nodo2->izq;
                                nodo2->izq = (*nodo);
                                switch(nodo2->FE)
                                {
                                    case -1: (*nodo)->FE = 0;
                                             nodo1->FE = 1;
                                             nodo2->FE = 0;
                                             break;
                                    case 0:  (*nodo)->FE = 0;
                                             nodo1->FE = 0;
                                             nodo2->FE = 0;
                                             break;
                                    case 1:  (*nodo)->FE = -1;
                                             nodo1->FE = 0;
                                             nodo2->FE = 0;
                                             break;
                                }
                                (*nodo) = nodo2;
                            }
                            band =0;
                            break;

                    }
                }
            }

            return(band);
}

//
int elimina(TNodoABa **nodo, TNodoABa **aux, int x)
{
    int temp;
    int band = 0;
    TNodoABa *nodo1, *nodo2;

    if(*nodo==NULL)
        *aux=NULL;
    else
        {
        if((*nodo)->info>x)
        {
            band=elimina(&((*nodo)->izq),aux,x);
    if(band==1)
    {
        switch((*nodo)->FE)
        {
        case -1:(*nodo)->FE=0;
            band=0;
            break;
        case 0:(*nodo)->FE=1;
            break;
        case 1:nodo1=(*nodo)->der;
        if(nodo1->FE>=0)//rotacion DD
        {
            (*nodo)->der=nodo1->izq;
            nodo1->izq=(*nodo);
            (*nodo)->FE=0;
            (*nodo)=nodo1;
            (*nodo)->FE=0;
        }
        else //rotacion DI
        {
            nodo2=nodo1->izq;
            nodo1->izq=nodo2->der;
            nodo2->der=nodo1;
            (*nodo)->der=nodo2->izq;
            nodo2->izq=(*nodo);
            switch(nodo2->FE)
            {
            case -1:(*nodo)->FE=0;
                nodo1->FE=1;
                nodo2->FE=0;
                break;
            case 0: (*nodo)->FE=0;
                nodo1->FE=0;
                nodo2->FE=0;
                break;
            case 1: (*nodo)->FE=-1;
                nodo1->FE=0;
                nodo2->FE=0;
                break;
            }
            (*nodo)=nodo2;
        }
        band=0;
        break;
        }
        }
    }
    else
        if((*nodo)->info<x)
        {
        band=elimina(&((*nodo)->der),aux,x);
    if(band==1)
        {
        switch((*nodo)->FE)
        {
        case 1:(*nodo)->FE=0;
            band=0;
            break;
        case 0:(*nodo)->FE=-1;
            break;
            case -1:nodo1=(*nodo)->izq;
            if(nodo1->FE<=0)//rotacion II
            {
                (*nodo)->izq=nodo1->der;
                nodo1->der=(*nodo);
                (*nodo)->FE=0;
                (*nodo)=nodo1;
                (*nodo)->FE=0;
            }
            else //rotacion ID
            {
                nodo2=nodo1->der;
                nodo1->der=nodo2->izq;
                nodo2->izq=nodo1;
                (*nodo)->izq=nodo2->der;
                nodo2->der=(*nodo);
                switch(nodo2->FE)
                {
                case 1:(*nodo)->FE=0;
                    nodo1->FE=1;
                    nodo2->FE=0;
                    break;
                case 0: (*nodo)->FE=0;
                    nodo1->FE=0;
                    nodo2->FE=0;
                    break;
                case -1: (*nodo)->FE=-1;
                    nodo1->FE=0;
                    nodo2->FE=0;
                    break;
                }
                (*nodo)=nodo2;
                }
            band=0;
            break;
            }
        }
    }
    else
    {
        *aux=*nodo;
        if((*aux)->der==NULL && (*aux)->izq==NULL)
        *nodo=NULL;
    else
        if((*aux)->der && !(*aux)->izq)
        *nodo=(*aux)->der;
    else
        if(!(*aux)->der && (*aux)->izq)
        *nodo=(*aux)->izq;
        else
            {
                band=buscaInmediato(&((*nodo)->der),aux);
                temp=(*nodo)->info;
                (*nodo)->info=(*aux)->info;
                (*aux)->info=temp;
                if(band==1)
                {
                switch((*nodo)->FE)
                {
                case 1:(*nodo)->FE=0;
                    band=0;
                    break;
                case 0:(*nodo)->FE=-1;
                    break;
                case -1:nodo1=(*nodo)->izq;
                if(nodo1->FE<=0)//rotacion II
                    {
                        (*nodo)->izq=nodo1->der;
                        nodo1->der=(*nodo);
                        (*nodo)->FE=0;
                        (*nodo)=nodo1;
                        (*nodo)->FE=0;
                    }
                    else //rotacion ID
                    {
                    nodo2=nodo1->der;
                    nodo1->der=nodo2->izq;
                    nodo2->izq=nodo1;
                    (*nodo)->izq=nodo2->der;
                    nodo2->der=(*nodo);
                    switch(nodo2->FE)
                    {
                    case 1:(*nodo)->FE=0;
                        nodo1->FE=1;
                        nodo2->FE=0;
                        break;
                    case 0: (*nodo)->FE=0;
                        nodo1->FE=0;
                        nodo2->FE=0;
                        break;
                    case -1:(*nodo)->FE=-1;
                        nodo1->FE=0;
                        nodo2->FE=0;
                        break;
                    }
                    (*nodo)=nodo2;
                    }
                //band=0;
                break;
                }
            }
        }
    }
}
    return(band);
}

//
int buscaInmediato(TNodoABa **nodo,TNodoABa **aux)
{
    int band;
    TNodoABa *nodo1, *nodo2;
    if((*nodo)->izq==NULL)
    {
        *aux=*nodo;
        *nodo=(*aux)->der;
        (*aux)->der=NULL;
        band=1;
    }
    else
    {
        band=buscaInmediato(&((*nodo)->izq),aux);
        if(band==1)
        {
            switch((*nodo)->FE)
            {
            case -1:(*nodo)->FE=0;
                band=0;
                break;
            case 0:(*nodo)->FE=1;
                break;
            case 1:nodo1=(*nodo)->der;
                if(nodo1->FE>=0)//rotacion DD
                {
                    (*nodo)->der=nodo1->izq;
                    nodo1->izq=(*nodo);
                    (*nodo)->FE=0;
                    (*nodo)=nodo1;
                    (*nodo)->FE=0;
                }
                else //rotacion DI
                    {
                        nodo2=nodo1->izq;
                        nodo1->izq=nodo2->der;
                        nodo2->der=nodo1;
                        (*nodo)->der=nodo2->izq;
                        nodo2->izq=(*nodo);
                        switch(nodo2->FE)
                        {
                        case -1:(*nodo)->FE=0;
                            nodo1->FE=1;
                            nodo2->FE=0;
                            break;
                        case 0: (*nodo)->FE=0;
                            nodo1->FE=0;
                            nodo2->FE=0;
                            break;
                        case 1: (*nodo)->FE=-1;
                            nodo1->FE=0;
                            nodo2->FE=0;
                            break;
                        }
                        (*nodo)=nodo2;
                        }
                        // band=0;
                    break;
                    }
                }
            }
        return(band);
}
