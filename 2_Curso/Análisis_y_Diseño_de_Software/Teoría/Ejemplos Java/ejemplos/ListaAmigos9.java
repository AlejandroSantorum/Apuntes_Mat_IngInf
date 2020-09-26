package ejemplos;
import java.util.*;

public class ListaAmigos9 {
	  public static void main(String... args) {
		List<String> amigos = new ArrayList<String>();
		List<String> tusAmigos = new LinkedList<String>();
			
		amigos.add("Luis");  amigos.add("Leo");  amigos.add("José");
			
		tusAmigos.add("Pi"); tusAmigos.add("Ed"); tusAmigos.add("Mar");
		
		amigos.addAll( tusAmigos ); 
		tusAmigos.addAll( amigos );  // ¿algún error? Eso depende…	
		System.out.println( amigos );
		System.out.println( tusAmigos );
	  }                              
}


