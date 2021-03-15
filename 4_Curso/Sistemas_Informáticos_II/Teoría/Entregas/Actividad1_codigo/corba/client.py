import sys
from omniORB import CORBA
import IntLibraryApp
import CosNaming



if len(sys.argv) != 6:
	print "Uso: python client.py -ORBInitRef NameService=`cat IOR_ns.txt` <tipo de operacion (0:suma / 1: resta / 2: multiplicacion / 3:division)> <operador 1> <operador 2>"
	sys.exit()



orb = CORBA.ORB_init(sys.argv, CORBA.ORB_ID)



obj = orb.resolve_initial_references("NameService")
rootContext = obj._narrow(CosNaming.NamingContext)



name = [CosNaming.NameComponent("IntLibrary","")]
obj = rootContext.resolve(name)

l = obj._narrow(IntLibraryApp.IntLibrary)

if l is None:
	print "La referencia facilitada por el NS no es un IntLibraryApp::IntLibrary"
	sys.exit(1)




result  = l.procesarPeticion(int(sys.argv[ 1 ]), int(sys.argv[ 2 ]), int(sys.argv[ 3 ]))

print "El resultado de la operacion es: %d" % (result)


