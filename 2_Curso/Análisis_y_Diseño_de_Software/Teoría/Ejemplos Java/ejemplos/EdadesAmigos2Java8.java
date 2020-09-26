package ejemplos;
import java.util.*;
public class EdadesAmigos2Java8 {
	  public static void main(String... args) {
		Map<String, Integer> edades = new HashMap<>();
	     	edades.put("Luis", 23);
	     	edades.put("Leo", 28);
	     	edades.put("José", 25);

		System.out.println(edades); 
		 
	     if (! edades.containsKey( "Ana" ))
			System.out.println( "Ana no tiene edad." );
	     else System.out.println("Edad de Ana es: " + edades.get("Ana"));
							//  Ana no tiene edad.
	  }
}  // El mapa edades NO es inmutable


