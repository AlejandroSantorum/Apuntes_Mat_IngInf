#include <stdio.h>

#define DOLARES_POR_EURO 1.35
#define LIBRAS_POR_EURO 0.874
#define YENES_POR_EURO 102.892

int main ()
{
    int opcion;
    float euros, cambio;

    printf ("Introduce una cantidad en euros: ");
    scanf ("%f", &euros);

    printf("Selecciona una opción:\n1. Dólar\n2. Yen japonés\n3. Libra esterlina\n");
    scanf("%d", &opcion);

    switch(opcion)
    {
        case 1:
            cambio = euros * DOLARES_POR_EURO;
            printf ("%.2f euros son %.2f dolares.\n", euros, cambio);
        break;

        case 2:
            cambio = euros * YENES_POR_EURO;
            printf ("%.2f euros son %.2f yenes.\n", euros, cambio);
        break;

        case 3:
            cambio = euros * LIBRAS_POR_EURO;
            printf ("%.2f euros son %.2f libras.\n", euros, cambio);
        break;

        default:
            printf("La opción introducida es incorrecta");

    }

    return 0;
}