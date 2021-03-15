//HelloServer.java
import javax.naming.InitialContext;
import javax.naming.Context;


public class HelloServer {
    public static void main(String[] args) {
        try {
            // Step 1: Instantiate the Hello servant
            HelloImpl helloRef = new HelloImpl();

            // Step 2: Publish the reference in the Naming Service 
            // using JNDI API
            Context initialNamingContext = new InitialContext();
            initialNamingContext.rebind("HelloService", helloRef );

            System.out.println("Hello Server: Ready...");

         } catch (Exception e) {
            System.out.println("Trouble: " + e);
            e.printStackTrace();
         } 
     }
}
