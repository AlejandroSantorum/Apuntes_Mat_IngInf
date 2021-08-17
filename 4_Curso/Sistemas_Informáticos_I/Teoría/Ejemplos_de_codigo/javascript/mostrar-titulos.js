function mostrarTitulos() {
     document.write("<H1><U>Títulos</U><BR></H1>")
     for (i=1; i<=6; i++){
	document.write("<H" + i + ">Título " + i)
	document.write("</H" + i + "><BR>")
     }
}
