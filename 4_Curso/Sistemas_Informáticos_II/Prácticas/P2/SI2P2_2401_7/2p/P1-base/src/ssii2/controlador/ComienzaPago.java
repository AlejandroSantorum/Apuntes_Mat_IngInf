/**
 * Pr&aacute;ctricas de Sistemas Inform&aacute;ticos II
 * 
 * Esta servlet se encarga de recibir la peticiones de inicio de pago. Es necesario
 * que en la llamada se incluya un valor correcto de los siguientes par&aacute;metros:
 * <dl>
 *    <dt>Identificador de la transacci&oacuten;</dt>
 *    <dd>Este identificador es de uso interno del comercio y le sirve para poder
 * distinguir entre dos peticiones realizadas concurrentemente</dd>.
 *    <dt>Identificador del comercio</dt>
 *    <dd>Este identificador es &uacute;nico para cada comercio. Se provee al comercio
 * tras la firma del contrato de utilizaci&oacute;n del sistema de pago. </dd>
 *    <dt>Importe</dt>
 *    <dd>Cantidad en euros que corresponde al importe a cargar en la tarjeta. Tiene
 * que se un nuevo igual o superior a cero. No se permiten pagos negativos</dd>
 *    <dt>Ruta Retorno</dt>
 *    <dd>URL a la que se debe regresar una vez completado el pago</dd>
 * </dl>
 * En caso de que falte alguno de los par&aacute;metros anteriores o los valores
 * no sean correcto (ej. pagos negativos) se intepretar&acute; la petici&oacute;n 
 * como un acceso no autorizado. 
 */

package ssii2.controlador;

import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import ssii2.visa.PagoBean;

/**
 *
 * @author phaya
 */
public class ComienzaPago extends ServletRaiz {

    /** 
     * Par&aacute;metro que indica el identificador de transacci&oacute;n
     */
    public final static String PARAM_ID_TRANSACCION = "idTransaccion";
    
    /** 
     * Par&aacute;metro que indica el identificador de comercio
     */
    public final static String PARAM_ID_COMERCIO = "idComercio";
    
    /** 
     * Par&aacute;metro que indica el importe del pago
     */
    public final static String PARAM_IMPORTE = "importe";
    
    /** 
     * Par&aacute;metro que indica la ruta de retorno
     */
    public final static String PARAM_RUTA_RETORNO = "ruta";
    
    /** 
     * Atribute que hace referencia la bean Pago
     */
    public final static String ATTR_PAGO = "pago";
    
    /** 
    * Procesa una petici&oacute;n HTTP tanto <code>GET</code> como <code>POST</code>.
    * @param request objeto de petici&oacute;n
    * @param response objeto de respuesta
    */    
    protected void processRequest(HttpServletRequest request, HttpServletResponse response)
    throws ServletException, IOException {        
        /* Se utiliza un bean para obtener los datos de la transaccion enviados por
             un comercio
                * idTransaccion
                * idComercio
                * importe
                * ruta          
        */
        
        PagoBean pago = creaPago(request);        
        if (! validaParametros(pago)) {      
            accesoNoAutorizado(request, response);
            return;
        }

        request.getSession(true).setAttribute(ATTR_PAGO, pago);
        reenvia("/formdatosvisa.jsp", request, response);
        return;       
    }      
    
   /** 
    * Procesa una petici&oacute;n HTTP <code>GET</code>.
    * @param request objeto de petici&oacute;n
    * @param response objeto de respuesta
    */
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
    throws ServletException, IOException {
        processRequest(request, response);
    } 

    /** 
    * Procesa una petici&oacute;n HTTP <code>POST</code>.
    * @param request objeto de petici&oacute;n
    * @param response objeto de respuesta
    */
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
    throws ServletException, IOException {
        processRequest(request, response);
    }
    
    /** 
    * Comprueba si un bean de pago es correcto.
    * @param pago bean que contiene los datos del pago
    * @return verdadero si es correcto, falso en caso contrario
    * @see ssii2.visa.PagoBean 
    */
    private boolean validaParametros(PagoBean pago) {
                
        if (esBlancoONulo(pago.getIdTransaccion())) {
            errorLog("[WARNING] Incorrecto idTransaccion:" + pago.getIdTransaccion());
            return false;
        }
        
        if (esBlancoONulo(pago.getIdComercio())) {
            errorLog("[WARNING] Incorrecto IdComercio:" + pago.getIdComercio());
            return false;
        }
        
        if (pago.getImporte() < 0) {                   
            errorLog("[WARNING] Incorrecto importe:" + pago.getImporte());
            return false;  
        }
                
        if (esBlancoONulo(pago.getRutaRetorno())) {
            errorLog("[WARNING] Incorrecta ruta retorno:" + pago.getRutaRetorno());
            return false;          
        }
        
        return true;        
    }
    
    /** 
    * Crea un bean de pago a partir de los par&aacute;metros de la petici&oacute;.
    * @param request objeto de petici&oacute;n
    * @return bean que contiene el pago a realizar
    * @see ssii2.visa.PagoBean 
    */
    private PagoBean creaPago(HttpServletRequest request) {
        PagoBean pago = new PagoBean();
        pago.setIdTransaccion(request.getParameter(PARAM_ID_TRANSACCION));
        pago.setIdComercio(request.getParameter(PARAM_ID_COMERCIO));
        double impd=-1.0;
        try {
            impd = Double.parseDouble(request.getParameter(PARAM_IMPORTE));
        } catch (NumberFormatException e) {
            impd = -1.0;
        } catch (NullPointerException e) {
            impd = -1.0;
        }
        pago.setImporte(impd);
        pago.setRutaRetorno(request.getParameter(PARAM_RUTA_RETORNO));  
        return pago;
    }
    
    /** 
    * Comprueba si una cadena de caracteres es vac&iacute;a o nula.
    * @param s cadena de caracteres
    * @return verdadero si es vac&iacute;a o nula, falso en caso contrario    
    */
    private boolean esBlancoONulo(String s) {
        return ((s == null) || (s.equals("")));
    }
           

    /** 
    * Devuelve una descripici&oacute;n abreviada del servlet
    */
    @Override
    public String getServletInfo() {
        return "Servlet Comienza Pago";
    }

}
