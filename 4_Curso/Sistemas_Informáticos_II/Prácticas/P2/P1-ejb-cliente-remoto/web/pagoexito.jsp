<%-- 
    Document   : OperacionExito
    Created on : Feb 8, 2010, 12:33:44 PM
    Author     : phaya
--%>

<jsp:include page="cabecera.jsp"/>

<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>

<%-- Se utiliza un bean para obtener los datos del pago e imprimirlos como
     comprobación      
     * idTransaccion;
     * idComercio;
     * importe;
     * codRespuesta
     * idAutorizacion 
     * ruta
--%>
<jsp:useBean id="pago" scope="request" class="ssii2.visa.PagoBean" />   

        <p>Pago realizado con &eacute;xito. A continuaci&oacute;n se muestra el 
        comprobante del mismo:</p> 
        <table>    
            <tr><td>idTransaccion:</td><td>${pago.idTransaccion}</td></tr>
            <tr><td>idComercio:</td><td>${pago.idComercio}</td></tr>
            <tr><td>importe:</td><td>${pago.importe}</td></tr>
            <tr><td>codRespuesta:</td><td>${pago.codRespuesta}</td></tr>
            <tr><td>idAutorizacion:</td><td>${pago.idAutorizacion}</td></tr>
        </table>
        <p><a href="<c:url value='${pago.rutaRetorno}'/>">Volver al comercio</a></p>        

<%@ include file="pie.html" %>      