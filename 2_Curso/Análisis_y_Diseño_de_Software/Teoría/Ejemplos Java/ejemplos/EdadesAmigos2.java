package ejemplos;
import java.util.*;
public class EdadesAmigos2 {
	  public static void main(String... args) {
		Map<String, Integer> edades = 
	                              Map.of("Luis",23,"Leo",28,"Jos�",25);
			


		System.out.println(edades); 
		 
	     if (! edades.containsKey( "Ana" ))
			System.out.println( "Ana no tiene edad." );
	     else System.out.println("Edad de Ana es: " + edades.get("Ana"));
							//  Ana no tiene edad.
	  }
	}  // El mapa edades es inmutable

