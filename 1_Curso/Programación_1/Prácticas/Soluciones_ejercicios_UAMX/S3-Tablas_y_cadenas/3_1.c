#include <stdio.h>

#define DOLARES_POR_EURO 1.35
#define LIBRAS_POR_EURO 0.874
#define YENES_POR_EURO 102.892

int main ()
{
    double euros;
    double cambio;

    printf ("Introduzca cantidad en euros: ");
    scanf ("%lf", &euros);
    
    cambio = euros * DOLARES_POR_EURO;
    printf ("%.2f euros son %.2f dolares.\n", euros, cambio);
    
    cambio = euros * LIBRAS_POR_EURO;
    printf ("%.2f euros son %.2f libras.\n", euros, cambio);
    
    cambio = euros * YENES_POR_EURO;
    printf ("%.2f euros son %.2f yenes.\n", euros, cambio);

    return 0;
}