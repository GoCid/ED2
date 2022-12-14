#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void presentacion(void);
void tamMat(int *n);
void pideDatos(float **Arre,float **Arre2, int n);
void reservaMemoria(float ***Arre,float ***Arre2, int n);
void muestraMatriz(float **Arre,float **Arre2 ,int n);
void reduccionRenglones(float **Arre,float **Arre2,int n);
void muestraMatrizInversa(float **Arre,float **Arre2 ,int n);
void liberaMemoria(float ***Arre,float ***Arre2, int n);

int main(void) {
    float **ArreMat=NULL, **ArreMat2=NULL;
    int n;
    presentacion();
    tamMat(&n);
    reservaMemoria(&ArreMat,&ArreMat2,n);
    pideDatos(ArreMat,ArreMat2,n);
    muestraMatriz(ArreMat,ArreMat2,n);
    reduccionRenglones(ArreMat,ArreMat2,n);
    muestraMatrizInversa(ArreMat,ArreMat2,n);
    liberaMemoria(&ArreMat,&ArreMat2,n);
    
    
}


void tamMat(int *n){
    printf("\n Escribe el numero de renglones y columna de la matriz: ");
    scanf("%d",n);
}

void reservaMemoria(float ***Arre,float ***Arre2, int n){
    int icont;

    *Arre = (float **)malloc(sizeof(float *)*n);
    if(*Arre != NULL)
    {
        
        for (icont = 0; icont<n; icont++)
        {
            *(*Arre+icont)=(float*)malloc(sizeof(float)*n);
            if (*(Arre+icont)==NULL)
            {
                exit(1);
            }
        }
    }
    *Arre2 = (float **)malloc(sizeof(float *)*n);
    if(*Arre2 != NULL)
    {
        for (icont = 0; icont<n; icont++)
        {
            *(*Arre2+icont)=(float*)malloc(sizeof(float)*n);
            if (*(Arre2+icont)==NULL)
            {
                exit(1);
            }
        }
    }
}


void pideDatos(float **Arre,float **Arre2, int n){
    int iren, jcol;

    for (iren=0; iren<n; iren++) {
        printf("\n");
        for(jcol=0; jcol<n; jcol++) {
            printf("\n Escribe el casillero [%d][%d]: ",iren,jcol);
            scanf("%f", (*(Arre+iren)+jcol));
            if(iren==jcol){
                *(*(Arre2+iren)+jcol)=1;
            }else{
                *(*(Arre2+iren)+jcol)=0;
            }
                
        }
    }
}

void muestraMatriz(float **Arre,float **Arre2 ,int n){
    int iren, jcol;
 printf("Matriz A con matriz identidad(B):\n");
    for (iren=0; iren<n; iren++) {
        printf("\n");
        for (jcol=0; jcol<n; jcol++) {
            printf("%.0f\t",*(*(Arre+iren)+jcol));
        }
        printf("\t");
        for (jcol=0; jcol<n; jcol++) {
            printf("%.0f\t",*(*(Arre2+iren)+jcol));
        }
    }printf("\n");
}

void reduccionRenglones(float **Arre,float **Arre2,int n){
    int i,j,k,piv;
    float aux;
    for(i=0;i<n;i++){
        piv=*(*(Arre+i)+i);
        for(k=0;k<n;k++){
            *(*(Arre+i)+k)=*(*(Arre+i)+k)/piv;
            *(*(Arre2+i)+k)=*(*(Arre2+i)+k)/piv;
        }
        for(j=0;j<n;j++){
            if(i!=j){
                aux=*(*(Arre+j)+i);
                for(k=0;k<n;k++){
                    *(*(Arre+j)+k)=*(*(Arre+j)+k)-(aux*(*(*(Arre+i)+k)));
                    *(*(Arre2+j)+k)=*(*(Arre2+j)+k)-(aux*(*(*(Arre2+i)+k)));
                }
            }
                
        }
    }
}

void muestraMatrizInversa(float **Arre,float **Arre2 ,int n){
    int iren, jcol;
 printf("Matriz identidad(A) con matriz inversa(B):\n");
    for (iren=0; iren<n; iren++) {
        printf("\n");
        for (jcol=0; jcol<n; jcol++) {
            printf("%.0f\t",*(*(Arre+iren)+jcol));
        }
        printf("\t");
        for (jcol=0; jcol<n; jcol++) {
            printf("%.2f\t",*(*(Arre2+iren)+jcol));
        }
    }printf("\n");
}

void liberaMemoria(float ***Arre,float ***Arre2, int n){
    int iren;
    
    if (*Arre) {
        for (iren=0; iren<n; iren++) {
            free(*(*Arre+iren));
            
        }
        free(*Arre);
        *Arre=NULL;
    }
    
    if (*Arre2) {
        for (iren=0; iren<n; iren++) {
            free(*(*Arre2+iren));
            
        }
        free(*Arre2);
        *Arre2=NULL;
    }
}
