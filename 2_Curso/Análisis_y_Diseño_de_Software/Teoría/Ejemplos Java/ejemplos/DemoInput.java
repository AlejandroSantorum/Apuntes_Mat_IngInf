package ejemplos;
import java.io.*;
public class DemoInput {
	  public static void main(String[] args) throws IOException {
	    FileInputStream stream = new FileInputStream( "texto.txt" );
	    InputStreamReader reader = new InputStreamReader(stream);
	    BufferedReader buffer = new BufferedReader(reader);

	    String linea;
	    while ((linea = buffer.readLine()) != null) { 
	      System.out.println( "Linea leida: " + linea);
	    }

	    buffer.close();
	 }
	}
           

