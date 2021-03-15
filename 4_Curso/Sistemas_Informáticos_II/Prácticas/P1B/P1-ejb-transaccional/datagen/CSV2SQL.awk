BEGIN { IFS=OFS=FS="|" }
{
  printf("INSERT INTO tarjeta(numeroTarjeta,titular,validaDesde,validaHasta,codigoVerificacion) ");
  printf("VALUES ('" $2 "','" $1 "','" $3 "','" $4 "','" $5 "');\n");
}
