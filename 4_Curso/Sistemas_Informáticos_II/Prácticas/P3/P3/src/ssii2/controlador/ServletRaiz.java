/**
 * Pr&aacute;ctricas de Sistemas Inform&aacute;ticos II
 * 
 * Esta servlet incluye los metodos comunes al resto de los servlet de la
 * aplicaci&oacute;n
 * 
 * Es necesario implementar el m&eacute;todo processRequest para poder heredar
 * de &eacute;l.
 * 
 */

package ssii2.controlador;

import java.io.IOException;
import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 *
 * @author phaya
 */
public abstract class ServletRaiz extends HttpServlet {

    /** 
    * Procesa una petici&oacute;n HTTP tanto <code>GET</code> como <code>POST</code>.
    * @param request objeto de petici&oacute;n
    * @param response objeto de respuesta
    */    
    protected abstract void processRequest(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException;
        
    /** 
    * Procesa a peticiones HTTP <code>GET</code>.
    * @param request objeto de petici&oacute;n
    * @param response objeto de respuesta
    */
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
    throws ServletException, IOException {
        processRequest(request, response);
    } 

    /** 
    * Procesa a peticiones HTTP <code>POST</code>.
    * @param request objeto de petici&oacute;n
    * @param response objeto de respuesta
    */
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
    throws ServletException, IOException {
        processRequest(request, response);
    }

    /**
     * Se encarga redireccoinar un error a la p&aacute;gina correspondiente
     * 
     * @param t excepci&oacute;n que ha producido el error
     * @param request objeto de petici&oacute;n
     * @param response objeto de respuesta
     * @throws javax.servlet.ServletException
     * @throws java.io.IOException
     */
    protected void enviaError(Throwable t, HttpServletRequest request, HttpServletResponse response) 
        throws ServletException, IOException {
        getServletContext().log("[ERROR] :" + t.getMessage());
        request.setAttribute("error", t);
        reenvia("/error/muestraerror.jsp", request, response);
    }
    
    /**
     * Para informar de un error de acceso no autorizado. Este se produce cuando se intenta
     * realizar un peticion con p&aacute;rametro malformados.
     * 
     * @param request objeto de petici&oacute;n
     * @param response objeto de respuesta
     * @throws javax.servlet.ServletException
     * @throws java.io.IOException
     */
    protected void accesoNoAutorizado(HttpServletRequest request, HttpServletResponse response)
        throws ServletException, IOException {
        enviaError(new Exception("Acceso No autorizado"), request, response);        
    }
    
    /**
     * Para informar de errores que no queremos que el usuario sepa su causas
     * 
     * @param request objeto de petici&oacute;n
     * @param response objeto de respuesta
     * @throws javax.servlet.ServletException
     * @throws java.io.IOException
     */
    protected void errorDesconocido(HttpServletRequest request, HttpServletResponse response)
        throws ServletException, IOException {
        enviaError(new Exception("Error desconocido"), request, response);        
    }
    
    /**
     * Permite reenviar una petici&oacute;n a un recurso dentro del contexto 
     * de la aplicaci&oacute;n
     * 
     * @param ruta del recurso
     * @param request objeto de petici&oacute;n
     * @param response objeto de respuesta
     * @throws javax.servlet.ServletException
     * @throws java.io.IOException
     */
    protected void reenvia(String ruta, HttpServletRequest request, HttpServletResponse response)
        throws ServletException, IOException {
        RequestDispatcher jsp;
        jsp = getServletContext().getRequestDispatcher(ruta);
        jsp.forward(request, response);
        return;
    }

    protected void errorLog(String error) {
        getServletContext().log("[ERROR] : " + error);
    }
        
}
