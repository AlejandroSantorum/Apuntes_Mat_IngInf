package ejemplos;
import java.util.*;
public class FrecuenciaPalabrasArgs {
	  public static void main(String... args) {
		Map<String, Integer> frecuencia = new HashMap<>();


		for (String palabra : args) {
		   if (frecuencia.containsKey(palabra))
	   		   frecuencia.put( palabra, frecuencia.get(palabra)+1 );
		   else frecuencia.put( palabra, 1 );
		}
		System.out.println(frecuencia);
		// Con args: la hora de la verdad es la hora de la muerte
	     // salida: {de=2, verdad=1, la=4, hora=2, muerte=1, es=1}
	  }
	}
