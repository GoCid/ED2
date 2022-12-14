#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <winbgim.h>

using namespace std;

typedef struct
{
    char Nom[20];
    char Movie[50];
}TDato;

typedef struct Nodo
{
    struct Nodo *sig;
    TDato pers;
}TNodo;

typedef struct
{
    TNodo *ini,*fin;
    int c, c2;
    int tam;
}TCola;

void Presentacion();
void ColocaB(TCola c);
void CajaDis(int *c);
void IniCola(TCola *c);
void PonMenu();
void Opcion(int *O,TCola c);
void ODato(TDato *info);
int PushLS(TCola *c,TDato info);
int Pregunta();
int PopLS(TCola *c);
int PopLSO(TCola *c,TDato info);
void MuestraCola(TCola c);
void LiberaL(TCola *c);
void Cajas(int b);
void personas(int b);
void AvanzaC(int cj,TCola c);
void Nombres(char n[20]);
void Peliculas(char n[50]);

int main()
{
    TCola cola;
    TDato inf;
    int Op,cj,x;

    initwindow(800,600);
    srand(time(0));

    Presentacion();
    IniCola(&cola);
    do
    {
        ColocaB(cola);
        Cajas(cola.tam-cola.c);
        PonMenu();
        Opcion(&Op,cola);
        system("cls");
        switch(Op)
        {
            case 1:
                if(cola.c <cola.tam)
                {
                    ODato(&inf);
                    x=PushLS(&cola,inf);
                    delay(1000);
                    personas(cola.c2);
                    if(x==1) printf("Persona Agregada a la fila.\n");
                    if(x==0) printf("Persona no agregada a la fila.\n";
                } else {printf("Ya no hay boletos.\n";}
                break;
            case 2:
                if(cola.c>0)
                {
                    x=Pregunta();
                    if(x==1)
                    {
                        CajaDis(&cj);
                        x=PopLS(&cola);
                        cleardevice();
                        Cajas(cola.tam-cola.c);
                        personas(cola.c2);
                        AvanzaC(cj,cola);
                        if(x==1) {printf("\nPersona fuera de la fila.\n"; ColocaB(cola);}
                        if(x==0) printf("\nLa persona no quiso pasar a la caja.\n";
                        personas(cola.c2);
                    } else
                    {
                        ODato(&inf);
                        delay(500);
                        x=PopLSO(&cola,inf);
                        cleardevice();
                        Cajas(cola.tam-cola.c);
                        personas(cola.c2);
                        if(x==1){ printf("\nPersona fuera de la fila.\n";cola.c--;}
                        if(x==0) printf("\nLa persona no se quiso ir de la fila o ya no se encontraba en la fila.\n";
                    }
                } else {printf("No hay personas que correr.\n";}
                break;
            case 3:
                if(cola.ini)
                {
                    MuestraCola(cola);
                    delay(10000);
                } else {printf("NO hay personas formadas.\n";}
                break;
            case 4:
                if(cola.c>0)
                {
                    IniCola(&cola);
                    LiberaL(&cola);
                    delay(3000);
                    cleardevice();
                    Cajas(cola.tam-cola.c);
                    personas(cola.c);
                    printf("Las personas se han ido de la fila.\n"; delay(300);
                } else {printf("NO hay personas que correr.\n\n";}
                break;
            case 5:
                if(cola.c>0)
                {
                    LiberaL(&cola);
                    Cajas(cola.tam-cola.c);
                    personas(cola.c);
                }
                delay(300);
                printf("Se agotaron los boletos.\nAhora la gente debe irse y el cine cerrar.\n";
                printf("Gracias por usar!!\n";
                printf("Vuelve pronto!!\n";
                break;
        }
    }while(Op!=5);
}

void Presentacion()
{
    printf("Este programa se encarga de simular la venta de boletos en un cine. Para esto utilizamos una estructura de datos llamada: 'Colas', las cuales son del tipo FIFO (First In, First Out), as"((char)161(" que la primera 'persona' que entra, es la primera en salir.\n ";
    printf("Muestra un men"((char)163(" de opciones, sin embargo, el usuario no puede seleccionar ninguna de esas opciones. S"((char)162("lo est"((char)160("n para que el usuario sepa lo que est"((char)160(" haciendo el programa. Adem"((char)160("s, de manera gr"((char)160("fica se muestra 'la llegada de las personas al cine'.\n\n";
    printf("Creado por: Arregu"((char)161("n Bustos Jos"((char)130(" Emmanuel\n\n";
    system("pause");
    system("cls");
}

//Imprime en pantalla la cantidad de boletos existentes.
void ColocaB(TCola c)
{
    printf("La cantidad de boletos es: "(c.tam-(c.c)(endl;
}
//Imprime el numero de caja disponible.
void CajaDis(int *c)
{
    *c=(rand()%5)+1;
    printf("Pase a la caja disponible.\n Caja #"(*c(endl(endl;
}

int Pregunta()
{
    int a=0;

    printf("La persona sale de la fila o pasa a la caja?\n 0)Sale de la fila.       1)Pasa a caja.\n";
    a=rand()%2;
    delay(500);
    printf("Opcion:   "(a(endl(endl;
    delay(500);
    return (a);
}

//Inicia la cola
void IniCola(TCola *c)
{
    c->c=c->c2=0;
    c->tam=(rand()%50)+10;
    c->ini=c->fin=NULL;
}

void PonMenu(void)
{
    printf("\nMenu\n";
    printf("1) Push - Insertar a la Fila\n2) Pop - Eliminar a la Fila\n3) Muestra Fila";
    printf("\n4) Vacia Fila\n5) Salir\n\n";
}

void Opcion(int *O,TCola c)
{
    if(c.c <= (c.tam/2))
    {
        *O=(rand()%3)+1;
        delay(300);
        printf("Opcion:  "(*O(endl;
        delay(1000);
    } else{ *O=(rand()%5)+1;delay(300);printf("Opcion:    "(*O(endl;delay(1000);}
}

void ODato(TDato *info)
{
    Nombres(info->Nom);
    printf("NOMBRE:  "(info->Nom(endl;
    delay(500);
    Peliculas(info->Movie);
    printf("PELICULA:  "(info->Movie(endl;
    delay(500);
}

TNodo * creaNodo(TDato d)
{
    TNodo *nuevo;
    nuevo=(TNodo *)malloc(sizeof(TNodo));
    strcpy(nuevo->pers.Nom,d.Nom);
    strcpy(nuevo->pers.Movie,d.Movie);
    nuevo->sig=NULL;
    return (nuevo);
}

int PushLS(TCola *c,TDato info)
{
    TNodo *nuevo;
    int band=0;

    nuevo=creaNodo(info);
    if(nuevo)
    {
        if(c->ini==NULL)
        {
            c->ini=c->fin=nuevo;
            c->c=c->c+1;
            c->c2=c->c2+1;
        } else
        {
            c->fin->sig=nuevo;
            c->fin=nuevo;
            nuevo->sig=NULL;
            c->c2=c->c2+1;
            c->c=c->c+1;
        }
        band++;
    }
    return (band);
}

int PopLS(TCola *c)
{
    TNodo *aux=c->ini;
    int band=0;

    aux=c->ini;
    if(c->ini)
    {
        band++;
        c->ini=aux->sig;
        c->c2=c->c2-1;
        free(aux);
    }
    return (band);
}

int PopLSO(TCola *c,TDato info)
{
    TNodo *aux1,*aux2;
    int ret=0;

    if(c->ini)
    {
        for(aux1=c->ini;aux1 && strcmp(aux1->pers.Nom,info.Nom)!= 0;aux2=aux1,aux1=aux1->sig);
        if(aux1)
        {
            if(aux1==c->ini)
            {
                c->ini=aux1->sig;
                free(aux1);
                c->c2=c->c2-1;
            } else
            {
                aux2->sig=aux1->sig;
                free(aux1);
                c->c2=c->c2-1;
            }
            ret++;

        }
    }
    return (ret);
}

void MuestraCola(TCola c)
{
    TNodo *aux;
    int i=1;

    aux=c.ini;
    while(aux)
    {
        printf("Persoma %d\n",i);
        printf("NOMBRE:  "(aux->pers.Nom(endl;
        printf("PELICULA:  "(aux->pers.Movie(endl;
        aux=aux->sig;
        i++;
    }
}

void LiberaL(TCola *c)
{
    TNodo *aux;

    while(c->ini)
    {
        aux=c->ini->sig;
        c->ini=NULL;
        c->ini=aux;
    }

}

void Cajas(int b)
{
    int i;
    char a[2],c[2];

    settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
    for(i=0;i<5;i++)
    {
        sprintf(c,"%d",i+1);
        outtextxy(10+120*(i),15,"Caja ");
        outtextxy(90+120*(i),15,c);
        rectangle(5+i*120,5,(i+1)*100+20*(i+1),40);
    }
    sprintf(a,"%d",b);
    rectangle(610,5,780,40);
    outtextxy(615,15,"Boletos: ");
    outtextxy(740,15,a);
    rectangle(610,50,780,90);
    outtextxy(615,60,"Caja Dis: ");
    rectangle(610,100,700,150);
    outtextxy(615,110,"TIME:");
    for(i=0;i<30;i++)
    {
        settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
        outtextxy(230,(i*20)+100,"|");
        outtextxy(270,(i*20)+100,"|");
    }
}

void personas(int b)
{
    int i;

    for(i=0;i<b;i++)
    {
        settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
        outtextxy(250,(i*20)+100,"X");
    }
}

void AvanzaC(int cj,TCola c)
{
    int i=1,a;
    char b[2],t[2];
    Cajas(c.tam-c.c);
    sprintf(b,"%d",cj);
    outtextxy(760,60,b);
    personas(c.c2);
    outtextxy(50+120*(cj-1),50,"X");
    a=(rand()%10)+1;
    while(i<(a*10))
    {

        sprintf(t,"%d",i);
        outtextxy(640,130,t);
        delay(500);
        i++;
    }
    cleardevice();

}

void Nombres(char n[20])
{
    int x;
    x=rand()%10;
    switch(x)
    {
        case 0:
            strcpy(n,"Juan ");
            break;
        case 1:
            strcpy(n,"Andres ");
            break;
        case 2:
            strcpy(n,"Felipe ");
            break;
        case 3:
            strcpy(n,"Josafat ");
            break;
        case 4:
            strcpy(n,"Luis ");
            break;
        case 5:
            strcpy(n,"Jesus ");
            break;
        case 6:
            strcpy(n,"Daniel ");
            break;
        case 7:
            strcpy(n,"Isaac ");
            break;
        case 8:
            strcpy(n,"Jose ");
            break;
        case 9:
            strcpy(n,"Emmanuel ");
            break;
        }
}

void Peliculas(char n[50])
{
    int x;
    x=rand()%10;
    switch(x)
    {
        case 0:
            strcpy(n,"Sing, Ven y Canta!");
            break;
        case 1:
            strcpy(n,"Shazam!");
            break;
        case 2:
            strcpy(n,"Fragmentado!");
            break;
        case 3:
            strcpy(n,"El conjuro.");
            break;
        case 4:
            strcpy(n,"No manches Frida!");
            break;
        case 5:
            strcpy(n,"IT 2- Todos Flotan!!");
            break;
        case 6:
            strcpy(n,"Star Wars Episodio VII");
            break;
        case 7:
            strcpy(n,"Annabel");
            break;
        case 8:
            strcpy(n,"Historias de terror para contar en la oscuridad.");
            break;
        case 9:
            strcpy(n,"Como entrenar a tu Dragon");
            break;
        }
}
