package ejemplos;
import java.util.*;

public class ListaAmigos5 {
	  public static void main(String[] args) {
		List<String> amigos = new ArrayList<>();
			
		amigos.add("Luis");  amigos.add("Leo");  amigos.add("Jos�");
			
		System.out.println( amigos );
				
		if ( amigos.contains( args[0] ) ) {  // �alg�n error?
		  System.out.println( "Hello " + args[0] + "!" );
		}
	  }
	}

