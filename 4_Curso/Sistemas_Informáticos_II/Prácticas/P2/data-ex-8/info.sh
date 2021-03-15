#!/usr/bin/env bash
echo CPU:
for i in 1 250 500 750 1000 1250 1500 1750 2000 2250 2500
do
    tail -1 $i\u/cpu-vm.txt | awk '{print $4}'
done
echo Monitorization:
for i in 1 250 500 750 1000 1250 1500 1750 2000 2250 2500
do
    tail -1 $i\u/monitor.txt | awk '{printf ("%12s\t%12s\t%12s\n", $2, $3, $4)}'
done
