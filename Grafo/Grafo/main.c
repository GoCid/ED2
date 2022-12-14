//
//  main.c
//  Grafo
//
//  Created by Leonardo Alejandro González López on 12/06/21.
//  Copyright © 2021 UASLP. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct ver{
    int nVer;
    struct ver *sig;
    struct ar *aba;
}TVertice;

typedef struct ar{
    int peso;
    struct ar *sig;
    TVertice *arr;
}TArista;

int **CreaArreglo2D(int n, int x);
void CapturaArreglo(int **a, int n, int x);
TArista *crea_nodoA(TVertice *d);
TVertice *crea_verticeV(int dato);
void Crea_Grafo(TVertice **grafo, int **a, int nv);
void Inserta_FinalNV(TVertice **cab, int dato);
void Inserta_FinalNA(TArista **cab, TVertice *dato);
void ImprimeGrafo(TVertice *grafo);

int main()
{
    int **pa;
    int ne,x;
    TVertice *grafo=NULL;
    printf("Indique renglones:\n");
    scanf("%d",&ne);
    printf("Indique columnas:\n");
    scanf("%d",&x);
    pa=CreaArreglo2D(ne,x);
    CapturaArreglo(pa,ne,x);

    Crea_Grafo(&grafo,pa,ne);
    ImprimeGrafo(grafo);
}

int **CreaArreglo2D(int ren, int col)
{
    int **p,i,j;
    p=(int**)malloc(sizeof(int*)*ren);
    if(p==NULL)
    {
        printf("No fue posible crear el arreglo\n");
        exit(1);
    }else{
            for(i=0;i<ren;i++)
            {
                *(p+i)=(int*)malloc(sizeof(int)*col);
                if(*(p+i)!=NULL)
                {
                    for(j=0;j<col;j++)
                    {
                        *(*(p+i)+j)=0;
                    }
                }else{
                        for(i--;i>=0;i--)
                        {
                            free(*(p+i));
                        }
                        free(p);
                        printf("No fue posible crear el arreglo\n");
                        p=NULL;
                        break;
                    }
            }
        }
    return(p);
}

void CapturaArreglo(int **a, int n, int x)
{
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<x;j++)
        {
            printf("Ingrese dato [%d][%d]:",i,j);
            scanf("%d",*(a+i)+j);
        }
    }
}

TArista *crea_nodoA(TVertice *d)
{
    TArista *a;
    a=(TArista*)malloc(sizeof(TArista));
    a->arr=d;
    a->sig=NULL;
    return(a);
}

TVertice *crea_verticeV(int dato)
{
    TVertice *a;
    a=(TVertice*)malloc(sizeof(TVertice));
    a->nVer=dato;
    a->sig=NULL;
    a->aba=NULL;
    return(a);
}

void Crea_Grafo(TVertice **grafo, int **a, int nv)
{
    int i,r,c;
    TVertice *origen,*destino;
    for(i=1;i<=nv;i++)
    {
        Inserta_FinalNV(&(*grafo),i);
    }
    for(origen=*grafo,r=0;origen!=NULL;origen=origen->sig,r++)
    {
        for(destino=*grafo,c=0;destino!=NULL;destino=destino->sig,c++)
        {
            if(*(*(a+r)+c)==1)
            {
                Inserta_FinalNA(&origen->aba,destino);
            }
        }
    }
}

void Inserta_FinalNV(TVertice **cab, int dato)
{
    TVertice *corre;
    if(*cab==NULL)
    {
        *cab=crea_verticeV(dato);
    }
    else{
    corre=*cab;
    while(corre->sig!=NULL)
    {
        corre=corre->sig;
    }
    corre->sig=crea_verticeV(dato);
    }

}

void Inserta_FinalNA(TArista **cab, TVertice *dato)
{
    TArista *corre;
    if(*cab==NULL)
    {
        *cab=crea_nodoA(dato);
    }
    else
    {
        corre=*cab;
        while(corre->sig!=NULL)
        {
            corre=corre->sig;
        }
        corre->sig=crea_nodoA(dato);
    }
}

void ImprimeGrafo(TVertice *grafo)
{
    TVertice *corre;
    TArista *corre2;
    for(corre=grafo;corre!=NULL;corre=corre->sig)
    {
        printf("Vertice %d: -> \n",corre->nVer);
        for(corre2=corre->aba;corre2!=NULL;corre2=corre2->sig)
        {
            printf("{%d} -> \n", corre2->arr->nVer);
        }
        printf("\n");
    }
}
