package ejemplos;
import java.util.*;
public class EdadesAmigos1 {
	  public static void main(String... args) {
		Map<String, Integer> edades = 
	                              Map.of("Luis",23,"Leo",28,"Jos�",25);
		
		

		System.out.println(edades); // {Luis=23, Leo=28, Jos�=25}
		 
	     System.out.println("Edad de Jos� es: " + edades.get("Jos�") );
							//  Edad de Jos� es: 25
	     System.out.println("Edad de Ana es: " + edades.get("jos�") );
								//  Edad de Ana es: null
	  }
	}  // El mapa edades es inmutable

