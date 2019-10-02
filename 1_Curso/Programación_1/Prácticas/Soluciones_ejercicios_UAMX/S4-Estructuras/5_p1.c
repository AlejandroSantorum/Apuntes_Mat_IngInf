
#include <stdio.h>

#define CAD 30
#define TAM 2

typedef struct
{
    char nombre[CAD];
    int edad;
}Persona;

typedef struct
{
    Persona persona[TAM];
    double media;
}Gente;

int main() 
{
    Gente gente;

    printf("Introduce un nombre: ");
    scanf("%s", gente.persona[0].nombre);
    printf ("Introduce una edad: ");
    scanf ("%d", &gente.persona[0].edad);

    printf("\nIntroduce otro nombre: ");
    scanf("%s", gente.persona[1].nombre);
    printf ("Introduce otra edad: ");
    scanf ("%d", &gente.persona[1].edad);

    gente.media = (gente.persona[0].edad + gente.persona[1].edad) / 2.0;

    printf("\n%s tiene %d años y %s tiene %d años.\n", gente.persona[0].nombre, gente.persona[0].edad, gente.persona[1].nombre, gente.persona[1].edad);
    printf("La media de sus edades es de %.1lf años.", gente.media);

    return 0;
}