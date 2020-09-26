package ejemplos.persistencia;
import java.io.*;
import java.util.*;
import es.uam.eps.ads.geometria.Poligono;

public class LeerPoligonos {

  public static void main(String[] args) throws Exception {
	ObjectInputStream entradaObjetos = 
        new ObjectInputStream(
          new FileInputStream("poligonos.objectData") );
	Poligono p1 = (Poligono)entradaObjetos.readObject();
	Poligono p2 = (Poligono)entradaObjetos.readObject();
	entradaObjetos.close();
	System.out.println("Segmento: " + p1);
	System.out.println("Cuadrado: " + p2);
	p2.desplazar(10,100);
	System.out.println("Cuadrado desplazado: " + p2);
  }

}
