#!/bin/bash

Ninicial=640 #64+64*9 P=(19%7)+4=9
Nstep=8
Nfinal=704 #64+64*10
V=8 # Max asoc.
M=$(( ((Nfinal-Ninicial)/Nstep)+1 )) # Number of different matrix sizes
fCachegrind=cachegrind_file_E4.dat
size=8192
head_lines=30
LLsize=8388608 # 8 MB
fD2=.dat
fM=files/exercise4_2/data_
fPlotMR=files/exercise4_2/mult_cacheNvias_lectura_ex4.png
fPlotMW=files/exercise4_2/mult_cacheNvias_escritura_ex4.png

echo "Running script..."

# Delete data and PNG files
rm -f $fPlotMR $fPlotMW
rm -f files/exercise4_2/data_2.dat files/exercise4_2/data_4.dat files/exercise4_2/data_8.dat


for((n_v = 2 ; n_v <= V ; n_v *= 2)); do
	for((N = Ninicial ; N <= Nfinal ; N += Nstep)); do
		echo -e "\nN: $N / $Nfinal [Asoc=$n_v]...\n"
		valgrind --tool=cachegrind --I1=$size,$n_v,64 --D1=$size,$n_v,64 --LL=$LLsize,$n_v,64 \
					 	 --cachegrind-out-file=$fCachegrind ./csource/matrix_mult $N &>/dev/null
		normalMR=$(cg_annotate $fCachegrind | head -n $head_lines | grep 'PROGRAM TOTALS' | awk '{print $5}')
		normalMR="${normalMR//,}"
		normalMW=$(cg_annotate $fCachegrind | head -n $head_lines | grep 'PROGRAM TOTALS' | awk '{print $8}')
		normalMW="${normalMW//,}"
		valgrind --tool=cachegrind --I1=$size,$n_v,64 --D1=$size,$n_v,64 --LL=$LLsize,$n_v,64 \
				 		 --cachegrind-out-file=$fCachegrind ./csource/transMatrix_mult $N &>/dev/null
		transMR=$(cg_annotate $fCachegrind | head -n $head_lines | grep 'PROGRAM TOTALS' | awk '{print $5}')
		transMR="${transMR//,}"
		transMW=$(cg_annotate $fCachegrind | head -n $head_lines | grep 'PROGRAM TOTALS' | awk '{print $8}')
		transMW="${transMW//,}"
		echo "$N $normalMR $normalMW $transMR $transMW" >> $fM$n_v$fD2
	done
done

echo "Generating plots..."
gnuplot << END_GNUPLOT
set title "Normal-Trans Mult Reading Miss Rate"
set ylabel "Miss rate (n misses)"
set xlabel "Matrix size (dim)"
set key left top
set grid
set term png
set output "$fPlotMR"
plot "files/exercise4_2/data_2.dat" using 1:2 with lines lw 2 title "normal - asoc=2", \
	   "files/exercise4_2/data_2.dat" using 1:4 with lines lw 2 title "trans - asoc=2", \
	   "files/exercise4_2/data_4.dat" using 1:2 with lines lw 2 title "normal - asoc=4", \
	   "files/exercise4_2/data_4.dat" using 1:4 with lines lw 2 title "trans - asoc=4", \
	   "files/exercise4_2/data_8.dat" using 1:2 with lines lw 2 title "normal - asoc=8", \
	   "files/exercise4_2/data_8.dat" using 1:4 with lines lw 2 title "trans - asoc=8"
replot
set output "$fPlotMW"
set title "Normal-Trans Mult Writing Miss Rate"
set ylabel "Miss rate (n misses)"
set xlabel "Matrix size (dim)"
set key left top
set grid
set term png
plot "files/exercise4_2/data_2.dat" using 1:3 with lines lw 2 title "normal - asoc=2", \
	   "files/exercise4_2/data_2.dat" using 1:5 with lines lw 2 title "trans - asoc=2", \
	   "files/exercise4_2/data_4.dat" using 1:3 with lines lw 2 title "normal - asoc=4", \
	   "files/exercise4_2/data_4.dat" using 1:5 with lines lw 2 title "trans - asoc=4", \
	   "files/exercise4_2/data_8.dat" using 1:3 with lines lw 2 title "normal - asoc=8", \
	   "files/exercise4_2/data_8.dat" using 1:5 with lines lw 2 title "trans - asoc=8"
replot
quit
END_GNUPLOT

rm -f $fCachegrind