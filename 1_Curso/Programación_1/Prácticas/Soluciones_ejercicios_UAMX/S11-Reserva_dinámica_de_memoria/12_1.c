#include <stdio.h>
#include <stdlib.h>
 
int main()
{
    int tamano, *tabla, i;
    double media;
    
    printf("Introduce cuantos enteros se van a leer: ");
    scanf("%d", &tamano);
    
    tabla = (int *) malloc (tamano * sizeof(int)); /* Se intenta reservar memoria */
    if (tabla == NULL) /* Si no se ha podido reservar */
    {
        printf("Error. No se ha podido reservar memoria.");
        return 1; /* El programa no puede continuar. Se termina devolviendo 1 para indicar que el programa acaba con error, sin realizar las tareas que tenía previstas */
    }
    
    /* Una vez reservada memoria, se trabaja con tabla exactamente igual que si fuera una tabla estática */
    /* Fíjate que es importante empezar inicializando media a cero */
    for (i=0, media=0; i<tamano; i++)
    {
        printf("Introduce el numero %d: ", i+1);
        scanf("%d", &tabla[i]);
        media+=tabla[i];
    }
   
    media /= i;
    printf("La media de los numeros leidos es: %lf", media);
    
    free(tabla); /* Antes de terminar, siempre hay que liberar la memoria que se haya reservado */
  
    return 0; /* Se termina devolviendo 0 cuando el programa ha realizado todas las acciones correctamente */

}