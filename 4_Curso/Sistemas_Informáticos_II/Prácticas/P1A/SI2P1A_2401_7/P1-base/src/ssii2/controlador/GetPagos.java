/**
 * Pr&aacute;ctricas de Sistemas Inform&aacute;ticos II
 * 
 * Esta servlet se encarga de visualizar los pagos para un determinado comercio. 
 * Es necesario que en la llamada se incluya un valor correcto del par&aacute;metros:
 * <dl>
 *    <dt>Identificador del comercio</dt>
 *    <dd>Este identificador es &uacute;nico para cada comercio. Se provee al comercio
 * tras la firma del contrato de utilizaci&oacute;n del sistema de pago. </dd>
 * </dl>
 */

package ssii2.controlador;

import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import ssii2.visa.PagoBean;
import ssii2.visa.dao.VisaDAO;

/**
 *
 * @author phaya
 */
public class GetPagos extends ServletRaiz {
     
    /** 
     * Par&aacute;metro que indica el identificador de comercio
     */
    public final static String PARAM_ID_COMERCIO = "idComercio";

    /** 
     * Par&aacute;metro que indica la ruta de retorno
     */
    public final static String PARAM_RUTA_RETORNO = "ruta";

    /** 
     * Atribute que hace referencia a la lista de pagos
     */
    public final static String ATTR_PAGOS = "pagos";
    
    /** 
    * Procesa una petici&oacute;n HTTP tanto <code>GET</code> como <code>POST</code>.
    * @param request objeto de petici&oacute;n
    * @param response objeto de respuesta
    */    
    protected void processRequest(HttpServletRequest request, HttpServletResponse response)
    throws ServletException, IOException {        
        
		VisaDAO dao = new VisaDAO();
		
		/* Se recoge de la petici&oacute;n el par&aacute;metro idComercio*/  
		String idComercio = request.getParameter(PARAM_ID_COMERCIO);
		
		/* Petici&oacute;n de los pagos para el comercio */
		PagoBean[] pagos = dao.getPagos(idComercio);        

        request.setAttribute(ATTR_PAGOS, pagos);
        reenvia("/listapagos.jsp", request, response);
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
    * Devuelve una descripici&oacute;n abreviada del servlet
    */
    @Override
    public String getServletInfo() {
        return "Servlet Get Pagos";
    }

}
