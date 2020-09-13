/*****************************************************************/
/* Programa: ejercicio1     Fecha: 22/09/2017                    */
/* Autores: Alejandro Santorum Varela y David Cabornero          */
/*                                                               */
/* Programa que genera numeros aleatorios                        */
/* entre dos numeros dados                                       */
/*                                                               */
/* Entrada: Linea de comandos                                    */
/* -limInf: limite inferior                                      */
/* -limSup: limite superior                                      */
/* -numN: cantidad de numeros                                    */
/* Salida: 0: OK, -1: ERR                                        */
/*****************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "permutaciones.h"


int main(int argc, char** argv)
{
  int i,k, aux;
  unsigned int inf, sup, num, j;
  int* histograma;
  FILE *out=NULL;

  srand(time(NULL));

  if (argc != 7) {
    fprintf(stderr, "Error en los parametros de entrada:\n\n");
    fprintf(stderr, "%s -limInf <int> -limSup <int> -numN <int>\n", argv[0]);
    fprintf(stderr, "Donde:\n");
    fprintf(stderr, " -limInf : Limite inferior.\n");
    fprintf(stderr, " -limSup : Limite superior.\n");
    fprintf(stderr, " -numN : Cantidad de numeros a generar.\n");
    exit(-1);
  }
  printf("Practica numero 1, apartado 1.b (HISTOGRAMA)\n");
  printf("Realizada por: Alejandro Santorum & David Cabornero\n");
  printf("Grupo: 1201\n");

  /* comprueba la linea de comandos */
  for(i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-limInf") == 0) {
      inf = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-limSup") == 0) {
      sup = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-numN") == 0) {
      num = atoi(argv[++i]);
    } else {
      fprintf(stderr, "Parametro %s es incorrecto\n", argv[i]);
    }
  }

  /* imprimimos los datos */
  histograma = (int*) malloc ((sup-inf+1)*sizeof(int));
  if(histograma == NULL){
    printf("Error de memoria en la creación del histograma.\n"); /* Error */
    return -1;
  }
  
  for(i = 0; i<(sup-inf+1);i++){
    histograma[i]=0;
  }
  
  for(j = 0; j < num; j++) { 
    aux = aleat_num(inf, sup);
    printf("%d\n", aux);
    for(k=inf; k<=sup; k++){ 
        if(k == aux){
            histograma[k-inf]++;
        }
    }
  }
  
  for(i = inf; i<=sup;i++){
      printf("Frecuencia del %d: %d/%d\n", i, histograma[i-inf], num);
      printf("Porcentaje del %d: %.2f%%\n\n", i, (((double)histograma[i-inf]/num)*100));
  }
  
  out = (FILE *) fopen("data", "w");
  if(out == NULL){
    free(histograma);
    return -1;
  }
  
  for(i=inf; i<=sup; i++){
    fprintf(out, "%d   %d\n", i, histograma[i-inf]);
  }
  
  fclose(out);
  
  free(histograma);
  
  return 0;
}
