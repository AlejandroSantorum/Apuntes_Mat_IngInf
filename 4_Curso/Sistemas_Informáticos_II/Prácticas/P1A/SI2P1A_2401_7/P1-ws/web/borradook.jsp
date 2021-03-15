<%-- 
    Document   : Listado de pagos
    Created on : Feb 8, 2010, 12:33:44 PM
    Author     : phaya
--%>

<jsp:include page="cabecera.jsp"/>

<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>

    <p>Se han borrado <%= request.getAttribute("borrados") %> pagos correctamente para el comercio <%= request.getParameter("idComercio") %> </p>
    <p><a href="<c:url value='<%= request.getParameter("ruta") %>'/>">Volver al comercio</a></p>        

<%@ include file="pie.html" %>      