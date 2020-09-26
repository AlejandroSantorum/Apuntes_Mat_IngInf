package ejemplos;
import java.io.*;
public class DemoInput2 {
	  public static void main(String[] args) throws IOException {
	    BufferedReader buffer = new BufferedReader(
	                              new InputStreamReader(
	                                new FileInputStream("texto.txt")));

	    String linea;
	    while ((linea = buffer.readLine()) != null) { 
	      System.out.println( "Linea leida: " + linea);
	    }

	    buffer.close();
	 }
	}

           

