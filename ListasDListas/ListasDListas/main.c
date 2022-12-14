//
//  main.c
//  ListasDListas
//
//  Created by Leonardo Alejandro González López on 30/04/21.
//  Copyright © 2021 UASLP. All rights reserved.
// NOTA AUN NO ESTA COMPLETO
// NOTA .cid porque cid es mi apodo :D
// NOTA si esta en windows borrar el fpurge(stdin);
/*
 
 PLANTEAMIENTO:
 Hay de dos, usar memoria y que el usuario ingrese las lineas y las estaciones a las cuales se conectan, o bien tener un archivo
 con  la informacion requerida, esta ultima es la que planeo usar.
 En un archivo no hay apuntadores en si, es decir no existe un null pero siguen existiendo los numeros entonces planee la
 siguiente estructura
 NULL = -1
                                                    TVERTICE: (O bien, la linea)
 
    ApuntadorAnterior   |   NombreLinea   |   ApuntadorAListaEstacion   | ApuntadorSiguiente
 
 --ApuntadorAnterior, si es -1, No hay lineas registradas, si != -1 indica la direccion en el archivo donde inicia la lista
 de lineas
 --NombreLinea, el nombre de la linea, puede ser un numero o cadena
 --ApuntadorAListaEstacion, si es -1, No hay estaciones registradas, si != -1 indica la direccion en el archivo donde inicia la
  lista de estaciones de la linea que se esta leyendo
 --ApuntadorSiguiente, si es -1, No existen mas lineas que leer, si != -1 indica la direccion  que se debe seguir en la lista de
  lineas
 
                                                    TARISTA: (O bien, la estacion)
    
    ApuntadorLineaActual   |   NombreEstacion   |   ArregloDeLineas   |   ApuntadorSig   |   ApuntadorAnterior
 
--ApuntadorLineaActual, es el que le correspinde a ApuntadorAListaEstacion, esto indica si esta conectada a la linea o no
--NombreEstacion, el nombre de la estacion, es una cadena
--ArregloDeLineas, es un arreglo de 5 casilleros que contiene las direcciones de las lineas a las que se conecta la estacion, si
 solo se conecta con 1 este empezara con -1
--ApuntadorSig, indica la estacion que sigue en la linea
--ApuntadorAnterion, indica la estacion que queda atras en la direccion a la que se va
 
 Intentare poner las funciones necesarias para escribir las lineas en caso de que no exista el archivo(no existe jejeje)
 
 */

#include <stdio.h>
#include <string.h>
#include <string.h>
#include <time.h>
#define N 25
// lista interior, contiene las estaciones de la linea
typedef struct{
    char estacion[N];      // nombre de la estacion
    long sig; // estacion siguiente
    long ant; // estacion anterior
}TArista;

typedef struct{
    char Linea[N];            // nombre de la linea
    TArista estacion;       // variable de tipo TArista que contiene la informacion de las estaciones
    long sig;   // linea que sigue para moverse dentro del arreglo
    long ant;   // linea anterior para moverse dentro del arreglo
}TVertice;

//Protos
void presentacion(void);
void abrirArchivo(void);                                                 // abre el archivo "lineas.cid", si no existe lo crea
void inicializaArchivo(void);                                            // inicializa en -1 el archivo
long obtenerCabeza(void);                                                // obtiene la direccion de la cabecera
int insertarLinea(void);                                            // inserta una linea al final del archivo
int compara(TVertice busca, long cab);                              // verifica si ya existe la linea
int insertarEstacion(TVertice linea);                                   // inserta una estacion en una linea
void traslado(TVertice LineaOrigen,TArista Origen, TArista Destino);    // imprime el recorrido si lo hay

//Protos

int main() {
    presentacion();
    
}

//
void presentacion(void){
        char x;
        printf("\n\t\t\t    ESTRUCTURAS DE DATOS II \n \t\t Leonardo Alejandro Gonzalez Lopez \n\t\t Tarea 6: Programa líneas del metro CDMX usando grafos \n \t\t\t\t 17/Mayo/2021 \n\t\t Profesor: Francisco Edgar Castillo Barrera \n\t\t Version 1.0 \n Presione cualquier tecla para continuar :D \n");
        gets(&x);
}

//
void abrirArchivo(void){
    
    time_t start, end;                                          //
    time(&start);
    printf("\n Se verificara la existencia del archivo\n");     // esta parte del codigo solo hace tiempo :P
    do time(&end);
    while(difftime(end, start) <= 3);                           //
    
    FILE *fp;
    fp=fopen("lineas.cid", "r");
    if (fp==NULL) {                                             // revisa que lineas.cid exista
        printf("\n Archivo no encontrado, se creara 'lineas.cid'\n");
        fp = fopen("lineas.cid", "wb+");                        // si no existe creara el archivo
        if (fp==NULL) {
            printf("\n Error al crear archivo\n");
        }else{
            inicializaArchivo();
            printf("\n Archivo creado con exito\n");
        }
    }else{                                                      // si encuentra el archivo envia un mensaje de exito
        printf("\n Se ha encontrado el archivo :D\n");
    }
}

//
long obtenerCabeza(void){                       // obtiene la cabeza del grafo, si es -1 es que el archivo esta vacio
    long cab;                                   // esta funcion solo la usare cuando me mueva por el grafo
    FILE *fp;
    fp=fopen("lineas.cid","rb+");
    fseek(fp,0,SEEK_SET);
    fread(&cab,sizeof(long),1,fp);
    fclose(fp);
    return (cab);
}

//
void inicializaArchivo(void){                   // escribe un bloque de tamaño long con el numero -1
    long cab = -1;
    FILE *fp;
    fp=fopen("lineas.cid", "rb+");
    fseek(fp, 0, SEEK_SET);
    fwrite(&cab, sizeof(long), 1, fp);
    fclose(fp);
}

// 1, se inserto con exito, 0 error al insertar, -1 ya existe
int insertarLinea(void){
    long ap, pos, vertice;
    ap = obtenerCabeza();
    FILE *fp;
    TVertice aux, auxmov;
    
    fp=fopen("lineas.cid", "rb+");  //abre archivo binario para lectura y escritura
    if (fp == NULL) {
        return (0);     // error al escribir
    }
    if (ap == -1) {   // si el archivo esta vacio
        
        long cab = sizeof(long);    // cab es el tamaño de long
        
        fseek(fp, 0, SEEK_SET);
        fwrite(&cab, sizeof(long), 1, fp);  // sobreescribe la cabecera, le da el valor de long que es donde empezaran los datos
        fflush(stdin);
        fpurge(stdin);
        printf("\n Escribe el nombre de la linea: \n");
        gets(&aux.Linea[N]);
        aux.ant=-1;                             // no tiene anterior porque es cabecera
        aux.sig=-1;                             // aun no tiene siguiente porque es el primer vertice
        fwrite(&aux, sizeof(TVertice), 1, fp); // no es necesario moverse porque ya estamos al final del archivo
        fclose(fp);
        return (1);
        
    }else{
        
        fseek(fp, ap, SEEK_SET);
        fread(&aux, sizeof(TVertice), 1, fp);
        printf("\n Escribe el nombre de la linea: \n");
        gets(&aux.Linea[N]);
        fflush(stdin);
        fpurge(stdin);
        if (compara(aux, ap)==1) {                              // la linea ya existe
            
            printf("\n La linea ya existe en los datos\n");
            fclose(fp);
            return (-1);
            
        }else{                                              // el archivo no esta vacio ya contiene informacion
            
            fseek(fp, ap , SEEK_SET);
            pos = ftell(fp);                                // indica la posicion actual, pos = TVertice.ant
            fread(&auxmov, sizeof(TVertice), 1, fp);        // lee el nodo encontrado
            vertice = auxmov.sig;                           // variable para saber a donde se tiene que ir
            while (!feof(fp)) {                             //mientras no sea final del archivo
                if (auxmov.sig == -1) { // si el apuntador a siguiente esta vacio se agrega el vertice
                    
                    aux.sig=-1;             //el apuntador a siguiente del nuevo vertice sera -1
                    aux.ant=pos;            //el apuntador anterior sera la posicion donde se encontraba el indicador
                    fwrite(&aux, sizeof(TVertice), 1, fp);  // se escribe el nuevo vertice
                    pos = ftell(fp);    // se obtiene la posicion actual que sera el siguiente del nodo anterior
                    auxmov.sig=pos;
                    fseek(fp, -1*(aux.ant), SEEK_CUR);      // AQUI HAY DUDA si se usa el -1 para moverse "hacia atras?"
                    fwrite(&auxmov, sizeof(TVertice), 1, fp);   // escribe el valor actualizado de siguiente del vertice anterior al agregado
                    return (1); // sale del bucle con exito
                }
                fseek(fp, vertice, SEEK_CUR); // desde la posicion actual busca el siguiente vertice
                pos = ftell(fp);
                fread(&auxmov, sizeof(TVertice), 1, fp);
                vertice = auxmov.sig;
            }
        }
        
    }
  return (0);
}

// -1 no se pudo abrir, 0 no existe, 1 ya existe
int compara(TVertice busca, long cab){
    FILE *fp;
    TVertice aux;
    
    fp=fopen("lineas.cid", "rb");   // abre archivo binario para lectura
    if (fp == NULL) {
        return (-1);     // error al abrir
    }
    fseek(fp, cab, SEEK_SET);                   // se mueve a la cabecera
    fread(&aux, sizeof(TVertice), 1, fp);       // le el primer vertice
    while (!feof(fp)) {                         // mientras no sea final del archivo
        if (strcmp(busca.Linea, aux.Linea)==0) {    // compara el vertice que se busca con el que se leyo
            fclose(fp);
            return (1);
        }
        fread(&aux, sizeof(TVertice), 1, fp);
    }
    fclose(fp);
    return (0);
}
