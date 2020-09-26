package ejemplos;
import java.util.*;
public class EdadesAmigos1Java8 {
	  public static void main(String... args) {
		Map<String, Integer> edades = new HashMap<>();
	     	edades.put("Luis", 23);
	     	edades.put("Leo", 28);
	     	edades.put("Jos�", 25);

		System.out.println(edades); // {Luis=23, Jos�=25, Leo=28}
		 
	     System.out.println("Edad de Jos� es: " + edades.get("Jos�") );
							//  Edad de Jos� es: 25
	     System.out.println("Edad de Ana es: " + edades.get("jos�") );
								//  Edad de Ana es: null
	  }
}  // El mapa edades es inmutable


