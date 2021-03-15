// Copyright and License 
 
import HelloApp.*;
import org.omg.CosNaming.*;
import org.omg.CosNaming.NamingContextPackage.*;
import org.omg.CORBA.*;

public class HelloClient
{
  static Hello helloImpl;

  public static void main(String args[])
    {
      try{
        // create and initialize the ORB
	ORB orb = ORB.init(args, null);

        // get the root naming context
        org.omg.CORBA.Object objRef = 
	    orb.resolve_initial_references("NameService");
        // Use NamingContextExt instead of NamingContext. This is 
        // part of the Interoperable naming Service.  
        NamingContextExt ncRef = NamingContextExtHelper.narrow(objRef);
 
        // resolve the Object Reference in Naming

        String name = "Hello";

	org.omg.CORBA.Object objRef_server = ncRef.resolve_str(name);

        // Create an Any object to hold the return value of the method and 
        // wrap it in a NamedValue 

        Any result = orb.create_any(); 
        result.insert_string(""); 
        NamedValue resultVal = orb.create_named_value("result", result, org.omg.CORBA.ARG_OUT.value); 
 
        // Create the method request using the default context, the name of 
        // the method, the NVList argument list, and the NamedValue for the 
        // result.  Then invoke the method by calling invoke () on the Request. 

        Request thisReq = objRef_server._create_request(null, "sayHello", null, resultVal); 
        thisReq.invoke(); 
  
        // Get the return value from the Request object and output results. 

        result = thisReq.result().value(); 
        System.out.println(result.extract_string()); 


	} catch (Exception e) {
          System.out.println("ERROR : " + e) ;
	  e.printStackTrace(System.out);
	  }
    }

}
