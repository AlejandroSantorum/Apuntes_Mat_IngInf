package ejemplos;
import java.io.IOException;
import java.nio.file.*;
import java.util.*;
public class FrecuenciaPalabrasArchivoStream {
  public static void main(String[] args) throws IOException {

    Map<String, Integer> frecuencia = new TreeMap<>();

    Files.lines(Paths.get( "texto.txt" ) )
	    .forEach(linea -> { 
            for (String palabra : linea.split(" "))
              if (frecuencia.containsKey(palabra))
                  frecuencia.put(palabra, frecuencia.get(palabra)+1 );
             else frecuencia.put(palabra, 1 );
          } );
    System.out.println(frecuencia);  
  }
} // lo veremos con más detalle al final del Tema 3



