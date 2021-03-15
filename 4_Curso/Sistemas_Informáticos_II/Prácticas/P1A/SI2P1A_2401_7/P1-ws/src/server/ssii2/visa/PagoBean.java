/**
 * Pr&aacute;ctricas de Sistemas Inform&aacute;ticos II
 * 
 * Esta clase incluye los datos necesarios para realizar un pago. En esta
 * primera versi&oacute; no se a&ntilde;ade aun el bean Tarjeta
 */

package ssii2.visa;

/**
 *
 * @author jaime
 */
public class PagoBean {
    
	private String idTransaccion; 
	private String idComercio;  
	private double importe;
        private String ruta_retorno;
        
        private TarjetaBean tarjeta;
        
        /* Calculados por el gestor de medios de pago */
        private String codRespuesta;    
        private String idAutorizacion;  

    /**
     * @return el ID de transacci&oacute;n
     */
    public String getIdTransaccion() {
        return idTransaccion;
    }

    /**
     * @param idTransaccion el ID de transacci&oacute;n
     */
    public void setIdTransaccion(String idTransaccion) {
        this.idTransaccion = idTransaccion;
    }

    /**
     * @return el ID del comercio
     */
    public String getIdComercio() {
        return idComercio;
    }

    /**
     * @param idComercio el ID del comercio
     */
    public void setIdComercio(String idComercio) {
        this.idComercio = idComercio;
    }

    /**
     * @return el importe
     */
    public double getImporte() {
        return importe;
    }

    /**          
     * @param importe el nuevo importe. Si hubiera alg&uacute;n error en la 
     * cadena de caracteres, el importe final se establecer&iacute;a a negativo. 
     */
    public void setImporte(String importe) {
        try {
            this.importe = Double.parseDouble(importe);            
        } catch (NumberFormatException e) {
            this.importe = -1;
        } catch (NullPointerException e) {
            this.importe = -1;      
        }
    }
    
    /**
     * @param importe el nuevo importe. 
     */
    public void setImporte(double importe) {
        this.importe = importe;
    }

    /**
     * @return la ruta de retorno
     */
    public String getRutaRetorno() {
        return this.ruta_retorno;
    }
    
    /**
     * @param ruta la ruta de retorno
     */
    public void setRutaRetorno(String ruta) {
        this.ruta_retorno = ruta;
    }

    /**
     * @return el c&oacute;digo de respuesta
     */
    public String getCodRespuesta() {
        return codRespuesta;
    }

    /**
     * @param codRespuesta c&oacute;digo de respuesta
     */
    public void setCodRespuesta(String codRespuesta) {
        this.codRespuesta = codRespuesta;
    }

    /**
     * @return el ID de autorizaci&oacute;n
     */
    public String getIdAutorizacion() {
        return idAutorizacion;
    }

    /**
     * @param idAutorizacion el ID de autorizaci&oacute;n
     */
    public void setIdAutorizacion(String idAutorizacion) {
        this.idAutorizacion = idAutorizacion;
    }
    
    /**
     * @return la tarjeta
     */
    public TarjetaBean getTarjeta() {
        return tarjeta;
    }

    /**
     * @param tarjeta bean tarjeta 
     */
    public void setTarjeta(TarjetaBean tarjeta) {
        this.tarjeta = tarjeta;
    }
}
