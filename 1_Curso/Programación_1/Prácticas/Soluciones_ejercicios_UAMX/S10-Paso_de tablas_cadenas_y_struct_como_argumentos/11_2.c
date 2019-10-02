#include <stdio.h>
#include <string.h>
 
#define TAM 30
 
int deMinusculasAMayusculas(char * cadena)
{
    int i;

    for (i=0; i<strlen(cadena); i++)
        cadena[i]-='a'-'A'; // Hay que restar la diferencia que han entre el código ascii de las minúsuclas y las mayúsculas

    return strlen(cadena);
}
 
/* Alternativamente, si quisiéramos trabajar exclusivamente con punteros y no utilizar la función strlen
 
int deMinusculasAMayusculas(char * cadena)
{
    int tamano;

    for (tamano=0; *cadena!=0; cadena++, tamano++)
        *cadena-='a'-'A'; // Hay que restar la diferencia que han entre el código ascii de las minúsuclas y las mayúsculas

    return tamano;
}
*/
 
int main()
{
    char cad[TAM];
    int tam;

    printf("Introduce una cadena de caracteres en minúsuclas: ");
    scanf("%s", cad);

    tam=deMinusculasAMayusculas(cad);

    printf("La cadena en mayúsculas es %s y su tamaño %d.", cad, tam);
    
    /* Una alternativa para no tener que utilizar la variable tam sería: 
       printf("La cadena en mayúsculas es %s y su tamaño %d.", cad, deMinusculasAMayusculas(cad)); 
       eliminando la instrucción con la llamada a la función anterior y poniéndola dictamente dentro del pritnf */

    return 0;
}
