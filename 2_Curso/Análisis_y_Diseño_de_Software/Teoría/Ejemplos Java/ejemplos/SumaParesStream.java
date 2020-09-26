package ejemplos;
import java.util.List;

public class SumaParesStream {
	  public static void main(String... args) {
			List<Integer> numeros = List.of(5,2,4,7,8);
		 	
			System.out.println( "El n�mero de pares es: " 
		           + numeros.stream().filter(n -> n % 2 == 0)
		                             .reduce(0, Integer::sum));
		  
		  }

}
