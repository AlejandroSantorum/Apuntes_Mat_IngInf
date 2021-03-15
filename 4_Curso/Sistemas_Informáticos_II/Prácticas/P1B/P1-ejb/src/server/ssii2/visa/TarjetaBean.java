/**
 * Pr&aacute;ctricas de Sistemas Inform&aacute;ticos II
 * 
 * Esta clase incluye los campos de una tarjeta de cr&eacute;dito
 * 
 */
package ssii2.visa;

public class TarjetaBean {
    
    private String numero;
    private String titular;
    private String fechaEmision;
    private String fechaCaducidad;
    private String codigoVerificacion; /* CVV2 */

    /**
     * Devuelve el titular de la tarjeta
     * @return titular de la tarjeta
     */
    public String getTitular() {
        return titular;
    }

    /**
     * Establece el titular de la tarjeta
     * @param titular
     */
    public void setTitular(String titular) {
        this.titular = titular;
    }

    /**
     * Devuelve el n&uacute;mero de la tarjeta
     * @return el n&uacute;mero de la tarjeta
     */   
    public String getNumero() {
        return numero;
    }

    /**
     * Establece el n&uacute;mero de la tarjeta
     * @param numero de la tarjeta
     */
    public void setNumero(String numero) {
        this.numero = numero;
    }

    /**
     * Devuelve la fecha emisi&oacute;n
     * @return la fecha emisi&oacute;n
     */
    public String getFechaEmision() {
        return fechaEmision;
    }

    /**
     * Establece la fecha emisi&oacute;n
     * @param fechaEmision la fecha emisi&oacute;n
     */
    public void setFechaEmision(String fechaEmision) {
        this.fechaEmision = fechaEmision;
    }

    /**
     * Devuelve la fecha de caducidad
     * @return la fecha Caducidad
     */
    public String getFechaCaducidad() {
        return fechaCaducidad;
    }

    /**
     * Establece la fecha de caducidad
     * @param fechaCaducidad la fecha caducidad
     */
    public void setFechaCaducidad(String fechaCaducidad) {
        this.fechaCaducidad = fechaCaducidad;
    }

    /**
     * Devuelve el c&oacute;digo de verificaci&oacute;n
     * @return el c&oacute;digo verificacion
     */
    public String getCodigoVerificacion() {
        return codigoVerificacion;
    }

    /**
     * Establece el c&oacute;digo de verificaci&oacute;n
     * @param codigoVerificacion el c&oacute;digo de verificaci&oacute;n
     */
    public void setCodigoVerificacion(String codigoVerificacion) {
        this.codigoVerificacion = codigoVerificacion;
    }
}
