<%-- 
    Document   : muestraerror
    Created on : Feb 16, 2010, 10:33:29 PM
    Author     : phaya
--%>

<jsp:include page="../cabecera.jsp"/>

<jsp:useBean id="error" scope="request" class="java.lang.Exception" />

<p>${error.message}</p>

<%@ include file="../pie.html" %>      