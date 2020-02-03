#!/bin/bash

values=(1 2 4 6 7 8 9 10 12)
size=9
fD=files/exercise4/data_ex4_5.dat
fPlot=files/exercise4/paddings_graph.png

rm -f $fD $fPlot

for((i = 0 ; i < $size ; i += 1)); do
	echo "Padding = ${values[i]}"
	time=$(./csource/pi_par3_mod ${values[5]} | grep 'Tiempo' | awk '{print $2}')
	echo "${values[i]} $time" >> $fD
done

echo "Generating plots..."
gnuplot << END_GNUPLOT
set title "Exercise 4 part 5 - Different padding test"
set ylabel "Execution time (s)"
set xlabel "Padding size (bytes)"
set key left top
set grid
set term png
set output "$fPlot"
plot "$fD" using 1:2 with lines lw 2  title "Pi Par3 Mod"
quit
END_GNUPLOT