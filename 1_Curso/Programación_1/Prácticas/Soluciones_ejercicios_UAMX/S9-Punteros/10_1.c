#include <stdio.h>
 
int main ()
{
    int uno, dos;
    int * p, * q;
    double media;
    double * m;

    p = &uno; /* p apunta a la variable uno */
    q = &dos; /* q apunta a la variable dos */
    m = &media; /* m apunta a media */
 
    printf ("Primero: ");
    scanf ("%d", p); /* p es &uno */
 
    printf ("Segundo: ");
    scanf ("%d", q); /* q es &dos */
 
    *m = (*p + *q) / 2.0;

    /* Aunque el enunciado no pedía estos valores, los siguientes cuatro printf */
    /* muestran los valores de los punteros y las variables, para que entiendas */
    /* mejor cómo se manejan los punteros                                       */ 
    printf ("p = &uno = %p\n", p); /* El valor de p es la dirección de la variable uno */
    printf ("q = &dos = %p\n", q);
    printf ("*p = uno = %d\n", *p); /* El contenido de p es el valor de la variable uno */
    printf ("*q = dos = %d\n", *q);

    /* Este es el resultado solicitado */
    printf ("media = %g\n", *m);
 
    return 0;
}