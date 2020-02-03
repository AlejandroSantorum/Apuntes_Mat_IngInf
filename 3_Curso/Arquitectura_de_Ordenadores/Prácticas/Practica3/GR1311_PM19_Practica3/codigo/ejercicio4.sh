#!/bin/bash

Ninicial=320 #32+32*9  P=(19%7)+4=9
Nstep=4
Nfinal=352 #32+32*10
Nrep=30
M=$(( ((Nfinal-Ninicial)/Nstep)+1 )) # Number of different matrix sizes
fCachegrind=cachegrind_file_E4.dat
base=1024
head_lines=30
LLsize=8388608 # 8 MB
fD1=data_
fD2=.dat
fM=files/exercise4/data_
fPlotTimes=files/exercise4/mult_times_ex4.png
fPlotMR=files/exercise4/mult_cache_lectura_ex4.png
fPlotMW=files/exercise4/mult_cache_escritura_ex4.png

echo "Running script..."

# Delete data and PNG files
rm -f $fPlotMR $fPlotMW $fPlotTimes $fCachegrind
rm -f files/exercise4/data_1024.dat
rm -f files/exercise4/data_2048.dat
rm -f files/exercise4/data_4096.dat
rm -f files/exercise4/data_8192.dat

for((k = 0 ; k < 4 ; k += 1)); do
	size=$((base*(2**k)))
	for((i = 1 ; i <= Nrep ; i++)); do
		for((N = Ninicial ; N <= Nfinal ; N += Nstep)); do
			echo -e "\nN: $N / $Nfinal [Cache=$size][Rep Number = $i of $Nrep]...\n"
			normalTime=$(valgrind --tool=cachegrind --I1=$size,1,64 --D1=$size,1,64 --LL=$LLsize,1,64 \
					 --cachegrind-out-file=$fCachegrind ./csource/matrix_mult $N | grep 'time' | awk '{print $3}')
			normalMR=$(cg_annotate $fCachegrind | head -n $head_lines | grep 'PROGRAM TOTALS' | awk '{print $5}')
			normalMR="${normalMR//,}"
			normalMW=$(cg_annotate $fCachegrind | head -n $head_lines | grep 'PROGRAM TOTALS' | awk '{print $8}')
			normalMW="${normalMW//,}"
			transTime=$(valgrind --tool=cachegrind --I1=$size,1,64 --D1=$size,1,64 --LL=$LLsize,1,64 \
					 --cachegrind-out-file=$fCachegrind ./csource/transMatrix_mult $N | grep 'time' | awk '{print $3}')
			transMR=$(cg_annotate $fCachegrind | head -n $head_lines | grep 'PROGRAM TOTALS' | awk '{print $5}')
			transMR="${transMR//,}"
			transMW=$(cg_annotate $fCachegrind | head -n $head_lines | grep 'PROGRAM TOTALS' | awk '{print $8}')
			transMW="${transMW//,}"
			echo "$N $normalTime $normalMR $normalMW $transTime $transMR $transMW" >> $fD1$size$fD2
		done
	done
	python ./pythonSource/cal_mean_mult_cache.py $fD1$size$fD2 $M $fM$size$fD2
done

echo "Generating plots..."
gnuplot << END_GNUPLOT
set title "Matrix Multiplication Execution Time"
set ylabel "Execution time (s)"
set xlabel "Matrix size (dim)"
set key left top
set grid
set term png
set output "$fPlotTimes"
plot "files/exercise4/data_1024.dat" using 1:2 with lines lw 2 title "normal - cache=1024", \
	 "files/exercise4/data_1024.dat" using 1:5 with lines lw 2 title "trans - cache=1024", \
	 "files/exercise4/data_2048.dat" using 1:2 with lines lw 2 title "normal - cache=2048", \
	 "files/exercise4/data_2048.dat" using 1:5 with lines lw 2 title "trans - cache=2048", \
	 "files/exercise4/data_4096.dat" using 1:2 with lines lw 2 title "normal - cache=4096", \
	 "files/exercise4/data_4096.dat" using 1:5 with lines lw 2 title "trans - cache=4096", \
	 "files/exercise4/data_8192.dat" using 1:2 with lines lw 2 title "normal - cache=8192", \
	 "files/exercise4/data_8192.dat" using 1:5 with lines lw 2 title "trans - cache=8192"
replot
set output "$fPlotMR"
set title "Matrix Multiplication Reading Miss Rate"
set ylabel "Miss rate (n misses)"
set xlabel "Matrix size (dim)"
set key left top
set grid
set term png
plot "files/exercise4/data_1024.dat" using 1:3 with lines lw 2 title "normal - cache=1024", \
	 "files/exercise4/data_1024.dat" using 1:6 with lines lw 2 title "trans - cache=1024", \
	 "files/exercise4/data_2048.dat" using 1:3 with lines lw 2 title "normal - cache=2048", \
	 "files/exercise4/data_2048.dat" using 1:6 with lines lw 2 title "trans - cache=2048", \
	 "files/exercise4/data_4096.dat" using 1:3 with lines lw 2 title "normal - cache=4096", \
	 "files/exercise4/data_4096.dat" using 1:6 with lines lw 2 title "trans - cache=4096", \
	 "files/exercise4/data_8192.dat" using 1:3 with lines lw 2 title "normal - cache=8192", \
	 "files/exercise4/data_8192.dat" using 1:6 with lines lw 2 title "trans - cache=8192"
replot
set output "$fPlotMW"
set title "Matrix Multiplication Writing Miss Rate"
set ylabel "Miss rate (n misses)"
set xlabel "Matrix size (dim)"
set key left top
set grid
set term png
plot "files/exercise4/data_1024.dat" using 1:4 with lines lw 2 title "normal - cache=1024", \
	 "files/exercise4/data_1024.dat" using 1:7 with lines lw 2 title "trans - cache=1024", \
	 "files/exercise4/data_2048.dat" using 1:4 with lines lw 2 title "normal - cache=2048", \
	 "files/exercise4/data_2048.dat" using 1:7 with lines lw 2 title "trans - cache=2048", \
	 "files/exercise4/data_4096.dat" using 1:4 with lines lw 2 title "normal - cache=4096", \
	 "files/exercise4/data_4096.dat" using 1:7 with lines lw 2 title "trans - cache=4096", \
	 "files/exercise4/data_8192.dat" using 1:4 with lines lw 2 title "normal - cache=8192", \
	 "files/exercise4/data_8192.dat" using 1:7 with lines lw 2 title "trans - cache=8192"
replot
quit
END_GNUPLOT

rm -f data_1024.dat data_2048.dat data_4096.dat data_8192.dat
