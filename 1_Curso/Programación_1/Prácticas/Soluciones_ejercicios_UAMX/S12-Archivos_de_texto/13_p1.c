#include <stdio.h>

#define DIM 80

int guardarVecesInicial(char * nombreFichero, char inicial) 
{
    FILE * f;
    char nombre[DIM];
    int segundo, tercero, veces=0;

    f = fopen(nombreFichero, "r");
    if (f == NULL)
        return 1;

    while (fscanf(f, "%s %d %d", nombre, &segundo, &tercero) == 3)
        if (nombre[0] == inicial)
            veces++;

    fclose(f);

    f = fopen(nombreFichero, "a");
    if (f == NULL)
        return 1;

    fprintf(f, "\nHay: %d nombres que empiezan por la inicial %c", veces, inicial);

    fclose(f);

    return 0;
}

int main() 
{
    char inicial, nombre [DIM];

    printf("Teclea el nombre del archivo: ");
    scanf("%s", nombre);

    printf("Teclea na inicial: ");
    scanf("\n%c", &inicial);

    if (guardarVecesInicial(nombre, inicial) == 1) 
    {
        printf("Error: no se pudo abrir el fichero %s.", nombre);
        return 1;
    }

    printf("El resultado se ha guardado correctamente al final del fichero %s\n", nombre);

    return 0;
}