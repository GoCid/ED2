#include<stdio.h>
#include<stdlib.h>

typedef struct
{
 char nombre[25];
 char direccion[25];
 char telefono[25];
 int  tipo;
 void *Empleado;
}TEMPLEADO;

typedef struct
{
 float pagoEfectivo;
 float pagoElectronico;
}TFIJO;

typedef struct
{
 int horas;
 float sueldoHora;
}THORA;

int pideTam();

void asignaMem(TEMPLEADO **e, int tam);
void pideDatosFijo(void *pE);
void pideDatosHora(void *h);
void llenaArr(TEMPLEADO  *e, int tama);
void muestraDatosEmpleados(TEMPLEADO *e, int num);
float nomina(TEMPLEADO *e,int n);

int main()
{
 TEMPLEADO *e=NULL;
 int N, tipoE;
 float NominaE;

 N=pideTam();
 asignaMem(&e, N);
 llenaArr(e, N);
 muestraDatosEmpleados(e, N);
 NominaE=nomina(e, N);
 //printf("hola");
 system("pause");
}

int pideTam()
{
 int n;
 printf("Dame tamaño: ");
 scanf("%d", &n);
 return n;
}

void asignaMem(TEMPLEADO **e, int tam)
{
 int i;
 *e=(TEMPLEADO *)malloc(sizeof(TEMPLEADO)*tam);
    printf("memoria asignada a estructura TEMPLEADO\n");
    if(*e==NULL)
     {
     printf("error\n");
     system("pause");
     }
}
 /*
  for(i=0;i<tam;i++)
  {
    printf("Selecciona 1 si el empleado tiene sueldo fijo\n");
    printf("Selecciona 2 si el empleado tiene sueldo fijo\n");
    scanf("%d", & e[i]->tipo);

  tipoEmp=e[i]->tipo;
  switch(tipoEmp)
   {
    case 1: //e[i]->Empleado=(TFIJO*)malloc(sizeof(TFIJO));
            (*(e+i))->Empleado=malloc(sizeof(TFIJO));
            printf("memoria asignada a estructura TFIJO");
            break;
    case 2: //e[i]->Empleado=(THORA*)malloc(sizeof(THORA));
            (*(e+i))->Empleado=malloc(sizeof(THORA));
            printf("memoria asignada a estructura TFIJO");
            break;
   }
 }
}*/

void llenaArr(TEMPLEADO *e, int tama)
{ int i=0;

  for( ;i<tama;i++)
  {
   printf("Nombre del empleado: \n");
   // scanf("%s",&(*(e+i)).nombre);
   gets( (*(e+i)).nombre ) ;
   printf("Direccion del empleado: \n");
   scanf("%s",&(e+i)->direccion);
   printf("Telefono del empleado: \n");
   scanf("%s",& (*(e+i)).telefono);
   printf("Tipo de informacion del empleado 1=TFIJO 2=THORA \n");
   scanf("%d",&e[i].tipo);

      switch((e+i)->tipo)
      { case 1:
               (e+i)->Empleado=malloc(sizeof(TFIJO));
               if( (e+i)->Empleado )
               { printf("Dar el pago efectivo");
                 scanf("%f", &((TFIJO *)(e+i)->Empleado)->pagoEfectivo );
                 printf("Dar el pago efectivo");
                 scanf("%f", &((TFIJO *)(e+i)->Empleado)->pagoElectronico);
               }
               break;

        case 2:(*(e+i)).Empleado=malloc(sizeof(THORA));
               if( (e+i)->Empleado )
               { printf("Dar el pago efectivo");
                 scanf("%i", &((THORA *)(e+i)->Empleado)->horas );
                 printf("Dar el pago efectivo");
                 scanf("%f", &((THORA *)(e+i)->Empleado)->sueldoHora);
               }

               break;
      }
  }
}
void pideDatosFijo(void *pE)
{
 TFIJO *fijoEf =(TFIJO *)pE;
  float pElec;
  printf("cual es el pago en efectivo= ");
  scanf("%f",&(*fijoEf).pagoEfectivo);
  printf("cual es el pago electronico");
  scanf("%f",&pElec);
  fijoEf->pagoElectronico=pElec;
}

void pideDatosHora(void *h)
{
  THORA *horaH =(THORA *)h;
  float sH;
  printf("cuantas horas= ");
  scanf("%d",&(*horaH).horas);
  printf("sueldo por hora= ");
  scanf("%f",&sH);
  horaH->sueldoHora=sH;
}

void muestraDatosEmpleados(TEMPLEADO *e, int num)
{
 int i;
 for(i=0;i<num;i++)
 {
      printf("El nombre de el empleado es: %s\n",(*(e+i)).nombre);
      printf("La direccion del empleado es: %s\n",e[i].direccion);
      printf("El telefono del empleado es: %s\n",e[i].telefono);
      if((e+i)->tipo==1)
      {
      printf("Pago en efectivo es: %f\n",((TFIJO*)(e+i)->Empleado)->pagoEfectivo);
      printf("Pago en electronico es: %f\n",((TFIJO*)(e+i)->Empleado)->pagoElectronico);
      }
      else
       if((e+i)->tipo==2)
        {
         printf("Horas es: %d\n",((THORA*)(e+i)->Empleado)->horas);
         printf("Sueldo por hora es: %f\n",((THORA*)(e+i)->Empleado)->sueldoHora);
        }
 }
}

float nomina(TEMPLEADO *e,int n)
{
 float sumaT=0, sumaF=0, multiSum=0;
 int i;
 for(i=0;i<n;i++)
 {
    if((e+i)->tipo==1)
      {
      sumaF= (((TFIJO*)(e+i)->Empleado)->pagoEfectivo)+(((TFIJO*)(e+i)->Empleado)->pagoElectronico);
     // printf("La suma1 es= %f", sumaF);
      }

    else
      if((e+i)->tipo==2)
      {
        multiSum= (((THORA*)(e+i)->Empleado)->horas)*(((THORA*)(e+i)->Empleado)->sueldoHora);
        //printf("La suma2 es= %f", multiSum);
      }
      sumaT+=sumaF+multiSum;
      sumaF=0;
      multiSum=0;
  }
 printf("La respuesta es= %f", sumaT);
 return(sumaT);
}



