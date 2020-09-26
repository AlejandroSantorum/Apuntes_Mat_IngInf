package ejemplos;
import java.io.*; 
import java.util.*;
public class FrecuenciaPalabrasArchivo {
	  public static void main(String[] args) throws IOException {
	    BufferedReader buffer = new BufferedReader(
	                              new InputStreamReader(
	                                new FileInputStream("texto.txt")));
	    Map<String, Integer> frecuencia = new TreeMap<>();
	    String linea;
	    while ((linea = buffer.readLine()) != null) { 
	      for (String palabra : linea.split(" "))
	        if (frecuencia.containsKey(palabra))
	             frecuencia.put(palabra, frecuencia.get(palabra)+1 );
	        else frecuencia.put(palabra, 1 );
	    }
	    System.out.println(frecuencia);
	    buffer.close(); 
	  }
}


