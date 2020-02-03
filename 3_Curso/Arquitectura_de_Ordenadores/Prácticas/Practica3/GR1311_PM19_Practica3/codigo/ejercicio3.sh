#!/bin/bash

Ninicial=640 #64+64*9 P=(19%7)+4=9
Nstep=16
Nfinal=704 #64+64*10
Nrep=40
M=$(( ((Nfinal-Ninicial)/Nstep)+1 )) # Number of different matrix sizes
fCachegrind=cachegrind_file_E3.dat
base=1024
head_lines=30
LLsize=8388608 # 8 MB
fT=times.dat
fC=cache.dat
fM=files/exercise3/mult.dat
fPlotTimes=files/exercise3/mult_time.png
fPlotMR=files/exercise3/mult_cache_lectura.png
fPlotMW=files/exercise3/mult_cache_escritura.png

echo "Running script..."

# Delete data and PNG files
rm -f $fPlotTimes $fPlotMW $fPlotMR $fM

echo "Getting execution times..."
for((i = 1 ; i <= Nrep ; i += 1)); do
	for((N = Ninicial ; N <= Nfinal ; N += Nstep)); do
		echo "N: $N / $Nfinal [Rep Number = $i of $Nrep]..."
		normalTime=$(./csource/matrix_mult $N | grep 'time' | awk '{print $3}')
		transTime=$(./csource/transMatrix_mult $N | grep 'time' | awk '{print $3}')
		echo "$N $normalTime $transTime" >> $fT
	done
done

echo "Getting cache misses..."
for((N = Ninicial ; N <= Nfinal ; N += Nstep)); do
	echo "N: $N / $Nfinal..."
	valgrind --tool=cachegrind --cachegrind-out-file=$fCachegrind ./csource/matrix_mult $N &>/dev/null
	normalMR=$(cg_annotate $fCachegrind | head -n $head_lines | grep 'PROGRAM TOTALS' | awk '{print $5}')
	normalMR="${normalMR//,}"
	normalMW=$(cg_annotate $fCachegrind | head -n $head_lines | grep 'PROGRAM TOTALS' | awk '{print $8}')
	normalMW="${normalMW//,}"
	valgrind --tool=cachegrind --cachegrind-out-file=$fCachegrind ./csource/transMatrix_mult $N &>/dev/null
	transMR=$(cg_annotate $fCachegrind | head -n $head_lines | grep 'PROGRAM TOTALS' | awk '{print $5}')
	transMR="${transMR//,}"
	transMW=$(cg_annotate $fCachegrind | head -n $head_lines | grep 'PROGRAM TOTALS' | awk '{print $8}')
	transMW="${transMW//,}"
	echo "$N $normalMR $normalMW $transMR $transMW" >> $fC
done

# Calculating mean values and putting all together with python
python ./pythonSource/cal_mean_matrix_mult.py $fT $fC $M $fM

echo "Generating plots..."
gnuplot << END_GNUPLOT
set title "Normal-Trans Mult Execution Times"
set ylabel "Execution time (s)"
set xlabel "Matrix size (dim)"
set key left top
set grid
set term png
set output "$fPlotTimes"
plot "$fM" using 1:2 with lines lw 2 title "normal", \
	 "$fM" using 1:5 with lines lw 2 title "trans"
replot
set output "$fPlotMR"
set title "Normal-Trans Reading Miss Rate"
set ylabel "Miss rate (n misses)"
set xlabel "Matrix size (dim)"
set key left top
set grid
set term png
plot "$fM" using 1:3 with lines lw 2 title "normal", \
	 "$fM" using 1:6 with lines lw 2 title "trans"
replot
set output "$fPlotMW"
set title "Normal-Trans Writing Miss Rate"
set ylabel "Miss rate (n misses)"
set xlabel "Matrix size (dim)"
set key left top
set grid
set term png
plot "$fM" using 1:4 with lines lw 2 title "normal", \
	 "$fM" using 1:7 with lines lw 2 title "trans"
replot
quit
END_GNUPLOT

rm -f $fC $fT $fCachegrind

