#include <stdio.h>

#define DOLARES_POR_EURO 1.35
#define LIBRAS_POR_EURO 0.874
#define YENES_POR_EURO 102.892

int main ()
{
    char opcion;
    float euros, cambio;

    printf ("Introduce una cantidad en euros: ");
    scanf ("%f", &euros);

    printf("Selecciona una opción:\n(D)ólar\n(Y)en japonés\n(L)ibra esterlina\n");
    scanf("\n%c", &opcion);

    switch(opcion)
    {
        case 'D':
        case 'd':
            cambio = euros * DOLARES_POR_EURO;
            printf ("%.2f euros son %.2f dolares.\n", euros, cambio);
        break;

        case 'Y':
        case 'y':
            cambio = euros * YENES_POR_EURO;
            printf ("%.2f euros son %.2f yenes.\n", euros, cambio);
        break;

        case 'L':
        case 'l':
            cambio = euros * LIBRAS_POR_EURO;
            printf ("%.2f euros son %.2f libras.\n", euros, cambio);
        break;
        
        default:
            printf("La opción introducida es incorrecta");
    }

    return 0;
}