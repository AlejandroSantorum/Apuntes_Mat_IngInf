package ejemplos;
import java.util.*;

public class ListaAmigos8 {
	  public static void main(String... args) {
		List<String> amigos = List.of("Luis","Leo","Jos�");
		List<String> tusAmigos = new LinkedList<>();
			
		tusAmigos.add("Pi"); tusAmigos.add("Ed"); tusAmigos.add("Mar");

		tusAmigos.addAll( amigos );
			
		System.out.println( tusAmigos );//salida:[Pi,Ed,Mar,Luis,Leo,Jos�]

	     // Error al ejecutar: amigos.addAll( tusAmigos );
	  }
} // la lista amigos es inmutable: ni a�adir ni borrar elementos


