package ejemplos;
import java.util.*;

public class ConjuntoAmigos4Java8 {
	  public static void main(String... args) {
	   Set<String> amigos= new HashSet<>(Arrays.asList("Luis","Leo","José"));
		Set<String> tusAmigos = new TreeSet<>();
			
		tusAmigos.add("Pi"); tusAmigos.add("Ed"); tusAmigos.add("Leo");
		
		amigos.addAll( tusAmigos ); // amigos NO es inmutable 
		tusAmigos.addAll( amigos ); 	
		 
		System.out.println( tusAmigos);
	  }
	}




