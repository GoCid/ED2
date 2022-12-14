//
//  main.c
//  Apuntadoreds
//
//  Created by Leonardo Alejandro González López on 12/02/21.
//  Copyright © 2021 UASLP. All rights reserved.
//

#include <stdio.h>
//
void PideNumero(int *num);

void IntercambiaNumeros (int *Numero1, int *Numero2);

void Presentacion(void);

void MuestraNumeros(int Numero1, int Numero2);
//

int main() {
    int Num1, Num2;
    char x;
    Presentacion();
    PideNumero(&Num1);
    PideNumero(&Num2);
    IntercambiaNumeros(&Num1, &Num2);
    MuestraNumeros(Num1, Num2);
    printf(" Pulsa cualquier telca para salir \n");
    fpurge(stdin);
    gets(&x);
}

//
void Presentacion(){
    char x;
    printf("\t\t     ESTRUCTURAS DE DATOS II \n \t\t Leonardo Alejandro Gonzalez Lopez \n \t\t Programa de la semana: APUNTADORES \n \t\t\t\t 12/Febrero/2021 \n \t\t Profesor: Francisco Edgar Castillo Barrera \n \t\t Version 1.0 \n Presione cualquier tecla para continuar :D ");
    gets(&x);
}
void PideNumero(int *num){
    printf(" Ingresa un numero: \n");
    scanf("%i", num);
}

void IntercambiaNumeros (int *Numero1, int *Numero2){
    int aux=0;
    aux = *Numero1;
    *Numero1 = *Numero2;
    *Numero2 = aux;
}

void MuestraNumeros(int Numero1, int Numero2){
    printf("El numero 1 es : %i y el numero 2 es : %i", Numero1, Numero2);
}
