package ejemplos;
import java.util.*;

public class ListaAmigos4 {
	  public static void main(String[] args) {
		List<String> amigos = new ArrayList<>();
			
		amigos.add("Luis");  amigos.add("Leo");  amigos.add("José");
			
		System.out.println( amigos );
				
		if ( amigos.contains("Leo") ) {
		  System.out.println( "Hello Leo!" );
		}
	  }
	}

