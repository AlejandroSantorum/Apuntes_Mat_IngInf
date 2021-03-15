<%-- 
    Document   : ObtieneDatosVisa
    Created on : Jan 23, 2010, 7:47:05 PM
    Author     : phaya
--%>

<jsp:include page="cabecera.jsp"/>

<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>

<jsp:useBean id="pago" scope="session" class="ssii2.visa.PagoBean" />    
 
        <form action="procesapago" method="POST">   
            <table>
                <tr><td>Numero de visa: </td><td><input type="text" name="numero"  size="16" /></td></tr>                                              
                <c:if test="${not empty requestScope.ErrorVisaNumero}">                   
                  <tr><td colspan="2" class="error">${requestScope.ErrorVisaNumero.textoError}</td></tr>                  
                </c:if>                
                <tr><td>Titular: </td><td><input type="text" name="titular" size="25" /></td></tr>
                <c:if test="${not empty requestScope.ErrorVisaTitular}">                   
                  <tr><td colspan="2" class="error">${requestScope.ErrorVisaTitular.textoError}</td></tr>                  
                </c:if>                
                <tr><td>Fecha Emisi&oacute;n:</td><td><input type="text" name="fechaEmision" maxlength="10" size="10" /></td></tr>
                <c:if test="${not empty requestScope.ErrorVisaFechaEmision}">                   
                  <tr><td colspan="2" class="error">${requestScope.ErrorVisaFechaEmision.textoError}</td></tr>                  
                </c:if>                
                <tr><td>Fecha Caducidad: </td><td><input type="text" name="fechaCaducidad" maxlength="10" size="10" /></td></tr>
                <c:if test="${not empty requestScope.ErrorVisaFechaCaducidad}">                   
                  <tr><td colspan="2" class="error">${requestScope.ErrorVisaFechaCaducidad.textoError}</td></tr>                  
                </c:if>
                <tr><td>CVV2:</td><td><input type="text" name="codigoVerificacion" maxlength="3" size="3" /></td></tr>
                <c:if test="${not empty requestScope.ErrorVisaCVV}">                   
                  <tr><td colspan="2" class="error">${requestScope.ErrorVisaCVV.textoError}</td></tr>                  
                </c:if>
                <tr><td colspan="2"><input type="submit" value="Pagar" name="EnviarPago" /></td></tr>                
            </table>
            <hr/>
            <table>
                <tr><td>Id Transacci&oacute;n:</td><td>${pago.idTransaccion}</td></tr>
                <tr><td>Id Comercion:</td><td>${pago.idComercio}</td></tr>
                <tr><td>Importe:</td><td>${pago.importe}</td></tr>
            </table>
        </form>

<%@ include file="pie.html" %>
