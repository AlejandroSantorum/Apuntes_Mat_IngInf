package ejemplos;
import java.util.*;

public class ListaAmigos3 {
	  public static void main(String... args) {
		List<String> amigos = new LinkedList<>();
			
		amigos.add("Luis");  amigos.add("Leo");  amigos.add("Jos�");
			
		System.out.println( amigos );
				
		for (String amigo : amigos) {
		  System.out.println( "Hello " + amigo + "!" );
		}
	  }
} // IMPORTANTE: 
  //   el c�digo para recorrerla no depende de la implementaci�n 

