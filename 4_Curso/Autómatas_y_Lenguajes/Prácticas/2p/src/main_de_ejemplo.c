#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../srclib/afnd.h"
#include "../srclib/transforma.h"
#include "../srclib/minimiza.h"

int main(int argc, char ** argv)
{

	AFND * p_afnd;
	AFND * afd;

    // EJEMPLO 1
    // p_afnd = AFNDNuevo("af1",12,2);
    // AFNDInsertaSimbolo(p_afnd,"0");
    // AFNDInsertaSimbolo(p_afnd,"1");
    // AFNDInsertaEstado(p_afnd,"q0",INICIAL_Y_FINAL);
    // AFNDInsertaEstado(p_afnd,"q1",NORMAL);
    // AFNDInsertaEstado(p_afnd,"q2",NORMAL);
    // AFNDInsertaEstado(p_afnd,"q3",NORMAL);
    // AFNDInsertaEstado(p_afnd,"q4",FINAL);
    // AFNDInsertaEstado(p_afnd,"q5",NORMAL);
    // AFNDInsertaEstado(p_afnd,"q6",NORMAL);
    // AFNDInsertaEstado(p_afnd,"q7",NORMAL);
    // AFNDInsertaEstado(p_afnd,"q8",FINAL);
    // AFNDInsertaEstado(p_afnd,"q9",NORMAL);
    // AFNDInsertaEstado(p_afnd,"q10",NORMAL);
    // AFNDInsertaEstado(p_afnd,"q11",NORMAL);
    // AFNDInsertaTransicion(p_afnd, "q0", "0", "q1");
    // AFNDInsertaTransicion(p_afnd, "q0", "1", "q1");
    // AFNDInsertaTransicion(p_afnd, "q1", "0", "q2");
    // AFNDInsertaTransicion(p_afnd, "q1", "1", "q2");
    // AFNDInsertaTransicion(p_afnd, "q2", "0", "q3");
    // AFNDInsertaTransicion(p_afnd, "q2", "1", "q3");
    // AFNDInsertaTransicion(p_afnd, "q3", "0", "q4");
    // AFNDInsertaTransicion(p_afnd, "q3", "1", "q4");
    // AFNDInsertaTransicion(p_afnd, "q4", "0", "q5");
    // AFNDInsertaTransicion(p_afnd, "q4", "1", "q5");
    // AFNDInsertaTransicion(p_afnd, "q5", "0", "q6");
    // AFNDInsertaTransicion(p_afnd, "q5", "1", "q6");
    // AFNDInsertaTransicion(p_afnd, "q6", "0", "q7");
    // AFNDInsertaTransicion(p_afnd, "q6", "1", "q7");
    // AFNDInsertaTransicion(p_afnd, "q7", "0", "q8");
    // AFNDInsertaTransicion(p_afnd, "q7", "1", "q8");
    // AFNDInsertaTransicion(p_afnd, "q8", "0", "q9");
    // AFNDInsertaTransicion(p_afnd, "q8", "1", "q9");
    // AFNDInsertaTransicion(p_afnd, "q9", "0", "q10");
    // AFNDInsertaTransicion(p_afnd, "q9", "1", "q10");
    // AFNDInsertaTransicion(p_afnd, "q10", "0", "q11");
    // AFNDInsertaTransicion(p_afnd, "q10", "1", "q11");
    // AFNDInsertaTransicion(p_afnd, "q11", "0", "q0");
    // AFNDInsertaTransicion(p_afnd, "q11", "1", "q0");

    // EJEMPLO 2
    // p_afnd= AFNDNuevo("afnd", 8, 2);
    //
    // 	AFNDInsertaSimbolo(p_afnd,"0");
    // 	AFNDInsertaSimbolo(p_afnd,"1");
    //
    // 	AFNDInsertaEstado(p_afnd, "A",INICIAL);
    // 	AFNDInsertaEstado(p_afnd, "B", NORMAL);
    // 	AFNDInsertaEstado(p_afnd, "C", FINAL);
    // 	AFNDInsertaEstado(p_afnd, "D", NORMAL);
    // 	AFNDInsertaEstado(p_afnd, "E", NORMAL);
    // 	AFNDInsertaEstado(p_afnd, "F", NORMAL);
    // 	AFNDInsertaEstado(p_afnd, "G", NORMAL);
    // 	AFNDInsertaEstado(p_afnd, "H", NORMAL);
    //
    // 	AFNDInsertaTransicion(p_afnd, "A", "0", "B");
    // 	AFNDInsertaTransicion(p_afnd, "A", "1", "F");
    // 	AFNDInsertaTransicion(p_afnd, "B", "0", "G");
    // 	AFNDInsertaTransicion(p_afnd, "B", "1", "C");
    // 	AFNDInsertaTransicion(p_afnd, "C", "0", "A");
    // 	AFNDInsertaTransicion(p_afnd, "C", "1", "C");
    //
    // 	AFNDInsertaTransicion(p_afnd, "D", "0", "C");
    // 	AFNDInsertaTransicion(p_afnd, "D", "1", "G");
    // 	AFNDInsertaTransicion(p_afnd, "E", "0", "H");
    // 	AFNDInsertaTransicion(p_afnd, "E", "1", "F");
    // 	AFNDInsertaTransicion(p_afnd, "F", "0", "C");
    // 	AFNDInsertaTransicion(p_afnd, "F", "1", "G");
    // 	AFNDInsertaTransicion(p_afnd, "G", "0", "G");
    // 	AFNDInsertaTransicion(p_afnd, "G", "1", "E");
    // 	AFNDInsertaTransicion(p_afnd, "H", "0", "G");
    // 	AFNDInsertaTransicion(p_afnd, "H", "1", "C");

    // EJEMPLO 3
    // p_afnd= AFNDNuevo("afnd", 5, 3);
    //
	// AFNDInsertaSimbolo(p_afnd,"a");
	// AFNDInsertaSimbolo(p_afnd,"b");
	// AFNDInsertaSimbolo(p_afnd,"c");
    //
	// AFNDInsertaEstado(p_afnd, "A", INICIAL);
	// AFNDInsertaEstado(p_afnd, "B", NORMAL);
	// AFNDInsertaEstado(p_afnd, "C", FINAL);
	// AFNDInsertaEstado(p_afnd, "D", NORMAL);
	// AFNDInsertaEstado(p_afnd, "E", NORMAL);
    //
    // AFNDInsertaTransicion(p_afnd, "A", "a", "A");
    // AFNDInsertaTransicion(p_afnd, "A", "b", "B");
    // AFNDInsertaTransicion(p_afnd, "A", "c", "C");
    // AFNDInsertaTransicion(p_afnd, "B", "a", "A");
    // AFNDInsertaTransicion(p_afnd, "B", "b", "B");
    // AFNDInsertaTransicion(p_afnd, "B", "c", "C");
    // AFNDInsertaTransicion(p_afnd, "C", "a", "A");
    // AFNDInsertaTransicion(p_afnd, "C", "b", "B");
    // AFNDInsertaTransicion(p_afnd, "C", "c", "C");
    // AFNDInsertaTransicion(p_afnd, "D", "a", "A");
    // AFNDInsertaTransicion(p_afnd, "D", "b", "E");
    // AFNDInsertaTransicion(p_afnd, "D", "c", "E");
    // AFNDInsertaTransicion(p_afnd, "E", "a", "D");
    // AFNDInsertaTransicion(p_afnd, "E", "b", "D");
    // AFNDInsertaTransicion(p_afnd, "E", "c", "C");


    // EJEMPLO 4
    // p_afnd= AFNDNuevo("afnd", 4, 1);
    //
	// AFNDInsertaSimbolo(p_afnd,"a");
    //
    // AFNDInsertaEstado(p_afnd, "initial", INICIAL);
    // AFNDInsertaEstado(p_afnd, "state2", NORMAL);
    // AFNDInsertaEstado(p_afnd, "state3", NORMAL);
    // AFNDInsertaEstado(p_afnd, "final", FINAL);
    //
    // AFNDInsertaTransicion(p_afnd, "initial", "a", "final");
    // AFNDInsertaTransicion(p_afnd, "state2", "a", "state3");
    // AFNDInsertaTransicion(p_afnd, "state3", "a", "state2");
    // AFNDInsertaTransicion(p_afnd, "final", "a", "state2");

    // EJEMPLO 5
    p_afnd= AFNDNuevo("afnd", 4, 1);

	AFNDInsertaSimbolo(p_afnd,"a");

    AFNDInsertaEstado(p_afnd, "q0", INICIAL);
    AFNDInsertaEstado(p_afnd, "q1", NORMAL);
    AFNDInsertaEstado(p_afnd, "q2", NORMAL);
    AFNDInsertaEstado(p_afnd, "q3", FINAL);

    AFNDInsertaTransicion(p_afnd, "q0", "a", "q3");
    AFNDInsertaTransicion(p_afnd, "q2", "a", "q1");
    AFNDInsertaTransicion(p_afnd, "q1", "a", "q2");
    AFNDInsertaTransicion(p_afnd, "q3", "a", "q0");


    // afd  = AFNDTransforma(p_afnd);
    AFNDImprime(stdout, p_afnd);
    afd = AFNDMinimiza(p_afnd);
	AFNDImprime(stdout,afd);
    AFNDADot(afd);
	AFNDADot(p_afnd);

	AFNDElimina(afd);
	AFNDElimina(p_afnd);

	return 0;
}
