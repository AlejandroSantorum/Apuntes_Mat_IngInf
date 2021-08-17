function validarNombre(nombre) {
	return(nombre.trim().length >= 2);
}

function validarEdad(edad) {
	// isInteger a partir de ECMAScript 6. Antes debía validarse combinando isNan y parseInt
	return((edad != "") && Number.isInteger(Number(edad)));
}

function validarCorreo(correo) {
	// Nos lo podríamos currar un poco más, pero con esto es suficiente
	return((correo.indexOf("@") > 0) && (correo.lastIndexOf("@") < correo.length-1) && (correo.indexOf("@") == correo.lastIndexOf("@")));
}

function validar(formulario) {
	var retorno = true;
	var msj = "";
	
	if(! validarNombre(formulario["fnombre"].value)) 
	{
		formulario["fnombre"].focus();
		retorno = false;
		msj += "Escriba al menos 2 caracteres en el campo \"Nombre\".";
	}
	
	if(! validarEdad(formulario["fedad"].value)) 
	{
		if(retorno) 
		{
			formulario["fedad"].focus();
			retorno = false;
		}
		else msj += "\n";
		msj += "El campo \"Edad\" debe ser un n\u00FAmero entero.";
	}
	
	if(! validarCorreo(formulario["femail"].value)) 
	{
		if(retorno) 
		{
			formulario["femail"].focus();
			retorno = false;
		}
		else msj += "\n";
		msj += "Escriba una direcci\u00F3n de correo v\u00E1lida en el campo \"Email\".";
	}
	
	if(! retorno) alert(msj);
	
	return(retorno);	
}