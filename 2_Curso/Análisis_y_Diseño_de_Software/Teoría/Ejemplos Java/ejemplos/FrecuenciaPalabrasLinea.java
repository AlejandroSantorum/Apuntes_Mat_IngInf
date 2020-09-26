package ejemplos;
import java.util.*;
public class FrecuenciaPalabrasLinea {
	  public static void main(String... args) {
		Map<String, Integer> frecuencia = new TreeMap<>();

		String linea = "la hora de   la   verdad    es la hora de la muerte" ;
		for (String palabra : linea.split("\\s+")) {
		   if (frecuencia.containsKey(palabra))
	   		   frecuencia.put( palabra, frecuencia.get(palabra)+1 );
		   else frecuencia.put( palabra, 1 );
		}
		System.out.println(frecuencia);
		//
	     // salida: {de=2, es=1, hora=2, la=4, muerte=1, verdad=1}
	  }
}

