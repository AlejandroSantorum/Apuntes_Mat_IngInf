package ejemplos;
import java.io.*; 
import java.util.*;
import java.io.IOException; import java.nio.file.*;import java.util.*;
public class FrecuenciaPalabrasArchivo2 {
  public static void main(String[] args) throws IOException {

    List<String> lineas = Files.readAllLines(Paths.get("texto.txt"));

    Map<String, Integer> frecuencia = new TreeMap<>();
    for (String linea : lineas){ 
      for (String palabra : linea.split(" "))
        if (frecuencia.containsKey(palabra))
             frecuencia.put(palabra, frecuencia.get(palabra)+1 );
        else frecuencia.put(palabra, 1 );
    }
    System.out.println(frecuencia);
  }
}


