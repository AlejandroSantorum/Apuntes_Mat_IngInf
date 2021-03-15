#!/bin/bash
WHO=`whoami`

if [ "$WHO" != "root" ]; then
  echo "Debes ser root"
  exit 1
fi

IF=$1
if [ "$1" = "" ]; then
  echo "Uso: $0 <if>"
  echo "<if> debe ser una interfaz de red existente en el sistema"
  echo "     y con direccion IP asignada"
  exit 1
fi

IFINFO=`/sbin/ifconfig $IF`
rc=$?

if [ "$rc" != "0" ]; then
  echo "Error obteniendo info de interfaz de red $IF"
  exit 2
fi

export LANG=C
IP=`/sbin/ifconfig $IF  | /usr/bin/perl -ne 'if ( m/^\s*inet (?:addr:)?([\d.]+).*?cast/ ) { print qq($1\n); exit 0; }' | awk -F'.' '{ print "10.10." $3 "." $4 }'`

ifconfig $IF:0 $IP

echo "Direccion $IP asignada interfaz $IF:0"
