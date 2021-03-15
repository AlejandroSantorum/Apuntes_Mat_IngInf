#include "int_library.h"
#include <stdio.h>

int main(int argc, char **argv) {

	CLIENT *cl;

	argumento in;
	resultado *outp;

	if (argc != 5) {
		printf("usage:%s <hostname> <tipo de operacion (0:suma / 1: resta / 2: multiplicacion / 3:division)> <operador 1> <operador 2>\n", argv[ 0 ]);
		exit(1);
	}
	
	
	cl = clnt_create(argv[ 1 ], INT_LIBRARY_PROG, INT_LIBRARY_VERS, "tcp");

	in.type = atoi(argv[2]);
	in.op1 = atoi(argv[3]); 
	in.op2 = atoi(argv[4]);

	if ((outp = procesapeticion_1(&in, cl)) == NULL) {
		printf("Error in RPC call!\n");
		exit(1);
	}

	printf("Result:%d\n", outp->res);

	exit(0);
}

