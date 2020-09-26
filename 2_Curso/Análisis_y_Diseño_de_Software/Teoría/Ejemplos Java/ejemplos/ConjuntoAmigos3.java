package ejemplos;
import java.util.*;

public class ConjuntoAmigos3 {
	  public static void main(String... args) {
		Set<String> amigos = new HashSet<>();
		Set<String> tusAmigos = new TreeSet<>();
			
		amigos.add("Luis");  amigos.add("Leo");  amigos.add("José");
			
		tusAmigos.add("Pi"); tusAmigos.add("Ed"); tusAmigos.add("Leo");
		
		tusAmigos.addAll( amigos ); 
		amigos.addAll( tusAmigos ); 	
		
		System.out.println( tusAmigos.equals( amigos ) ); // true 
	  }
	}


