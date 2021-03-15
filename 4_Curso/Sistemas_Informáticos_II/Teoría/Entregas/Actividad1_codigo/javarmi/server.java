package intLibrary;

import java.rmi.registry.Registry;
import java.rmi.registry.LocateRegistry;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

public class server implements intLibrary {

    public server() {}

    // implement procesarPeticion() method
    public short procesarPeticion(short type, short op1, short op2) {
      
      switch(type)
      {
	case 0: return (short)(op1+op2);
	case 1: return (short)(op1-op2);
	case 2: return (short)(op1*op2);
	case 3: return (short)(op1/op2);
	default: return -1;
      }
      
    }

    public static void main(String args[]) {

        try {
            server obj = new server();
            intLibrary stub = (intLibrary) UnicastRemoteObject.exportObject(obj, 0);

            Registry registry = LocateRegistry.getRegistry();
            registry.bind("intLibrary", stub);

            System.err.println("Server ready");
        } catch (Exception e) {
            System.err.println("Server exception: " + e.toString());
            e.printStackTrace();
        }
    }
}
