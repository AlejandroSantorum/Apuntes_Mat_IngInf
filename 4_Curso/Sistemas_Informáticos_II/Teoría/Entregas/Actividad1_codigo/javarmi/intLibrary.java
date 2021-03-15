package intLibrary;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface intLibrary extends Remote {
    short procesarPeticion(short type, short op1, short op2) throws RemoteException;
}
