#include <stdio.h>
 
typedef struct
{
    int dia;
    int mes;
    int anyo;
}Fecha;
 
void incrementaDia(Fecha * f)
{
    f->dia++; // Recuerda que esta instrucción es equivalente a (*f).dia++;

    if (f->dia > 30)
    {
        f->dia=1;
        f->mes++;
        if (f->mes>12)
        {
            f->mes=1;
            f->anyo++;
        }
    }
}
 
int main()
{
    Fecha fecha;

    printf("Introduce un dia: ");
    scanf("%d", &fecha.dia);
    printf("Introduce un mes: ");
    scanf("%d", &fecha.mes);
    printf("Introduce un año: ");
    scanf("%d", &fecha.anyo);

    incrementaDia(&fecha);

    printf("El día siguiente al introducido es: %d/%d/%d", fecha.dia, fecha.mes, fecha.anyo);
 
    return 0;
}
