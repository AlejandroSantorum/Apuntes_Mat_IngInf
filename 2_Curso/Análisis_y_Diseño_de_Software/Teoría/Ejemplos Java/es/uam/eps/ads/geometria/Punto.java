package es.uam.eps.ads.geometria;

import java.io.Serializable;

public class Punto implements Serializable {	  
	  private int x, y; // componentes privados
		  
	  public Punto(int x, int y) {	    
	    this.x = x; 
	    this.y = y;
	  }
	  
	  public String toString( ) { return "("+x+","+y+")"; }
	  
	  public void desplazar(int dx, int dy) { x += dx; y += dy; }
}

