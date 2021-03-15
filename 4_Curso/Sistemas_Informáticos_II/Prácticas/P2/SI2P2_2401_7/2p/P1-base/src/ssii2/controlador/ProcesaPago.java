/**
 * Pr&aacute;ctricas de Sistemas Inform&aacute;ticos II
 * Esta servlet se encarga de recibir los datos de la tarjeta a la que se va 
 * a cargar el pago. Es necesario que en la llamada se incluya un valor correcto
 * de los siguientes par&aacute;metros:
 * <dl>
 *    <dt>N&uacute;mero de tarjeta</dt>
 *    <dd>N&uacute;mero de tarjeta de la tarjeta VISA</dd>.
 *    <dt>Titular</dt>
 *    <dd>Nombre y apellidos tal cual aparecen en la tarjeta</dd>
 *    <dt>Fecha de emisi&oacute;n</dt>
 *    <dd>Fecha cuando fue emitada la tarjeta</dd>
 *    <dt>Fecha de caducidad</dt>
 *    <dd>Fecha a partir de la cual la tarjeta deja de ser v&aacute;lida</dd>
 *    <dt>CVV</dt>
 *    <dd>C&oacute;digo de verificaci&oacute;n que aparece en la parte posterior</dd>
 * </dl>
 * En caso de que falte alguno de los par&aacute;metros anteriores o los valores
 * no sean correcto (ej. pagos negativos) se intepretar&acute; la petici&oacute;n 
 * como un acceso no autorizado.  
 * 
 * Si los datos de la tarjeta son correcto se invoca al bean VisaDAO que encapsula
 * el servioc de pago con tarjeta. Primeramente se comprueba que se encuentra
 * autorizada, y a continuaci&oacute;n se realiza el pago.  Si la operaci&oacute;n
 * es correcto se redirige a pagoexitoso.jsp. En caso contrario, se redirige
 * al error correspondiente.
 * 
 * @see ssii2.visa.dao.VisaDAO
 * @see ssii2.visa.TarjetaBean
 * @see ssii2.visa.PagoBean
 */

package ssii2.controlador;

import java.io.IOException;
import java.net.InetAddress;
import java.net.NetworkInterface;
import java.net.SocketException;
import java.net.UnknownHostException;
import java.util.Collections;
import java.util.Enumeration;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import ssii2.visa.*;
import ssii2.visa.dao.VisaDAO;

/**
 *
 * @author phaya
 */
public class ProcesaPago extends ServletRaiz {

   
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
     * Par&aacute;metro que indica el n&uacute;mero de la tarjeta
     */
    public final static String PARAM_NUMERO = "numero";
    
    /** 
     * Par&aacute;metro que indica el titular de la tarjeta
     */
    public final static String PARAM_TITULAR = "titular";
   
    /** 
     * Par&aacute;metro que indica la fecha de emisi&oacute;n  de la tarjeta
     */
    public final static String PARAM_FECHAEMISION = "fechaEmision";
  
    /** 
     * Par&aacute;metro que indica la fecha de caducidad  de la tarjeta
     */  
    public final static String PARAM_FECHACADUCIDAD = "fechaCaducidad";
        
    /** 
     * Par&aacute;metro que indica el c&oacute;digo de verificaci&oacute;n 
     * de la tarjeta
     */ 
    public final static String PARAM_CVV = "codigoVerificacion";            

    /**
     * Atribute que hace referencia la bean Pago
     */
    public final static String ATTR_PAGO = "pago";
    
  private static void displayInterfaceInformation(
         NetworkInterface netint) throws SocketException {
       System.out.printf(
           "Display name: %s%n", netint.getDisplayName());
       System.out.printf("Name: %s%n", netint.getName());
       Enumeration<InetAddress> inetAddresses = 
           netint.getInetAddresses();
       for (InetAddress inetAddress : Collections.list(
           inetAddresses)) {
       System.out.printf("InetAddress: %s%n", inetAddress);
       }
      System.out.printf("%n");
     }


private void printAddresses(HttpServletRequest request, HttpServletResponse response) throws SocketException {
    Enumeration<NetworkInterface> nets =
         NetworkInterface.getNetworkInterfaces();
       for (NetworkInterface netint : Collections.list(nets)) {
         displayInterfaceInformation(netint);
       }
      
}
   /** 
    * Procesa una petici&oacute;n HTTP tanto <code>GET</code> como <code>POST</code>.
    * @param request objeto de petici&oacute;n
    * @param response objeto de respuesta
    */
    @Override
    protected void processRequest(HttpServletRequest request, HttpServletResponse response)
    throws ServletException, IOException {
                 
        TarjetaBean tarjeta = creaTarjeta(request);            
        ValidadorTarjeta val = new ValidadorTarjeta();                        
        PagoBean pago = null; 
        
        // printAddresses(request,response);
        if (! val.esValida(tarjeta)) {            
            request.setAttribute(val.getErrorName(), val.getErrorVisa());
            reenvia("/formdatosvisa.jsp", request, response);
            return;
        }

		VisaDAO dao = new VisaDAO();
		HttpSession sesion = request.getSession(false);
		if (sesion != null) {
			pago = (PagoBean) sesion.getAttribute(ComienzaPago.ATTR_PAGO);
		}
		if (pago == null) {
			pago = creaPago(request);
			boolean isdebug = Boolean.valueOf(request.getParameter("debug"));
			dao.setDebug(isdebug);
			boolean isdirectConnection = Boolean.valueOf(request.getParameter("directConnection"));
			dao.setDirectConnection(isdirectConnection);
			boolean usePrepared = Boolean.valueOf(request.getParameter("usePrepared"));	
			dao.setPrepared(usePrepared);
        }

        // Almacenamos la tarjeta en el pago
        pago.setTarjeta(tarjeta);
		
        if (! dao.compruebaTarjeta(tarjeta)) {           
            enviaError(new Exception("Tarjeta no autorizada:"), request, response);
            return;
        }

	if (! dao.realizaPago(pago)) {      
            enviaError(new Exception("Pago incorrecto"), request, response);
            return;
        }

        request.setAttribute(ComienzaPago.ATTR_PAGO, pago);
        if (sesion != null) sesion.invalidate();
        reenvia("/pagoexito.jsp", request, response);
        return;        
    }

     /** 
    * Crea un bean de tarjeta a partir de los par&aacute;metros de la petici&oacute;.
    * @param request objeto de petici&oacute;n
    * @return bean que contiene los datos de la tarjeta recibida
    * @see ssii2.visa.TarjetaBean 
    */
    private TarjetaBean creaTarjeta(HttpServletRequest request) {
        TarjetaBean tarjeta = new TarjetaBean();
        tarjeta.setNumero(request.getParameter(PARAM_NUMERO));
        tarjeta.setTitular(request.getParameter(PARAM_TITULAR));
        tarjeta.setFechaEmision(request.getParameter(PARAM_FECHAEMISION));
        tarjeta.setFechaCaducidad(request.getParameter(PARAM_FECHACADUCIDAD));
        tarjeta.setCodigoVerificacion(request.getParameter(PARAM_CVV)); /* CVV2 */
        return tarjeta;        
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
    * Devuelve una descripici&oacute;n abreviada del servlet
    */
    @Override
    public String getServletInfo() {
        return "Servlet Procesa Pago";
    }

}
