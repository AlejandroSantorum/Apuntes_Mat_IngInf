#!/bin/bash

Ninicial=11216 #2000+1024*9  P=(19%7)+4=9
Nstep=64
Nfinal=12240 #2000+1024*10
M=$(( ((Nfinal-Ninicial)/Nstep)+1 )) # Number of different matrix sizes
fCachegrind=cachegrind_file_E2.dat
fD=.dat
fM=files/exercise2/cache_
base=1024
head_lines=30
LLsize=8388608 # 8 MB
fPlotMR=files/exercise2/cache_lectura.png
fPlotMW=files/exercise2/cache_escritura.png

echo "Running script..."

# Delete data and PNG files
rm -f $fPlotMR $fPlotMW
rm -f files/exercise2/cache_1024.dat
rm -f files/exercise2/cache_2048.dat
rm -f files/exercise2/cache_4096.dat
rm -f files/exercise2/cache_8192.dat

for((k = 0 ; k < 4 ; k += 1)); do
	size=$((base*(2**k)))
	for ((N = Ninicial ; N <= Nfinal ; N += Nstep)); do
		echo "N: $N / $Nfinal [Cache=$size]..."
		valgrind --tool=cachegrind --I1=$size,1,64 --D1=$size,1,64 --LL=$LLsize,1,64 \
				 --cachegrind-out-file=$fCachegrind ./csource/slow $N &>/dev/null
		slowMR=$(cg_annotate $fCachegrind | head -n $head_lines | grep 'PROGRAM TOTALS' | awk '{print $5}')
		slowMR="${slowMR//,}"
		slowMW=$(cg_annotate $fCachegrind | head -n $head_lines | grep 'PROGRAM TOTALS' | awk '{print $8}')
		slowMW="${slowMW//,}"
		valgrind --tool=cachegrind --I1=$size,1,64 --D1=$size,1,64 --LL=$LLsize,1,64 \
				 --cachegrind-out-file=$fCachegrind ./csource/fast $N &>/dev/null
		fastMR=$(cg_annotate $fCachegrind | head -n $head_lines | grep 'PROGRAM TOTALS'| awk '{print $5}')
		fastMR="${fastMR//,}"
		fastMW=$(cg_annotate $fCachegrind | head -n $head_lines | grep 'PROGRAM TOTALS' | awk '{print $8}')
		fastMW="${fastMW//,}"
		echo "$N $slowMR $slowMW $fastMR $fastMW" >> $fM$size$fD
	done
done

echo "Generating plots..."
gnuplot << END_GNUPLOT
set title "Slow-Fast Reading Miss Rate"
set ylabel "Miss rate (n misses)"
set xlabel "Matrix size (dim)"
set key left top
set grid
set term png
set output "$fPlotMR"
plot "files/exercise2/cache_1024.dat" using 1:2 with lines lw 2 title "slow - cache size=1024", \
		"files/exercise2/cache_1024.dat" using 1:4 with lines lw 2 title "fast - cache size=1024", \
		"files/exercise2/cache_2048.dat" using 1:2 with lines lw 2 title "slow - cache size=2048", \
		"files/exercise2/cache_2048.dat" using 1:4 with lines lw 2 title "fast - cache size=2048", \
		"files/exercise2/cache_4096.dat" using 1:2 with lines lw 2 title "slow - cache size=4096", \
		"files/exercise2/cache_4096.dat" using 1:4 with lines lw 2 title "fast - cache size=4096", \
		"files/exercise2/cache_8192.dat" using 1:2 with lines lw 2 title "slow - cache size=8192", \
		"files/exercise2/cache_8192.dat" using 1:4 with lines lw 2 title "fast - cache size=8192"
replot
set output "$fPlotMW"
set title "Slow-Fast Writing Miss Rate"
set ylabel "Miss rate (n misses)"
set xlabel "Matrix size (dim)"
set key left top
set grid
set term png
plot "files/exercise2/cache_1024.dat" using 1:3 with lines lw 2 title "slow - cache size=1024", \
		"files/exercise2/cache_1024.dat" using 1:5 with lines lw 2 title "fast - cache size=1024", \
		"files/exercise2/cache_2048.dat" using 1:3 with lines lw 2 title "slow - cache size=2048", \
		"files/exercise2/cache_2048.dat" using 1:5 with lines lw 2 title "fast - cache size=2048", \
		"files/exercise2/cache_4096.dat" using 1:3 with lines lw 2 title "slow - cache size=4096", \
		"files/exercise2/cache_4096.dat" using 1:5 with lines lw 2 title "fast - cache size=4096", \
		"files/exercise2/cache_8192.dat" using 1:3 with lines lw 2 title "slow - cache size=8192", \
		"files/exercise2/cache_8192.dat" using 1:5 with lines lw 2 title "fast - cache size=8192"
replot
quit
END_GNUPLOT

# Removing data files (but no mean values files)
rm -f $fCachegrind
