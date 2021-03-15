#include "square.h"
#include <stdio.h>

int main(int argc, char **argv) {

	CLIENT *cl;

	square_in in;
	square_out *outp;

	if (argc != 3) {
		printf("usage:%s <hostname> <integer>\n", argv[ 0 ]);
		exit(1);
	}
	
	if ((cl = clnt_create(argv[ 1 ], SQUARE_PROG, SQUARE_VERS, "tcp")) == 0) {
		printf("Error in RPC call!\n");
		exit(1);
	}

	in.arg1 = atoi(argv[ 2 ]);

	if ((outp = squareproc_1(&in, cl)) == NULL) {
		printf("Error in RPC call!\n");
		exit(1);
	}

	printf("Result:%ld\n", outp->res1);

	exit(0);
}

