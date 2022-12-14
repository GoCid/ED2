//
//  main.c
//  SumaYMultiplicacion
//
//  Created by Leonardo Alejandro González López on 26/02/21.
//  Copyright © 2021 UASLP. All rights reserved.
//
// ***NOTA*** si no esta en un entorno linux/mac, se deben borrar las funciones "fpurge(stdin);"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//Prototipos

void presentacion(void);

void tamMatriz(int *ren, int *col);

void reservaMemoria(int ***arre, int ren, int col);

void pideDatos(int **arre, int ren, int col);

void muestraMatriz(int **arre, int ren, int col);

void suma(int **arre, int **arre2, int **arre3, int ren, int col);

void multiplicacion(int **arre, int **arre2, int **arre3, int ren2, int col1);

void liberaMemoria(int ***arre, int ren);

void inversa(int **arre, int **matres, int ren, int col, int det);

int determinante(int **arre, int ren);

int cofactor(int **arre, int ren, int dot, int col);

void matPorEscalar(int **arre, int **arres, int esc, int ren, int col);

void transpuesta(int **arre, int ren, int col);
//Prototipos

int main() {
    int ren1, ren2, col1, col2;
    int **arre = NULL, **arre2 = NULL, **arre3 = NULL, det, esc;
    fflush(stdin);
    fpurge(stdin);
    while (1) {
        printf("\n\t\t\t-----MENU PRINCIPAL-----\n Elige una opcion: \n 1. Suma de matrices \n 2. Multiplicacion de matrices \n 3. Matriz Inversa\n 4. Transpuesta\n 5. Escalar por matriz\n 6. Salir\n");
        switch (getchar()) {
            //Suma
            case '1':
                printf("\n\t\t\t\t Suma de matrices \n\n\n");
                printf("\n Matriz 1 ");
                tamMatriz(&ren1, &col1);
                printf("\n Matriz 2 ");
                tamMatriz(&ren2, &col2);
                if (ren1 == ren2 && col1 == col2) {
                    reservaMemoria(&arre, ren1, col1);
                    reservaMemoria(&arre2, ren2, col2);
                    reservaMemoria(&arre3, ren1, col1);
                    printf("\n Ingresa los datos de la matriz 1: \n");
                    pideDatos(arre, ren1, col1);
                    fflush(stdin);
                    fpurge(stdin);
                    printf("\n Ingresa los datos de la matriz 2: \n");
                    pideDatos(arre2, ren2, col2);
                    fflush(stdin);
                    fpurge(stdin);
                    suma(arre, arre2, arre3, ren1, col1);
                    muestraMatriz(arre3, ren1, col1);
                    liberaMemoria(&arre, ren1);
                    liberaMemoria(&arre2, ren2);
                    liberaMemoria(&arre3, ren1);
                }else{
                    printf("\n No se pueden sumar matrices no cuadradas \n");
                }
                fflush(stdin);
                fpurge(stdin);
                break;
            //Multiplicacion
            case '2':
                printf("\n\t\t\t Multiplicacion de matrices \n\n");
                printf("\n Matriz 1");
                tamMatriz(&ren1, &col1);
                printf("\n Matriz 2");
                tamMatriz(&ren2, &col2);
                if (col1 == ren2) {
                    reservaMemoria(&arre, ren1, col1);
                    reservaMemoria(&arre2, ren2, col2);
                    reservaMemoria(&arre3, ren1, col1);
                    printf("\n Ingresa los datos de la matriz 1: \n");
                    fflush(stdin);
                    fpurge(stdin);
                    pideDatos(arre, ren1, col1);
                    printf("\n Ingresa los datos de la matriz 2: \n");
                    fflush(stdin);
                    fpurge(stdin);
                    pideDatos(arre2, ren2, col2);
                    multiplicacion(arre, arre2, arre3, ren2, col1);
                    printf("\n El producto de las matrices es: \n");
                    muestraMatriz(arre3, ren1, col2);
                    liberaMemoria(&arre, ren1);
                    liberaMemoria(&arre2, ren2);
                    liberaMemoria(&arre3, ren1);
                }else{
                    printf("\n No se pueden multiplicar las matrices, el numero de renglones tiene que ser igual al de las columnas \n ");
                }
                fflush(stdin);
                fpurge(stdin);
                break;
            //Inversa
            case '3':
                printf("\n\t\t\t Inversa de matriz \n\n");
                tamMatriz(&ren1, &col1);
                if (ren1 == col1) {
                    reservaMemoria(&arre2, ren1, col1);
                    pideDatos(arre2, ren1, col1);
                    reservaMemoria(&arre3, ren1, col1);
                    printf("\n Ingresa los datos de la matriz \n");
                    det = determinante(arre2, ren1);
                    printf("\n El determinante es: %2d \n", det);
                    printf("\n La matgriz inversa es: \n");
                    inversa(arre2, arre3, ren1, ren1, det);
                    liberaMemoria(&arre2, ren1);
                    liberaMemoria(&arre3, ren1);
                }else{
                    printf("\n Las matrices no cuadradas no tiene inversa \n");
                }
                fflush(stdin);
                fpurge(stdin);
                break;
            //Transpuesta
            case '4':
                printf("\n\t\t\t Transpuesta \n\n");
                tamMatriz(&ren1, &col1);
                reservaMemoria(&arre, ren1, col1);
                pideDatos(arre, ren1, col1);
                transpuesta(arre, ren1, col1);
                liberaMemoria(&arre, ren1);
                fflush(stdin);
                fpurge(stdin);
                break;
            //matpor escalar
            case '5':
                printf("\n\t\t\t Matriz por Escalar \n\n");
                tamMatriz(&ren1, &col1);
                reservaMemoria(&arre, ren1, col1);
                reservaMemoria(&arre2, ren1, col1);
                pideDatos(arre, ren1, col1);
                printf("\n Ingresa el numero escalar: \n");
                scanf("%d", &esc);
                matPorEscalar(arre, arre2, esc, ren1, col1);
                printf("\n El resultado es: \n");
                muestraMatriz(arre2, ren1, col1);
                liberaMemoria(&arre2, ren1);
                liberaMemoria(&arre, ren1);
                break;
            //Salir
            case '6':
                exit(EXIT_SUCCESS);
                break;
            case '\n':
                printf("\n No se ingreso ningun dato \n");
                fflush(stdin);
                fpurge(stdin);
                break;
            default:
                printf("\n Comando desconocido \n");
                fflush(stdin);
                fpurge(stdin);
                break;
        }
    }
}

//
void Presentacion(){
    char x;
    printf("\t\t     ESTRUCTURAS DE DATOS II \n \t\t Leonardo Alejandro Gonzalez Lopez \n \t\t Programa de la semana 3: Multiplicacion y Suma de matrices \n \t\t\t\t 26/Febrero/2021 \n \t\t Profesor: Francisco Edgar Castillo Barrera \n \t\t Version 1.0 \n Presione cualquier tecla para continuar :D ");
    gets(&x);
}

//
void tamMatriz(int *ren, int *col){
    printf("\n Escribe el numero de renglones de la matriz: ");
    scanf("%d",ren);
    printf("\n Escribe el numero de columnas: ");
    scanf("%d",col);
}

//
void reservaMemoria(int ***arre, int ren, int col){
    int icont;

    *arre = (int **)malloc(sizeof(int *)*ren);
    if(*arre != NULL)
    {
        for (icont = 0; icont<ren; icont++)
        {
            *(*arre+icont)=(int*)malloc(sizeof(int)*col);
            if (*(arre+icont)==NULL)
            {
                exit(1);
            }
        }
    }
}

//
void pideDatos(int **Arre, int ren, int col){
    int iren, jcol;

    for (iren=0; iren<ren; iren++) {
        printf("\n");
        for(jcol=0; jcol<col; jcol++) {
            printf("\n Escribe el casillero [%d][%d]", iren, jcol);
            scanf("%d", (*(Arre+iren)+jcol));
        }
    }
}

void muestraMatriz(int **arre, int ren, int col){
    int iren, jcol;

    for (iren=0; iren<ren; iren++) {
        printf("\n");
        for (jcol=0; jcol<col; jcol++) {
            printf("\n Dato [%i][%i]: %d \n", iren, jcol, *(*(arre+iren)+jcol));
        }
    }
}

//
void liberaMemoria(int ***arre, int ren){
    int iren;
    
    if (*arre) {
        for (iren=0; iren<ren; iren++) {
            free(*(*arre+iren));
            
        }
        free(*arre);
        *arre=NULL;
    }
}

//

void suma(int **arre, int **arre2, int **arre3, int ren, int col){
    int i, j;
    for (i=0; i<ren; i++) {
        for (j=0; j<col; j++) {
            *(*(arre3+i)+j) = *(*(arre+i)+j) + *(*(arre2+i)+j);
        }
    }
    printf("\n La suma de las matrices es: ");
    }

//
void multiplicacion(int **arre, int **arre2, int **arre3, int ren2, int col1){
    int i, j, k, acum;
    
    for (i=0; i<ren2; i++){
        
        for (j=0; j<col1; j++){
            
            acum=0;
            
            for (k=0; k<col1; k++) {
                
                acum = acum + (*(*(arre+i)+j) * *(*(arre2+i)+j));
            }
            *(*(arre3+i)+j)=acum;
        }
    }
}

//
int cofactor(int **arre, int orden, int ren, int col){
    int i, j, x = 0, y = 0;
    int **aux, n = orden-1, cof;
    reservaMemoria(&aux, orden, col);
    for (i = 0; i < orden; i++) {
       for (j = 0; j < orden; j++) {
          if (i != ren && j != col) {
             *(*(aux+x)+y) = *(*(arre+i)+j);
             y++;
             if (y >= n) {
                x++;
                y = 0;
             }
          }
       }
    }
    cof = pow(-1, ren + col) * determinante(aux, orden);
    liberaMemoria(&aux, orden);
    return cof;
}

//
int determinante(int **arre, int ren){
    int i, det=0;
    if (ren == 1) {
        det = *(*(arre+0)+0);
    }else{
        for (i=0; i<ren; i++) {
            det = det + *(*(arre+0)+i) * cofactor(arre, ren, 0, ren);
        }
    }
    return det;
}

//
void matPorEscalar(int **arre, int **arres, int esc, int ren, int col){
    int i, j;
    for (i=0; i<ren; i++){
        
        for (j=0; j<col; j++){
            *(*(arres+i)+j) = esc * *(*(arre+i)+j);
        }
    }
}

//
void inversa(int **arre, int **matres, int ren, int col, int det){
    int iren, jcol;
    double mdet;
    mdet = 1/det;
    for (iren=0; iren<ren; iren++) {
        printf("\n");
        for (jcol=0; jcol<col; jcol++) {
            printf("\n Dato [%i][%i]: %d/%3f \n", iren, jcol, *(*(arre+iren)+jcol), mdet);
        }
    }
}

//
void transpuesta(int **arre, int ren, int col){
    int i,j;
    printf("\n La matriz transpuesta es: \n");
    for(i = 0;i < col;i++){
        printf("\n\t\t");
        for(j = 0;j < ren;j++){
            printf("\n Dato [%i][%i]: %d \n", i, j, *(*(arre+j)+i));
            }
    }
}
