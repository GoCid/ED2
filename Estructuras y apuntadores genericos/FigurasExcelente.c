#include <stdio.h>
#include <stdlib.h>

#define pi 3.1416

typedef struct{
        int tipo;
        void *fig;
        float area;
        }TFiguras;

typedef struct{
        float altri;
        float basetri;
        }TTriangulo;

typedef struct{
        float alturec;
        float baserec;
        }TRectangulo;

typedef struct{
        float radio;
        }TCirculo;

void PideTam (int *tam);
void ReservaMem (TFiguras **dato, int tam);
void PideTFiguras (TFiguras *dato, int tam);
float CalculaAreadeTTriangulos (TFiguras *dato, int tam);
void MuestraDatos (TFiguras *dato, int tam, float atr);
void LiberaMem(TFiguras *arreglo, int tam);
void CalculaAreasFiguras(TFiguras *arreglo, int tam );

void main (void)
{
    TFiguras *arreglo;
    float area;
    int t;

    PideTam (&t);
    ReservaMem (&arreglo, t);
    PideTFiguras (arreglo, t);
    area= CalculaAreadeTTriangulos (arreglo, t);
    MuestraDatos (arreglo, t, area);
    LiberaMem(arreglo, t);
    system ("PAUSE");
    return;
}

void PideTam (int *tam)
{
     printf ("Proporciona el n%c",(char)163);
     printf("mero de figuras: ");
     scanf ("%d", tam);
}

void ReservaMem (TFiguras **dato, int tam)
{
     *dato= (TFiguras*)malloc(sizeof(TFiguras)*tam);
     if(!*dato)
        printf ("Nose pudo reservar memoria");
}

void PideTFiguras (TFiguras *dato, int tam)
{
     int i=0;
     for ( ; i<tam; i++)
     {
         printf ("Que figura es: 1=TTriangulo \n\t2=TCirculo \n\t3=TRectangulo\n :");
         scanf ("%d", &(dato+i)->tipo);
         switch ((dato+i)->tipo)
         {
                case 1:
                       printf (" \n\tTRIANGULO ");
                       (dato+i)->fig = malloc(sizeof(TTriangulo));
                       if ( (*(dato+i)).fig )
                       {
                       printf ("\nDa la base del triangulo: ");
                       scanf("%f", &((TTriangulo*)((dato+i)->fig))->basetri);
                       printf ("Dame la altura del triangulo: ");
                       scanf ("%f", &(*((TTriangulo*)((dato+i)->fig))).altri);
                       }
                       break;
                case 2:
                       printf (" \n\tCIRCULO ");
                       (dato+i)->fig=malloc(sizeof(TCirculo));
                       if ((dato+i)->fig)
                       {
                       printf ("\nDame el radio del circulo : ");
                       scanf ("%f", &((TCirculo*)((dato+i)->fig))->radio);
                       }
                       break;
                case 3:
                       printf (" \n\tRECTANGULO ");
                       (dato+i)->fig=malloc(sizeof(TRectangulo));
                       if ((*dato).fig)
                       {
                       printf ("\nDame la base del rectangulo: ");
                       scanf ("%f", &((TRectangulo*)((dato+i)->fig))->baserec);
                       printf ("Dame la altura del rectangulo: ");
                       scanf ("%f", &((TRectangulo*)((dato+i)->fig))->alturec);
                       }
                       break;
         }
     }
}

float CalculaAreadeTTriangulos (TFiguras *dato, int tam)
{
      float cont=0, area;
      int i = 0;

      for ( ; i<tam; i++)
      {
          if( (dato+i)->tipo == 1 )
          area= (((TTriangulo*)(dato->fig))->altri)*(((TTriangulo*)(dato->fig))->basetri)/2;
          cont += area;
      }
      return area;

}

void MuestraDatos (TFiguras *dato, int tam, float atr)
{
     int i=0;
     for ( ; i<tam; i++)
     {
         switch ((dato+i)->tipo)
         {
                case 1:
                       printf (" \n\n\tTRIANGULO ");
                       printf ("\nBase del triangulo es : %f", ((TTriangulo*)((dato+i)->fig))->basetri);
                       printf ("\nAltura del triangulo es: %f",((TTriangulo*)((dato+i)->fig))->altri );
                       printf ("\n El area de los triangulos es: %f", atr);
                       break;
                case 2:
                       printf (" \n\n\tCIRCULO ");
                       printf ("\nEl radio del circulo es : %f", ((TCirculo*)((dato+i)->fig))->radio);
                       break;
                case 3:
                       printf (" \n\n\tRECTANGULO ");
                       printf ("\nLa base del rectangulo es: %f", ((TRectangulo*)((dato+i)->fig))->baserec);
                       printf ("Dame la altura del rectangulo: %f", ((TRectangulo*)((dato+i)->fig))->alturec);
                       break;

         }
     }
}

void LiberaMem(TFiguras *arreglo, int tam)
{ int i=0;
  for( ; i<tam; i++)
     free( (arreglo+i)->fig );
  free(arreglo);
}

void CalculaAreasFiguras(TFiguras *arreglo, int tam )
{int i=0;

 for( ;i<tam; i++)
 {
     switch( (arreglo+i)->tipo )
     case 1: arreglo[i].area =(((TTriangulo*)(arreglo->fig))->altri)*(((TTriangulo*)(arreglo->fig))->basetri)/2;
     case 2:
     case 3: break;
 }
}









