package ejemplos.persistencia;
import java.io.*;
import java.util.*;
import es.uam.eps.ads.geometria.Punto;

public class LeerPuntos {

  public static void main(String[] args) throws Exception {
	ObjectInputStream entradaObjetos = 
        new ObjectInputStream(
          new FileInputStream("puntos.objectData") );
	String puntos = (String)entradaObjetos.readObject();
	entradaObjetos.close();
	System.out.println("Leido: " + puntos);
  }

}
