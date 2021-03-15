package intLibrary;

import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

public class client {

    private client() {}

    public static void main(String[] args) {

        
        if (args.length < 4)
        {
	  System.err.println("Usage: <naming service host> <tipo de operacion (0:suma / 1: resta / 2: multiplicacion / 3:division)> <operador 1> <operador 2>\n\n");
	  return;
        }
        
        
        String host = (args.length < 1) ? null : args[0];
               
        
        try {
            Registry registry = LocateRegistry.getRegistry(host);
            intLibrary stub = (intLibrary) registry.lookup("intLibrary");
            short response = stub.procesarPeticion(Short.parseShort(args[1]),Short.parseShort(args[2]),Short.parseShort(args[3]));
            System.out.println("Respuesta del servidor: " + response);
        } catch (Exception e) {
            System.err.println("Client exception: " + e.toString());
            e.printStackTrace();
        }
    }
}
