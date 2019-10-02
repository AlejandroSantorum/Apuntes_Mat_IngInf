#include <stdio.h>

#define AS 1
#define DOS 2
#define TRES 3
#define CUATRO 4
#define CINCO 5
#define SEIS 6
#define SIETE 7
#define SOTA 0.5
#define CABALLO 0.5
#define REY 0.5

void main(){
    double puntos=0, cartas[40] = {AS, DOS, TRES, CUATRO, CINCO, SEIS, SIETE, SOTA, CABALLO, REY, AS, DOS, TRES, CUATRO, CINCO, SEIS, SIETE, SOTA, CABALLO, REY, AS, DOS, TRES, CUATRO, CINCO, SEIS, SIETE, SOTA, CABALLO, REY, AS, DOS, TRES, CUATRO, CINCO, SEIS, SIETE, SOTA, CABALLO, REY};
    
    int opcion, c=0, NumeroJugadores, i=0;
    
    printf("Introduzca el numero de jugadores: ");
    scanf("%d", &NumeroJugadores);
    
    while (i<NumeroJugadores){
        
        while ( puntos < 7.5 ) {
            printf("Quieres carta (s/n)? ");
            scanf("%c", &opcion);
            
            if ( opcion == 's' || opcion == 'S' ) {
                puntos = puntos + cartas[c];
                c++;
                continue;
            }
            else {
            printf("Te has plantado!\n");
            break;
            }
        printf("Tienes %f puntos!\n", puntos);
        i++;
        continue;
        }
    }
}