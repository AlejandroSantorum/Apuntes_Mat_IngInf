#!/bin/bash

Ninicial=19216 #10000+1024*9 P=(19%7)+4=9
Nstep=64
Nfinal=20240 #10000+1024*10
Nrep=15
M=$(( ((Nfinal-Ninicial)/Nstep)+1 )) # Number of different matrix sizes
fD=data.dat
fM=files/exercise1/time_slow_fast.dat
fPlot=files/exercise1/time_slow_fast.png

echo "Running script..."

# Delete data and PNG files
rm -f $fPlot $fM

for((i = 1 ; i <= Nrep ; i += 1)); do
	for((N = Ninicial ; N <= Nfinal ; N += Nstep)); do
		echo "N: $N / $Nfinal [Rep Number = $i of $Nrep]..."
		slowTime=$(./csource/slow $N | grep 'time' | awk '{print $3}')
		fastTime=$(./csource/fast $N | grep 'time' | awk '{print $3}')
		echo "$N $slowTime $fastTime" >> $fD
	done
done

# Calculating mean values with python
python ./pythonSource/cal_mean_fast_slow.py $fD $M $fM

echo "Generating plots..."
gnuplot << END_GNUPLOT
set title "Slow-Fast Execution Time"
set ylabel "Execution time (s)"
set xlabel "Matrix size (dim)"
set key left top
set grid
set term png
set output "$fPlot"
plot "$fM" using 1:2 with lines lw 2 title "slow", \
	 "$fM" using 1:3 with lines lw 2 title "fast"
replot
quit
END_GNUPLOT

rm -f $fD

