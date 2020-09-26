package ejemplos;
import java.util.*;


public class SumaParesJava8 {
	public static void main(String... args) {

		// Version Java 9  List<Integer> nums = List.of(5,2,4,7,8);
		// Version Java 8. Obliga a tener DOS import adicionales
		List<Integer> nums = new ArrayList<>( Arrays.asList(5,2,4,7,8) );
		System.out.println( nums );
		
        int totalPares = 0;
		for (Integer num : nums) {
		   if (num % 2 == 0) totalPares = totalPares + num;
		}
		System.out.println("La suma de pares es: " + totalPares);
	}
}
