package ejemplos;
import java.util.*;

public class ListaAmigos2 {
	  public static void main(String... args) {
		List<String> amigos = new ArrayList<>();
			
		amigos.add("Luis");  amigos.add("Leo");  amigos.add("José");
			
		System.out.println( amigos );
				
		for (String amigo : amigos) {
		  System.out.println( "Hello " + amigo + "!" );
		}
	  }
} // la lista amigos NO es inmutable 

