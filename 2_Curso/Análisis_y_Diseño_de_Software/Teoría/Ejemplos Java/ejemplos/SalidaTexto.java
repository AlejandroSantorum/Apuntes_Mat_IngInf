package ejemplos;

import java.io.*;
import java.time.LocalDate;

public class SalidaTexto {
  public static void main(String[] args) throws IOException {

    FileOutputStream stream = new
        				   FileOutputStream("numeros.txt");

    PrintWriter salida = new PrintWriter(stream);
    for (double i = 0.15; i <= 0.20; i = i + 0.01)
      salida.printf("%5.2f\n", i);
    salida.printf("\t%s\n\t==========", LocalDate.now() );
    salida.flush();
    salida.close();
 }
}

