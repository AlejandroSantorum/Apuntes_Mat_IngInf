package ejemplos;
import java.util.*;

public class ListaAmigos7Bis {
	  public static void main(String[] args) {
			List<String> amigos = List.of("Luis","Leo","José");
				


			System.out.println( amigos );
					
			if ( args.length >= 1 && amigos.contains( args[0] ) ) {
			  System.out.println( "Hello " + args[0] + "!" );
			}
	  }
} // para evitar excepción no controlada:


