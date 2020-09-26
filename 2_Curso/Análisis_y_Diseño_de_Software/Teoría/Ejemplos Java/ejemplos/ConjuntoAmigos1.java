package ejemplos;
import java.util.*;

public class ConjuntoAmigos1 {
	  public static void main(String... args) {
		Set<String> amigos = new TreeSet<>();
		Set<String> tusAmigos = new TreeSet<>();
			
		amigos.add("Luis");  amigos.add("Leo");  amigos.add("José");
			
		tusAmigos.add("Pi"); tusAmigos.add("Ed"); tusAmigos.add("Leo");
		
		amigos.addAll( tusAmigos ); 
		tusAmigos.addAll( amigos ); 	
		System.out.println( amigos );
		System.out.println( tusAmigos );
	  }
}


