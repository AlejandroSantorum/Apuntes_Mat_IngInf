#include <stdio.h>
#include <math.h>

int esPrimo(int n)
{
    int i, resultado=1;

    for (i=2; i<=sqrt(n); i++)
    {
        if (n%i==0)
        {
            resultado=0;
            break;
        }
    }

    return resultado;
}

int CuantosPrimos(int n, int * cantidad)
{
    int i;

    *cantidad=0;

    if (n<0)
        return 0;

    for (i=2; i<n; i++)
        if (esPrimo(i))
            (*cantidad)++;

    return 1;
}

int main()
{
    int num, resultado, retorno;

    do
    {
        printf("Introduce un número entero positivo: ");
        scanf("%d", &num);

        retorno=CuantosPrimos(num, &resultado);
        if (!retorno)
            printf("El número %d no es correcto\n", num);
        else
            printf("El número %d tiene %d números primos inferiores (sin contar el 1 y él mismo)", num, resultado);
    }while(!retorno);

    return 0;
}

---------------------EL MÍO------------------

#include <stdio.h>
#include <math.h>

int esPrimo(int n)
{
	int i, resultado = 1;

	for (i = 2; i <= sqrt(n); i++){
		if (n % i == 0){
			resultado = 0;
			break;
		}
	}
	return resultado;
}

int CuantosPrimos(int a, int *b){
	int i;
	*b = 0;

	if (a<0){
		return 0;
	}

	for (i = 2; i<a; i++){
		if (esPrimo(i)){
			(*b)++;
		}
	}
	return 1;
}


int main(){
	int n, primos = 0, res;

	do{
		printf("Introduce un número entero positivo: ");
		scanf("%d", &n);

		res = CuantosPrimos(n, &primos);

		if (res == 0){
			printf("Error de ejecución. ");
		}
		else if (res == 1){
			printf("El numero %d tiene %d numeros primos inferiores (sin contar el 1 y él mismo)", n, primos);
		}
	} while (res == 0);

	return 0;
}