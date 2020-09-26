package ejemplos;
import java.util.*;

public class ListaAmigos8Java8 {
	  public static void main(String... args) {
	List<String> amigos = new ArrayList<>(Arrays.asList("Luis","Leo","José"));
		List<String> tusAmigos = new LinkedList<>();
			
		tusAmigos.add("Pi"); tusAmigos.add("Ed"); tusAmigos.add("Mar");

		tusAmigos.addAll( amigos );
			
		System.out.println( tusAmigos );//salida:[Pi,Ed,Mar,Luis,Leo,José]

	     amigos.addAll( tusAmigos );
	  }
	} // la lista amigos NO es inmutable



