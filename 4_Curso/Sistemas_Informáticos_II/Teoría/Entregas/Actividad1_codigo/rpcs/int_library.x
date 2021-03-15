
struct argumento { 		/* input argument */
	int type;
	int op1;
	int op2;
};  

struct resultado{ 		/* output argument */
	int res;
};  

program INT_LIBRARY_PROG {

	version INT_LIBRARY_VERS {
		resultado PROCESAPETICION(argumento) = 1; /* procedure number 1 */
	} = 1; 			/* version number */	

} = 0x00000007;		/* Program number */

