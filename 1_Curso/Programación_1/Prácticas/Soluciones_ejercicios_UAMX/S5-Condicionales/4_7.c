/* Una posible solución sería: */

#include <stdio.h>

typedef struct
{
    int  dia;   
    int  mes;   
    int  anyo;  
} Fecha;

int main() 
{
    Fecha fecha1, fecha2;

    printf("Introduce un día, mes y año separados por espacios:\n");
    scanf("%d %d %d", &fecha1.dia, &fecha1.mes, &fecha1.anyo);

    printf("Introduce otro día, mes y año separados por espacios:\n");
    scanf("%d %d %d", &fecha2.dia, &fecha2.mes, &fecha2.anyo);

    if (fecha1.anyo == fecha2.anyo)
    {
        if (fecha1.mes == fecha2.mes)
        {
            if (fecha1.dia == fecha2.dia)
                printf("Las dos fechas son iguales");
            else if (fecha1.dia < fecha2.dia)
                printf("La fecha %d/%d/%d es anterior a %d/%d/%d", fecha1.dia, fecha1.mes, fecha1.anyo, fecha2.dia, fecha2.mes, fecha2.anyo);
            else
                printf("La fecha %d/%d/%d es anterior a %d/%d/%d", fecha2.dia, fecha2.mes, fecha2.anyo, fecha1.dia, fecha1.mes, fecha1.anyo);
        }
        else if (fecha1.mes < fecha2.mes)
            printf("La fecha %d/%d/%d es anterior a %d/%d/%d", fecha1.dia, fecha1.mes, fecha1.anyo, fecha2.dia, fecha2.mes, fecha2.anyo);
        else
            printf("La fecha %d/%d/%d es anterior a %d/%d/%d", fecha2.dia, fecha2.mes, fecha2.anyo, fecha1.dia, fecha1.mes, fecha1.anyo);
    }
    else if (fecha1.anyo < fecha2.anyo)
        printf("La fecha %d/%d/%d es anterior a %d/%d/%d", fecha1.dia, fecha1.mes, fecha1.anyo, fecha2.dia, fecha2.mes, fecha2.anyo);
    else
        printf("La fecha %d/%d/%d es anterior a %d/%d/%d", fecha2.dia, fecha2.mes, fecha2.anyo, fecha1.dia, fecha1.mes, fecha1.anyo);

    return 0;
}

/* Una posible solución alternativa sería: 

#include <stdio.h>

typedef struct
{
    int  dia;   
    int  mes;   
    int  anyo;  
} Fecha;

int main() 
{

    Fecha fecha1, fecha2;

    printf("Introduce un día, mes y año separados por espacios:\n");
    scanf("%d %d %d", &fecha1.dia, &fecha1.mes, &fecha1.anyo);

    printf("Introduce otro día, mes y año separados por espacios:\n");
    scanf("%d %d %d", &fecha2.dia, &fecha2.mes, &fecha2.anyo);

     if (fecha1.anyo < fecha2.anyo)
        printf("La fecha %d/%d/%d es anterior a %d/%d/%d", fecha1.dia, fecha1.mes, fecha1.anyo, fecha2.dia, fecha2.mes, fecha2.anyo);
    else if (fecha1.anyo > fecha2.anyo)
        printf("La fecha %d/%d/%d es anterior a %d/%d/%d", fecha2.dia, fecha2.mes, fecha2.anyo, fecha1.dia, fecha1.mes, fecha1.anyo);
    else
    {
        if (fecha1.mes < fecha2.mes)
            printf("La fecha %d/%d/%d es anterior a %d/%d/%d", fecha1.dia, fecha1.mes, fecha1.anyo, fecha2.dia, fecha2.mes, fecha2.anyo);
        else if (fecha1.mes > fecha2.mes)
            printf("La fecha %d/%d/%d es anterior a %d/%d/%d", fecha2.dia, fecha2.mes, fecha2.anyo, fecha1.dia, fecha1.mes, fecha1.anyo);
        else
        {
            if (fecha1.dia < fecha2.dia)
                printf("La fecha %d/%d/%d es anterior a %d/%d/%d", fecha1.dia, fecha1.mes, fecha1.anyo, fecha2.dia, fecha2.mes, fecha2.anyo);
            else if (fecha1.dia > fecha2.dia)
                printf("La fecha %d/%d/%d es anterior a %d/%d/%d", fecha2.dia, fecha2.mes, fecha2.anyo, fecha1.dia, fecha1.mes, fecha1.anyo);
            else
                printf("Las dos fechas son iguales");
        }
    }

    return 0;
}

*/ 