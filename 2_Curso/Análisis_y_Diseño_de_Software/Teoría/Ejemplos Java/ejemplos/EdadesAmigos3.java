package ejemplos;
import java.util.*;
public class EdadesAmigos3 {
	  public static void main(String... args) {
		Map<String, Integer> edades = new HashMap<>();
	     	edades.put("Luis", 23);
	     	edades.put("Leo", 28);
	     	edades.put("José", 25);
		
		System.out.println(edades); // {Luis=23, Leo=28, José=25}
	    	// al cumplir años:
	     	edades.put( "José", edades.get("José")+1 );	
	   	System.out.println(edades); // {Luis=23, Leo=28, José=26}
		
	  } // pero error si José no tiene edad
	}


