package ejemplos;
import java.util.List;

public class CuentaParesStream {
	  public static void main(String... args) {
			List<Integer> numeros = List.of(5,2,4,7,8);
		 	
			System.out.println( "El número de pares es: " 
		           + numeros.stream().filter(n -> n % 2 == 0).count());
		  
		  }

}
