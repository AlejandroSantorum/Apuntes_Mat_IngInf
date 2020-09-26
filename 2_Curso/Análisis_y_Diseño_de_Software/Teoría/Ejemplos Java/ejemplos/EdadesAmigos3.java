package ejemplos;
import java.util.*;
public class EdadesAmigos3 {
	  public static void main(String... args) {
		Map<String, Integer> edades = new HashMap<>();
	     	edades.put("Luis", 23);
	     	edades.put("Leo", 28);
	     	edades.put("Jos�", 25);
		
		System.out.println(edades); // {Luis=23, Leo=28, Jos�=25}
	    	// al cumplir a�os:
	     	edades.put( "Jos�", edades.get("Jos�")+1 );	
	   	System.out.println(edades); // {Luis=23, Leo=28, Jos�=26}
		
	  } // pero error si Jos� no tiene edad
	}


