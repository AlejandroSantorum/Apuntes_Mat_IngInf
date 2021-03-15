        
import java.rmi.registry.Registry;
import java.rmi.registry.LocateRegistry;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
        
public class Server extends java.rmi.server.UnicastRemoteObject implements Hello {
        
    public Server() throws java.rmi.RemoteException {};

    public String sayHello() {
        return "Hello, world!";
    }
        
    public static void main(String args[]) {
        
        try {
            Server hello = new Server();

            // Bind the remote object's stub in the registry

            Registry registry = LocateRegistry.getRegistry();
            registry.bind("Hello", hello);

            System.err.println("Server ready");
        } catch (Exception e) {
            System.err.println("Server exception: " + e.toString());
            e.printStackTrace();
        }
    }
}
