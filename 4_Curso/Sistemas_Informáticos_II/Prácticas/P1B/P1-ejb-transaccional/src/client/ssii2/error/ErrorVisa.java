/**
 * Pr&aacute;ctricas de Sistemas Inform&aacute;ticos II
 * 
 * Clase abstracta que representa un posible error en la validaci&oacute;n de 
 * los campos de una tarjeta 
 */
package ssii2.visa.error;

import ssii2.visa.TarjetaBean;

/**
 *
 * @author phaya
 */
public abstract class ErrorVisa {

    protected String textoError;
    
    protected TarjetaBean tarjeta;

    /**
     * Constructor de ErrorVisa
     * @param t tarjeta que ha producido el error
     * @param causa del mismo
     */
    protected ErrorVisa(TarjetaBean t, String causa) {
        setTarjeta(t);
        setTextoError(causa);
    }

    /**
     * Devuelve la tarjeta que ha producido el error
     * @return la tarjeta erronea
     */
    public TarjetaBean getTarjeta() {
        return tarjeta;
    }
     
    /**
     * Establece una tarjeta como erronea
     * @param t tarjeta erronea
     */
    public void setTarjeta(TarjetaBean t) {
        tarjeta = t;
    }
    
    /**
     * Devuelve el texto que explica la causa del error
     * @return la causa del error
     */
    public String getTextoError() {
        return textoError;
    }
    
    /**
     * Establece el texto que explica la causa del error
     * @param txt el texto 
     */
    public void setTextoError(String txt) {
        textoError = txt;
    }
}
