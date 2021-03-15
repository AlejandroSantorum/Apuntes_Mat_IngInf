#include "int_library.h"

/* OBS: La funcion se llama procesapeticion y su version es la 1 */
resultado * procesapeticion_1_svc(argumento *inp, struct svc_req *rqstp) {

	static resultado out;
	
	switch(inp->type)
	{
	  case 0: out.res=inp->op1 + inp->op2; break;
	  case 1: out.res=inp->op1 - inp->op2; break;
	  case 2: out.res=inp->op1 * inp->op2; break;
	  case 3: out.res=inp->op1 / inp->op2; break;
	  default: out.res=-1;
	}

	return(&out);
}

