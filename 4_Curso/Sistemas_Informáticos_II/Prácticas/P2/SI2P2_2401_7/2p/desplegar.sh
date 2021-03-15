#!/usr/bin/env bash

for i in P1-base P1-ws P1-ejb-servidor-remoto P1-ejb-cliente-remoto; do
    cd $i
    ant replegar; ant delete-pool-local
    cd -
done
cd P1-base
ant delete-db
cd -
for i in P1-base P1-ws P1-ejb-servidor-remoto P1-ejb-cliente-remoto; do
    cd $i
    ant limpiar-todo todo
    cd -
done
