package ejemplos.persistencia;
import java.util.*;

import es.uam.eps.ads.geometria.Poligono;
import es.uam.eps.ads.geometria.Punto;

import java.io.*;

public class PersistenciaPoligonos  {	
	
	public static void main(String[] args) throws IOException {
		
		  ObjectOutputStream salidaLineas = 
		       new ObjectOutputStream(
		           new FileOutputStream("poligonos.objectData") );
		  
		  Poligono segmento = new Poligono();
		  Poligono cuadrado = new Poligono();
		  segmento.add(new Punto(1,1)).add(new Punto(3,2));
		  cuadrado.add(new Punto(0,0)).add(new Punto(0,2))
		          .add(new Punto(2,2)).add(new Punto(0,2))
		          .add(new Punto(0,0));
		  
		  System.out.println( segmento );
		  System.out.println( cuadrado );
		  salidaLineas.writeObject(segmento);
		  salidaLineas.writeObject(cuadrado);
		  salidaLineas.close();		  
	}
}

