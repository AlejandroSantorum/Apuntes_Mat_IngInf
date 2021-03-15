<%-- 
    Document   : Listado de pagos
    Created on : Feb 8, 2010, 12:33:44 PM
    Author     : phaya
--%>

<jsp:include page="cabecera.jsp"/>

<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>

<%-- Se obtiene la lista de pagos recibida de la request --%>
<jsp:useBean id="pagos" scope="request" class="ssii2.visa.PagoBean[]" />   

<%-- Se utiliza un bean para obtener los datos del pago e imprimirlos como
     comprobación      
     * idTransaccion;
     * idComercio;
     * importe;
     * codRespuesta
     * idAutorizacion 
     * ruta
--%>


        <p>Lista de pagos del comercio <%= request.getParameter("idComercio") %> </p>
        <table border="1">    
		<thead>
            <tr>
				<th>idTransaccion</th>
                <th>Importe</th>
                <th>codRespuesta</th>
				<th>idAutorizacion</th>
			</tr>
		</thead>
		<tbody>
			<c:forEach var="pago" items="${pagos}">
				<tr>
					<td>${pago.idTransaccion}</td>
					<td>${pago.importe}</td>
					<td>${pago.codRespuesta}</td>
					<td>${pago.idAutorizacion}</td>
				</tr>
			</c:forEach>
		</tbody>
		</table>
        
		<p><a href="<c:url value='<%= request.getParameter("ruta") %>'/>">Volver al comercio</a></p>        

<%@ include file="pie.html" %>      