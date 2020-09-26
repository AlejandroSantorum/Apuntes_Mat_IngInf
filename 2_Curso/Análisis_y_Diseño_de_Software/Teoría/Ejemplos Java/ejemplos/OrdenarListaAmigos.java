package ejemplos;
import java.util.*;

public class OrdenarListaAmigos {
	  public static void main(String... args) {
		List<String> amigos = new ArrayList<String>();
		List<String> tusAmigos = new LinkedList<String>();
			
		amigos.add("Luis");  amigos.add("Leo");   amigos.add("José");	
		tusAmigos.add("Pi"); tusAmigos.add("Ed"); tusAmigos.add("Mar");
		
	     Collections.sort(amigos);   Collections.sort(tusAmigos);

	     System.out.println(amigos);    // [José, Leo, Luis]
	     System.out.println(tusAmigos); // [Ed, Mar, Pi]
	  }
}



