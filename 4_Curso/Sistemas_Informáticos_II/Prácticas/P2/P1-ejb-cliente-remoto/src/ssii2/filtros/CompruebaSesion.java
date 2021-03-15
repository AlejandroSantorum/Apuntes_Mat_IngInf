/**
 * Pr&aacute;ctricas de Sistemas Inform&aacute;ticos II
 * 
 * Filtro que se encarga de verificar que la sesi&oacute;n ha sido inicializada
 * correctamente.
 * 
 */

package ssii2.filtros;

import java.io.IOException;
import javax.servlet.Filter;
import javax.servlet.FilterChain;
import javax.servlet.FilterConfig;
import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.ServletRequest;
import javax.servlet.ServletResponse;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;
import ssii2.controlador.ComienzaPago;
import ssii2.visa.PagoBean;

/**
 *
 * @author phaya
 */
public class CompruebaSesion implements Filter {

    private String excluidas[];
    
    private FilterConfig filterconfig = null;
       
    /**
     * Procesa la inicializaci&oacute;n del filtro. Se a&ntilde;aden los 
     * par&aacute;metros de inicializaci&oacute;n del archivo web.xml 
     * 
     * @param fc objeto con la configuraci&oacute;n del filtro. 
     */
    public void init(FilterConfig fc) {        
        this.filterconfig = fc;
        String s = this.filterconfig.getInitParameter("rutasexcluidas");
        excluidas = s.split(",");
        
    }
    
    /**
     * M&eacute;todo que se llama en la destrucci&oacute;n del filtro.
     */      
    public void destroy() {
        /* Destruccion del filtro */
        this.filterconfig = null;
    }
    
    /**
     * Procesa cada petici&oacute;n que recibe el filtro.
     * @param request
     * @param response
     * @param chain
     * @throws java.io.IOException
     * @throws javax.servlet.ServletException
     */
    public void doFilter(ServletRequest request, ServletResponse response, FilterChain chain)  
    throws IOException, ServletException { 
        
        String URI = ((HttpServletRequest)request).getServletPath();
        boolean excluida = false;
        for (String r : excluidas) {
            if (URI.equals(r)) {
                excluida = true;
            }
        }
        if (!excluida) {
            HttpSession session = ((HttpServletRequest)request).getSession(false);
            if (session != null) {
                PagoBean pago = (PagoBean) session.getAttribute(ComienzaPago.ATTR_PAGO);
                if (pago == null) {
                    muestraerror(URI, request, response);
                    return;                    
                }
            } else {
                muestraerror(URI, request, response);
                return;
            }
        }
        this.filterconfig.getServletContext().log("[INFO] Acceso correcto:" + URI);    
        chain.doFilter(request, response);
    }
    
    /**
     * Redirige a una p&aacute;gina de error en caso de que se produzca un 
     * acceso no autorizado.
     * 
     * @param ruta del recurso que se ha intentado acceder sin autorizaci&oacute;n
     * @param request objeto de petici&oacute;n
     * @param response objeto de respuesta
     * @throws javax.servlet.ServletException
     * @throws java.io.IOException
     */
    private void muestraerror(String ruta, ServletRequest request, ServletResponse response) 
        throws ServletException, IOException {        
        this.filterconfig.getServletContext().log("[WARNING] Acceso No autorizado:" + ruta);
        reenvia("/error/muestraerror.jsp", request, response);
    }
    
    /**
     * Reenvia una petici&oacute;n a un recurso dentro del contexto 
     * de la aplicaci&oacute;n
     * @param ruta del recurso
     * @param request objeto de petici&oacute;n
     * @param response objeto de respuesta
     * @throws javax.servlet.ServletException
     * @throws java.io.IOException
     */
    private void reenvia(String ruta, ServletRequest request, ServletResponse response)
        throws ServletException, IOException {
        RequestDispatcher jsp;
        jsp = this.filterconfig.getServletContext().getRequestDispatcher(ruta);
        request.setAttribute("error", new Exception("Acceso No autorizado detectado en filtro"));
        jsp.forward(request, response);
        return;
    }
}
