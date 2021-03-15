<%-- 
    Document   : ObtieneDatosVisa
    Created on : Jan 23, 2010, 7:47:05 PM
    Author     : phaya
--%>

<jsp:include page="cabecera.jsp"/>

<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>

	<h2>Proceso de un pago</h2>
        <form action="procesapago" method="POST">   
            <table>
				<tr>
                    <td>Id Transacci&oacute;n: </td>
                    <td><input type="text" name="idTransaccion" maxlength="4" size="4" /></td>
                </tr>
                <tr>
                    <td>Id Comercio: </td>
                    <td><input type="text" name="idComercio" maxlength="4" size="4" /></td>
                </tr>
                <tr>
                    <td>Importe: </td>
                    <td><input type="text" name="importe" maxlength="4" size="4" /></td>
                </tr>                
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
				<tr>
                    <td>Modo debug: </td>
                    <td><input type="radio" name="debug" value="true" /> True <input type="radio" name="debug" value="false" /> False</td>
                </tr>
				<tr>
                    <td>Direct Connection: </td>
                    <td><input type="radio" name="directConnection" value="true" /> True <input type="radio" name="directConnection" value="false" /> False</td>
                </tr>
				<tr>
                    <td>Use Prepared: </td>
                    <td><input type="radio" name="usePrepared" value="true" /> True <input type="radio" name="usePrepared" value="false" /> False</td>
                </tr>
                <tr><td colspan="2"><input type="submit" value="Pagar" name="EnviarPago" /></td></tr>                
            </table>
			<input type="hidden" name="ruta" value="/testbd.jsp" />			
            <hr/>            
        </form>
		
		<h2>Consulta de pagos</h2>
		<form action="getpagos" method="POST">  
			<table>
				<tr>
                    <td>Id Comercio: </td>
                    <td><input type="text" name="idComercio" maxlength="4" size="4" /></td>
                </tr>		
				<tr><td colspan="2"><input type="submit" value="GetPagos" name="Recuperar pagos" /></td></tr>                
            </table>
			
			<input type="hidden" name="ruta" value="/testbd.jsp" />
			<input type="hidden" name="debug" value="false" />
			<input type="hidden" name="directConnection" value="false" />
			<input type="hidden" name="usePrepared" value="true" />
            <hr/>            
        </form>
		
		<h2>Borrado de pagos</h2>	
		<form action="delpagos" method="POST">  
			<table>
				<tr>
                    <td>Id Comercio: </td>
                    <td><input type="text" name="idComercio" maxlength="4" size="4" /></td>
                </tr>		
				<tr><td colspan="2"><input type="submit" value="DelPagos" name="Borrar pagos" /></td></tr>                
            </table>
			
			<input type="hidden" name="ruta" value="/testbd.jsp" />
			<input type="hidden" name="debug" value="true" />
			<input type="hidden" name="directConnection" value="false" />
			<input type="hidden" name="usePrepared" value="true" />
            <hr/>            
        </form>

<%@ include file="pie.html" %>
