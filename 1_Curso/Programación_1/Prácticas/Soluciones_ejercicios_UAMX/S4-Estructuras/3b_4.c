#include <stdio.h>

#define DIM 50
#define TEL 12
#define COD 6

#define NUM 2

typedef struct
{
    int dia;
    int mes; 
    int agno; 
} Fecha;

typedef struct 
{
    char calle [DIM];
    int  numero;
    char codigo [COD];
    char localidad [DIM];
} Direccion;

typedef struct 
{
    char      nombre [DIM];
    char      apellido [DIM];
    char      telefono [TEL];
    Direccion direccion;
    Fecha     fecha_nacimiento;
} Contacto;

int main () 
{
    Contacto c[NUM];
    
    printf ("Datos del primer contacto:\n");
    
    printf ("Introduzca su nombre: ");
    scanf ("%s", c[0].nombre);

    printf ("Introduzca su apellido: ");
    scanf ("%s", c[0].apellido);

    printf ("Introduzca su número de teléfono: ");
    scanf ("%s", c[0].telefono);

    printf ("Introduzca el nombre de su calle: ");
    scanf ("%s", c[0].direccion.calle);

    printf ("Introduzca el numero de la calle: ");
    scanf ("%d", &c[0].direccion.numero);

    printf ("Introduzca el código postal de su dirección: ");
    scanf ("%s", c[0].direccion.codigo);

    printf ("Introduzca su localidad: ");
    scanf ("%s", c[0].direccion.localidad);

    printf ("Introduzca el día de su fecha de nacimiento: ");
    scanf ("%d", &c[0].fecha_nacimiento.dia);

    printf ("Introduzca el mes de su fecha de nacimiento: ");
    scanf ("%d", &c[0].fecha_nacimiento.mes);

    printf ("Introduzca el año de su fecha de nacimiento: ");
    scanf ("%d", &c[0].fecha_nacimiento.agno);
    
    printf ("Datos del segundo contacto:\n");
    
    printf ("Introduzca su nombre: ");
    scanf ("%s", c[1].nombre);

    printf ("Introduzca su apellido: ");
    scanf ("%s", c[1].apellido);

    printf ("Introduzca su número de teléfono: ");
    scanf ("%s", c[1].telefono);

    printf ("Introduzca el nombre de su calle: ");
    scanf ("%s", c[1].direccion.calle);

    printf ("Introduzca el numero de la calle: ");
    scanf ("%d", &c[1].direccion.numero);

    printf ("Introduzca el código postal de su dirección: ");
    scanf ("%s", c[1].direccion.codigo);

    printf ("Introduzca su localidad: ");
    scanf ("%s", c[1].direccion.localidad);

    printf ("Introduzca el día de su fecha de nacimiento: ");
    scanf ("%d", &c[1].fecha_nacimiento.dia);

    printf ("Introduzca el mes de su fecha de nacimiento: ");
    scanf ("%d", &c[1].fecha_nacimiento.mes);

    printf ("Introduzca el año de su fecha de nacimiento: ");
    scanf ("%d", &c[1].fecha_nacimiento.agno);

    printf ("\nAgenda:\n");
    printf ("\nNombre:            %s\n", c[0].nombre);
    printf ("Primer apellido:     %s\n", c[0].apellido);
    printf ("Teléfono:            %s\n", c[0].telefono);
    printf ("Calle:               %s\n", c[0].direccion.calle);
    printf ("Numero:              %d\n", c[0].direccion.numero);
    printf ("Código postal:       %s\n", c[0].direccion.codigo);
    printf ("Localidad:           %s\n", c[0].direccion.localidad);
    printf ("Fecha de nacimiento: %2d/%2d/%4d\n", c[0].fecha_nacimiento.dia, c[0].fecha_nacimiento.mes, c[0].fecha_nacimiento.agno);

    printf ("\nNombre:              %s\n", c[1].nombre);
    printf ("Primer apellido:     %s\n", c[1].apellido);
    printf ("Teléfono:            %s\n", c[1].telefono);
    printf ("Calle:               %s\n", c[1].direccion.calle);
    printf ("Numero:              %d\n", c[1].direccion.numero);
    printf ("Código postal:       %s\n", c[1].direccion.codigo);
    printf ("Localidad:           %s\n", c[1].direccion.localidad);
    printf ("Fecha de nacimiento: %2d/%2d/%4d\n", c[1].fecha_nacimiento.dia, c[1].fecha_nacimiento.mes, c[1].fecha_nacimiento.agno);
    
    return 0;
}