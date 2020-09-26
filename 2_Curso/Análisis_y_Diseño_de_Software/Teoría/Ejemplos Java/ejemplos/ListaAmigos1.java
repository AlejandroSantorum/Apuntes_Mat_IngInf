package ejemplos;
import java.util.*;

public class ListaAmigos1 {
	  public static void main(String... args) {
		List<String> amigos = new ArrayList<String>();
			
		amigos.add("Luis");  amigos.add("Leo");  amigos.add("José");
					
		System.out.println( amigos ); // salida: [Luis,Leo,José]
		System.out.println( amigos.size()   + " amigos" ); // salida: 3
		System.out.println( "Primer amigo es: " + amigos.get(0) );
		System.out.println( "Último amigo es: " 
	                            + amigos.get( amigos.size() - 1) );
			
	  }
	}  // new crea un objeto nuevo de la clase indicada


