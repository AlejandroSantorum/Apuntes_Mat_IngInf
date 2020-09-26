package es.uam.eps.ads.geometria;
import java.util.*;
import java.io.Serializable;
// sobra import es.uam.eps.ads.geometria.Punto;

public class Poligono implements Serializable {	  
	  private List<Punto> puntos;
		  
	  public Poligono() {	    
	    puntos = new ArrayList<>();
	  }
	  
	  public Poligono add(Punto p) { puntos.add(p); return this; }
	  
	  public String toString() { 
		  String resultado = "<";
		  for (Punto p : puntos) { resultado += p; }; // p.toString();
		  return resultado + ">";
	  }
	  
	  public void desplazar(int dx, int dy) {
		  for (Punto p : puntos) { p.desplazar(dx, dy); };
	  }
}

