#!/bin/bash

minSize=3000000   # 3*10^6 -> obtained empirically
maxSize=300000000 # 3*10^8 -> obtained empirically
M=5 # Number of size samples
step=$(( (maxSize - minSize)/(M-1) ))
Nrep=2
fPreDataSerie=files/exercise2/preDataSerieE2.dat
fPreDataPar=files/exercise2/preDataParE2.dat
fD2=.dat
fData=files/exercise2/dataE2_
fPlotTime=files/exercise2/times_serie_par2.png
fPlotAcc=files/exercise2/acc_serie_par2.png
cores_1=$(cat /proc/cpuinfo | grep 'processor' | awk '{print $3}' | tail -1) # Getting number of cores
CPUCores=$((cores_1 += 1)) # Cores are listed from 0 to n-1

# Removing previos data files
rm -f $fPlotTime $fPlotAcc
for((i = 0 ; i <= CPUCores ; i += 1)); do
	rm -f $fData$i$fD2
done

echo "Maximum number of cores available: $CPUCores"

# Getting data using non-optimized escalar prod
for((i = 1 ; i <= Nrep ; i += 1)); do
	for((size = minSize ; size <= maxSize ; size += step)); do
		echo "Size = $size [rep num: $i]"
		time=$(./csource/pescalar_serie $size | grep 'Tiempo' | awk '{print $2}')
		echo "$size $time" >> $fPreDataSerie
	done
done

# Getting data using parallelized escalar prod
for((C = 1 ; C <= CPUCores ; C += 1)); do
	for((i = 1 ; i <= Nrep ; i += 1)); do
		for((size = minSize ; size <= maxSize ; size += step)); do
			echo "Size = $size [rep num: $i || nCores: $C]"
			time=$(./csource/pescalar_par2 $size $C| grep 'Tiempo' | awk '{print $2}')
			echo "$C $size $time" >> $fPreDataPar
		done
	done
done

# Processing data with python
python ./pySource/handle_data_e2.py $fPreDataSerie $fPreDataPar $M $CPUCores $fData $fD2


echo "Generating plots..."
gnuplot << END_GNUPLOT
set title "Standard-Paralellized Mult Vector Execution Time"
set ylabel "Execution time (s)"
set xlabel "Vector size (n coords)"
set key left top
set grid
set term png
set output "$fPlotTime"
plot for [j=0:$CPUCores] "$fData".j."$fD2" using 1:2 with lines lw 2 title "CPU Cores = ".j
replot
set output "$fPlotAcc"
set title "Standard-Paralellized Mult Vector SpeedUp"
set ylabel "Speed Up (adim)"
set xlabel "Vector size (n coords)"
set key left top
set grid
set term png
plot for [j=1:$CPUCores] "$fData".j."$fD2" using 1:3 with lines lw 2 title "CPU Cores = ".j
replot
quit
END_GNUPLOT

rm -f $fPreDataSerie $fPreDataPar
