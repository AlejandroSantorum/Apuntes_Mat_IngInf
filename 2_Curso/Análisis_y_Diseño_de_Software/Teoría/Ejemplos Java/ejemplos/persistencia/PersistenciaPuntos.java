package ejemplos.persistencia;
import java.io.*;
import java.util.*;

import es.uam.eps.ads.geometria.Punto;

public class PersistenciaPuntos {
	
 public static void main(String[] args) throws IOException {
	 
  ObjectOutputStream salidaObjetos = 
       new ObjectOutputStream(
           new FileOutputStream("puntos.objectData") );
  
  List<Punto> puntos = 
      new LinkedList<>(Arrays.asList( new Punto(3,4), new Punto(0,3), new Punto(2,6) ));
  
  salidaObjetos.writeObject(puntos);
  salidaObjetos.close();		  
 }
}
