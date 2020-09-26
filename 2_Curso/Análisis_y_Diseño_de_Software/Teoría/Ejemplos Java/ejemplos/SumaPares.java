package ejemplos;
import java.util.List;

public class SumaPares {
	  public static void main(String... args) {
		List<Integer> numeros = List.of(5,2,4,7,8);
	 	
		System.out.println( numeros );
			
	     int totalPares = 0;
		for (Integer num : numeros) {
			   if (num % 2 == 0) totalPares = totalPares + num;
		}
		System.out.println( "La suma de pares es: " + totalPares);  
	  }
}
