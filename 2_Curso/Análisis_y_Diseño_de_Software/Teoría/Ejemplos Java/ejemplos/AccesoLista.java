package ejemplos;
import java.util.List;

public class AccesoLista {
	  public static void main(String... args) {
		List<Integer> numeros = List.of(5,2,4,7,8);
	 	
		System.out.println( numeros );
			
		System.out.println( numeros.size()   + " números" );
		System.out.println( "Primer número es: " + numeros.get(0) );
		System.out.println( "Último número es: " 
	                            + numeros.get( numeros.size() - 1) );
	  }
	} // la lista numeros es inmutable: ni añadir ni borrar elementos

