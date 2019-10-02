/* NOTA: Este programa admite otras posibles soluciones */

#include <stdio.h>

typedef struct
{

    int dia;
    int mes;
    int agno;
} Fecha;

int main () 
{
    Fecha uno, dos;

    printf("Introduce la fecha de nacimiento del primer usuario separada por espacios: ");
    scanf("%d %d %d", &uno.dia, &uno.mes, &uno.agno);
    printf("Introduce la fecha de nacimiento del segundo usuario separada por espacios: ");
    scanf("%d %d %d", &dos.dia, &dos.mes, &dos.agno);

    if ( (uno.dia==dos.dia) && (uno.mes==dos.mes) && (uno.agno==dos.agno) )
        printf("¡Felicidades! Ambos habéis nacido el mismo día.");
    else if ( (uno.dia==dos.dia) && (uno.mes==dos.mes) )
        printf("Ambos cumplís años el mismo día. Os lleváis %d años de diferencia.", uno.agno-dos.agno);
    else
        printf("Vaya, no compartís cumpleaños.");

    return 0;
}