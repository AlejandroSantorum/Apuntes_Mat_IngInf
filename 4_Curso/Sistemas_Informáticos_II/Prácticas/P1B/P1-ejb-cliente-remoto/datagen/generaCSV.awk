# Generacion de datos aleatorios para P2
# SSII2, 2010-2011
#
# jaime.lopez@uam.es
# Uso: gawk -vPCTERR=X -vNOUT=Y -fgeneraCSV.awk  nombres.txt apellidos.txt
# NOUT     : Numero de registros a generar
# PCTERR=X : %ruido
#
BEGIN {
  ANIO_INI=(ANIO_INI+0>0?ANIO_INI+0:9)  # 2009 (+-margen) por defecto
  ANIO_FIN=(ANIO_FIN+0>0?ANIO_FIN+0:13) # 2013 (+-margen) por defecto
  MARGEN_INI=2.0
  MARGEN_FIN=2.0
  NOUT = (NOUT+0>0?NOUT+0:1000);
  nn = na = 0;
  PCTERR=(PCTERR+0>0?PCTERR+0:0);
  PCTOK=100-PCTERR;
  srand();
}

(FILENAME=="nombres.txt") {
  N[nn++] = $0;
}

(FILENAME=="apellidos.txt") {
  A[na++] = $0;
}

END {
  for (i=1 ; i<=NOUT ; i++) {
    t=rand() ;
    if (PCTERR > 0 && t >= PCTOK/100.0) {
      fe = fc = "00/00"; # Fecha erronea
    }
    else {
      fe = sprintf("%02d/%02d",1+(rand()*11.0),ANIO_INI+(rand()*MARGEN_INI));
      fc = sprintf("%02d/%02d",1+(rand()*11.0),ANIO_FIN+(rand()*MARGEN_FIN));
    }
    a = sprintf("%d",(rand()*nn*1.0)) + 0;
    b = sprintf("%d",(rand()*na*1.0)) + 0;
    c = sprintf("%d",(rand()*na*1.0)) + 0;
    tit = N[a] " " A[b] " " A[c];
    cvv = rand()*999.0;
    t1 = 9999.0 * rand();
    t2 = 9999.0 * rand();
    t3 = 9999.0 * rand();
    t4 = 9999.0 * rand();
    printf ("%s|%04d %04d %04d %04d|%s|%s|%03d|\n",tit,t1,t2,t3,t4,fe,fc,cvv);
  }
}
