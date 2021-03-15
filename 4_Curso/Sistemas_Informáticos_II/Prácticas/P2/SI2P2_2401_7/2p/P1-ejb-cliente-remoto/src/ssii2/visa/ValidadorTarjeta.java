/**
 * Pr&aacute;ctricas de Sistemas Inform&aacute;ticos II
 * 
 * Esta clase valida los campos de una tarjeta de cr&eacute;dito
 */

package ssii2.visa;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import ssii2.visa.error.ErrorVisa;
import ssii2.visa.error.ErrorVisaNumero;
import ssii2.visa.error.ErrorVisaCVV;
import ssii2.visa.error.ErrorVisaFechaCaducidad;
import ssii2.visa.error.ErrorVisaFechaEmision;
import ssii2.visa.error.ErrorVisaTitular;

/**
 *
 * @author phaya
 */
public class ValidadorTarjeta {
    
    /**
     * Texto de error si cualquier campo se encuentra vac&iacute;o
     */
    public final static String CAMPO_VACIO = "Campo vacio";
    
    /**
     * Texto de error si el n&uacute;mero de la tarjerta es inv&aacute;lido
     */    
    public final static String NUMERO_INVALIDO = "Numero de tarjeta no valido";

    /**
     * Texto de error si el c&oacute;digo de verificacion es inv&aacute;lido
     */    
    public final static String CVV_INVALIDO = "Codigo de verificacion no valido";
      
    /**
     * Texto de error si el titular de la tarjeta es inv&aacute;lido
     */       
    public final static String TITULAR_INVALIDO = "Titular de tarjeta no valido";
  
    /**
     * Texto de error si el formato de cualquier fecha es inv&aacute;lido
     */         
    public final static String FECHA_INVALIDA = "Formato de fecha incorrecto";
    
    /**
     * Texto de error si la fecha de caducidad es anterior a la fecha de emisi&oacute;n
     */             
    public final static String FECHA_CADUCIDAD_ANTERIOR = "Fecha de caducidad anterior a fecha de emision";

    /**
     * Numero de milisegundos de un mes
     */
    public final static long MILISEGUNDOS_MES = 30*24*60*60*(long)1000;
        
    private ErrorVisa err = null; 
    
    /**
     * Comprueba si todos los campos de una tarjeta son v&aacute;lidos. 
     * Si alg&acute;n campo produce error se puede acceder acceder a la causa
     * del mismo a trav&eacute; de getErrorVisa.
     * @see getErrorVisa
     * @param t
     * @return true si todos los campos son v&aacute;lidos, false en caso contrario
     */
    public boolean esValida(TarjetaBean t)
    {
        String numero = t.getNumero();
        if (esBlancoONulo(numero)) {
            err = new ErrorVisaNumero(t, CAMPO_VACIO);
            return false;
        }
        if (!esValidoNumero(numero)) {  
            err = new ErrorVisaNumero(t, NUMERO_INVALIDO);
            return false;
        }
        
        String titular = t.getTitular();
        if (esBlancoONulo(titular)) {
            err = new ErrorVisaTitular(t, CAMPO_VACIO);
            return false;        
        }
        if (!esValidoTitular(titular)) {
            err = new ErrorVisaTitular(t, TITULAR_INVALIDO);
            return false;
        }
        
        String fe = t.getFechaEmision(); 
        if (esBlancoONulo(fe)) {
            err = new ErrorVisaFechaEmision(t, CAMPO_VACIO);
            return false;       
        }
        if (!esValidaFechaEmision(fe)) {
             err = new ErrorVisaFechaEmision(t, FECHA_INVALIDA);
            return false;
        }
        
        String fc = t.getFechaCaducidad();
        if (esBlancoONulo(fc)) {
             err = new ErrorVisaFechaCaducidad(t, CAMPO_VACIO);
            return false;       
        }
        if (!esValidaFechaCaducidad(fc)) { 
             err = new ErrorVisaFechaCaducidad(t, FECHA_INVALIDA);
            return false;
        }
               
        if (esAnterior(fc,fe)) {
             err = new ErrorVisaFechaCaducidad(t, FECHA_CADUCIDAD_ANTERIOR);
            return false;       
        }

	String codigoVerificacion = t.getCodigoVerificacion();
        if (esBlancoONulo(codigoVerificacion)) {
            err = new ErrorVisaCVV(t, CAMPO_VACIO);
            return false;
        }
        if (!esValidoCodigoVerificacion(codigoVerificacion)) {  
            err = new ErrorVisaCVV(t, CVV_INVALIDO);
            return false;
        }
                                    
        return true;
    }
    
    /**
     * Devuelve el nombre del &uacute;ltimo error producido 
     * @return nombre de clase que representa el error
     */
    public String getErrorName() 
    {
        if (err != null)
            return err.getClass().getSimpleName();
        else
            return null;
    }
    
    /**
     * Comprueba si una cadena es vac&iacute;a o nula.
     * @param s cadena
     * @return verdadero si el campo es blanco o nulo, falso en caso contrario.
     */
    public boolean esBlancoONulo(String s)
    {
        boolean rt = false;
        if (s == null || s.isEmpty() ){
            rt = true;
        }
        return rt;
    }

    /**
     * Comprueba si el n&uacute;mero de la tarjeta es valido
     * @param s n&uacute;mero de la tarjeta
     * @return verdadero si el campo es correcto, falso en caso contrario.
     */    
    public boolean esValidoNumero(String s)
    {
        boolean rt = true;

        if(s==null) rt = false;
        else if( !s.matches("[0-9]{4} [0-9]{4} [0-9]{4} [0-9]{4}") ) rt=false;

        return rt;
    }

    /**
     * Comprueba si el n&uacute;mero de verificacion de la tarjeta es valido
     * @param s n&uacute;mero de verificacion de la tarjeta
     * @return verdadero si el campo es correcto, falso en caso contrario.
     */    
    public boolean esValidoCodigoVerificacion(String s)
    {
        boolean rt = true;

        if(s==null) rt = false;
        else if( !s.matches("[0-9]{3}") ) rt=false;

        return rt;
    }

    
    /**
     * Comprueba si el nombre completo del titular es valido
     * @param s nombre completo del titular
     * @return verdadero si el campo es correcto, falso en caso contrario.
     */        
    public boolean esValidoTitular(String s)
    {
        boolean rt = true;
        if ( !s.matches( "[a-zA-z ]*" ) ) {
            rt = false;
        }
        return rt;
    }
    
    /**
     * Comprueba si la fecha de emisi&oacute;n es correcta
     * @param s fecha de emisi&oacute;n
     * @return verdadero si el campo es correcto, falso en caso contrario.
     */            
    public boolean esValidaFechaEmision(String s)
    {
        boolean rt = true;
        SimpleDateFormat sdf;
        sdf = new SimpleDateFormat(  "MM/yy"  );
        Date f = null;
        try
        {
            f = sdf.parse( s );
            // Si la fecha es mayor que la fecha de hoy, no es valido
            if(f.compareTo(new Date())>0) rt = false;
        }
        catch ( ParseException exFecha )
        {
            rt = false;
        }
        return rt;
    }
    
    /**
     * Comprueba si la fecha de caducidad es correcta
     * @param s fecha de caducidad
     * @return verdadero si el campo es correcto, falso en caso contrario.
     */                
    public boolean esValidaFechaCaducidad(String fc)
    {
        boolean rt = true;
        SimpleDateFormat sdf;
        sdf = new SimpleDateFormat(  "MM/yy"  );
        Date f = null;
        try
        {
            f = sdf.parse( fc );
            // Sumamos un mes a la fecha de caducidad, por si se da el caso de
            // estar en el mes de caducidad
            f.setTime(f.getTime()+MILISEGUNDOS_MES);
            // Si la fecha es mayor que la fecha de hoy, no es valido
            if(f.compareTo(new Date())<0) rt = false;
        }
        catch ( ParseException exFecha )
        {
            rt = false;
        }
        return rt;
    }  
    
    /**
     * Comprueba si una fecha es anterior a otra 
     * @param fc fecha caducidad
     * @param fe fecha emisi&oacute;n
     * @return verdadero si es anterior fc a fe, falso en caso contrario
     */
    public boolean esAnterior(String fc, String fe)
    {
        boolean rt = false;
        SimpleDateFormat sdf;
        Date dc = null;
        Date de = null;
        
        sdf = new SimpleDateFormat("MM/yy");
        
        try {
            dc = sdf.parse(fc);
            de = sdf.parse(fe);
            // Si la fecha es mayor que la fecha de hoy, no es valido
            if(de.compareTo(dc)<0) rt = false;
        }
        catch(Exception e){
            rt = false;
        }
        /*
        String[] fcPartida = fc.split("/");
        String[] fePartida = fe.split("/");
        if(( Integer.parseInt( fcPartida[1] ) ) < ( Integer.parseInt( fePartida[1] ))){
            rt = true;
        }else if(( Integer.parseInt( fcPartida[0] ) ) < ( Integer.parseInt( fePartida[0] ))){
            rt = true;
        }*/
        return rt;
    }
    
    /**
     * Devuelve el &uacute;ltimo error producido
     * @return error
     */
    public ErrorVisa getErrorVisa() 
    {
        return err;
    }
            
}
