#!/bin/bash
# si2-monitor
# Practicas SI2, 2012
# Monitorizacion de parametros interesantes
# del servidor de aplicaciones
# Jaime Lopez (jaime.lopez@uam.es)

# Parametros a monitorizar
MONITORS="server.resources.VisaPool.numconnused-current
          server.network.http-listener-1.thread-pool.currentthreadsbusy-count
          server.network.http-listener-1.connection-queue.countqueued-count"

GFUSER=admin
GFPASSFILE=./passwordfile
# descomentar si se lanza desde la VM
# GFPASSFILE=/opt/SI2/passwordfile
SLEEP=1
LOGFILE=/tmp/$$.log

#set -x

# Funcion de impresion de la media
function Salida() {
  echo ""
  LOGFILE=$1
  cat $LOGFILE | awk '{
     accJDBCCount += $2+0;
     accHTTPCount += $3+0;
     accHTTPQ     += $4+0;
    }
    END {
     printf "%12s %12s:\n","TOT.MUESTRAS","MEDIA";
     printf "%12s %12s %12s %12s\n", NR,accJDBCCount/NR,accHTTPCount/NR, accHTTPQ/NR;
     fflush();
  }'

  #kill $PIDS
  rm $LOGFILE
}
#set -x

#########################################

if [ "$#" != "1" ]; then
  echo "Uso: $0 <host>"
  exit 1
fi
HOST=$1

#########################################
trap 'Salida $LOGFILE ; ' EXIT
MON=`echo $MONITORS | sed 's/ / -e /g'`

printf "%12s %12s %12s %12s\n" "#Muestra" "numJDBCCount" "numHTTPCount"  "numHTTPQ";
while true ; do
  sleep $SLEEP
  echo "" | awk -vMONITORS="$MONITORS" '{
     $0 = MONITORS;
     for (i=1;i<=NF;i++) {
        print "get -m " $i
        fflush();
     }
  }'
done |
asadmin --host $HOST --user $GFUSER --passwordfile $GFPASSFILE |
mawk -W interactive -vLOGFILE=$LOGFILE '
    BEGIN {
      numJDBCCount = numHTTPCount = numHTTPQ = -1;
    }
    /server.resources.VisaPool.numconnused-current/ {
        numJDBCCount = $3+0 ; next
    }
    /server.network.http-listener-1.thread-pool.currentthreadsbusy-count/ {
        numHTTPCount = $3+0 ; next
    }
    /server.network.http-listener-1.connection-queue.countqueued-count/ {
        numHTTPQ     = $3+0 ;
        if (numHTTPCount >= 0 && numHTTPQ >= 0 ) { # && numJDBCCount >= 0 ) {
          printf("%12s %12s %12s %12s\n", N++, numJDBCCount,numHTTPCount, numHTTPQ);
          numJDBCCount = numHTTPCount = numHTTPQ = -1;
        }
    }
  ' | tee $LOGFILE
