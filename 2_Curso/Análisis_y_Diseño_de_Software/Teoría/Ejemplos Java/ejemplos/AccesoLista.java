package ejemplos;
import java.util.List;

public class AccesoLista {
	  public static void main(String... args) {
		List<Integer> numeros = List.of(5,2,4,7,8);
	 	
		System.out.println( numeros );
			
		System.out.println( numeros.size()   + " n�meros" );
		System.out.println( "Primer n�mero es: " + numeros.get(0) );
		System.out.println( "�ltimo n�mero es: " 
	                            + numeros.get( numeros.size() - 1) );
	  }
	} // la lista numeros es inmutable: ni a�adir ni borrar elementos

