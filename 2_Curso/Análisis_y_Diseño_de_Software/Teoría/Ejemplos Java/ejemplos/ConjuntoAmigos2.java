package ejemplos;
import java.util.*;

public class ConjuntoAmigos2 {
	  public static void main(String... args) {
		Set<String> amigos = new HashSet<>();
		Set<String> tusAmigos = new HashSet<>();
			
		amigos.add("Luis");  amigos.add("Leo");  amigos.add("José");
			
		tusAmigos.add("Pi"); tusAmigos.add("Ed"); tusAmigos.add("Leo");
		
		tusAmigos.addAll( amigos ); 
		amigos.addAll( tusAmigos ); 	
		System.out.println( amigos );   // [Leo, Luis, José, Pi, Ed]
		System.out.println( tusAmigos );// [Luis, Leo, José, Pi, Ed]
	  }
} // el orden es irrelevante, excepto en SortedSet como TreeSet

