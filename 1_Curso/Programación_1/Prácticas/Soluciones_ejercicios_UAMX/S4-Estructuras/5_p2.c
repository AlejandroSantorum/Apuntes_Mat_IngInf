
#include <stdio.h>

#define NUM 2
#define CAD 20

typedef struct
{
    int dia;
    int mes;
    int agno;
}Fecha;

typedef struct
{
    char nombre[CAD];
    Fecha fecha[NUM];
}Citas;

int main() 
{
    Citas citas;

    printf("Introduce tu nombre: ");
    scanf("%s", citas.nombre);
    printf ("\nIntroduce un día: ");
    scanf ("%d", &citas.fecha[0].dia);
    printf ("Introduce un mes: ");
    scanf ("%d", &citas.fecha[0].mes);
    printf ("Introduce un año: ");
    scanf ("%d", &citas.fecha[0].agno);
    printf ("\nIntroduce otro día: ");
    scanf ("%d", &citas.fecha[1].dia);
    printf ("Introduce otro mes: ");
    scanf ("%d", &citas.fecha[1].mes);
    printf ("Introduce otro año: ");
    scanf ("%d", &citas.fecha[1].agno);

    printf("\nHola %s\n", citas.nombre);
    printf("Tienes una cita el %d/%d/%d y otra el %d/%d/%d\n", citas.fecha[0].dia, citas.fecha[0].mes, citas.fecha[0].agno, citas.fecha[1].dia, citas.fecha[1].mes, citas.fecha[1].agno);

    return 0;
}