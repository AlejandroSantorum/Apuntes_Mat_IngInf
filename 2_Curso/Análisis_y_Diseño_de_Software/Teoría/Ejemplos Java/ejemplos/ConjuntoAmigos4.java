package ejemplos;
import java.util.*;

public class ConjuntoAmigos4 {
	  public static void main(String... args) {
		Set<String> amigos = Set.of("Luis","Leo","José");
		Set<String> tusAmigos = new TreeSet<>();
			
		tusAmigos.add("Pi"); tusAmigos.add("Ed"); tusAmigos.add("Leo");
		
		// amigos.addAll( tusAmigos ); // error: amigos es inmutable 
		tusAmigos.addAll( amigos ); 	
		 
		System.out.println( tusAmigos);
	  }
}



