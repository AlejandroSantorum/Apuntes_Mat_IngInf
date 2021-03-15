// server.java
import java.io.*;
import IntLibraryApp.*;
import org.omg.CosNaming.*;
import org.omg.CosNaming.NamingContextPackage.*;
import org.omg.CORBA.*;
import org.omg.PortableServer.*;
import org.omg.PortableServer.POA;

import java.util.Properties;

class IntLibraryImpl extends IntLibraryPOA {
  private ORB orb;

  public void setORB(ORB orb_val) {
    orb = orb_val; 
  }
    
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
    
  // implement shutdown() method
  public void shutdown() {
    orb.shutdown(false);
  }
}


public class server {

  public static void main(String args[]) {
    try{
    

      ORB orb = ORB.init(args, null);

      POA rootpoa = POAHelper.narrow(orb.resolve_initial_references("RootPOA"));
      rootpoa.the_POAManager().activate();

      
      IntLibraryImpl ilImpl = new IntLibraryImpl();
      ilImpl.setORB(orb); 

      org.omg.CORBA.Object ref = rootpoa.servant_to_reference(ilImpl);
      IntLibrary href = IntLibraryHelper.narrow(ref);
          
      org.omg.CORBA.Object objRef =
          orb.resolve_initial_references("NameService");

      NamingContextExt ncRef = NamingContextExtHelper.narrow(objRef);

      String name = "IntLibrary";
      NameComponent path[] = ncRef.to_name( name );
      ncRef.rebind(path, href);

      System.out.println("IntLibrary Server ready and waiting ...");
      System.out.println("IOR NameServer:");
      System.out.println(ncRef);

      // save IOR into a file

      FileWriter fw = new FileWriter("IOR_ns.txt");
      fw.write(orb.object_to_string(ncRef));
      fw.close();

      orb.run();
    } 
        
      catch (Exception e) {
        System.err.println("ERROR: " + e);
        e.printStackTrace(System.out);
      }

      System.out.println("IntLibrary Server Exiting ...");
        
  }
}
 
