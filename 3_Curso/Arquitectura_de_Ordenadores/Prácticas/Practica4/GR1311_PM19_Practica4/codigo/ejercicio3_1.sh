Nrep=5
size1=1220 # obtained empirically
size2=2020 # obtained empirically
MaxThr=$(cat /proc/cpuinfo | grep 'processor' | awk '{print $3}' | tail -1) # maximum number of threads
fDataPre1=files/exercise3/preData_table.dat
fData1=files/exercise3/data_table.dat

rm -f $fData1

# Getting data using standard matrix multiplication
for((i = 1; i <= Nrep ; i += 1)); do
	echo "Standard matrix mult [Rep number = $i]"
	time1=$(./csource/matrix_mult_serie $size1 | grep 'time' | awk '{print $3}')
	time2=$(./csource/matrix_mult_serie $size2 | grep 'time' | awk '{print $3}')
	echo "$time1 $time2" >> $fDataPre1
done

# Getting data using parallelized matrix multiplication versions
for((C = 1; C <= MaxThr ; C += 1)); do
	for((i = 1 ; i <= Nrep ; i += 1)); do
		echo "Threads = $C [Rep number = $i]"
		time1_par1=$(./csource/matrix_mult_par1 $size1 $C | grep 'time' | awk '{print $3}')
		time2_par1=$(./csource/matrix_mult_par1 $size2 $C | grep 'time' | awk '{print $3}')
		echo "$C $time1_par1 $time2_par1" >> $fDataPre1
		time1_par2=$(./csource/matrix_mult_par2 $size1 $C | grep 'time' | awk '{print $3}')
		time2_par2=$(./csource/matrix_mult_par2 $size2 $C | grep 'time' | awk '{print $3}')
		echo "$C $time1_par2 $time2_par2" >> $fDataPre1
		time1_par3=$(./csource/matrix_mult_par3 $size1 $C | grep 'time' | awk '{print $3}')
		time2_par3=$(./csource/matrix_mult_par3 $size2 $C | grep 'time' | awk '{print $3}')
		echo "$C $time1_par3 $time2_par3" >> $fDataPre1
	done
done

# Processing data
python ./pySource/data_table_e3.py $fDataPre1 $Nrep $MaxThr $size1 $size2 $fData1

rm -f $fDataPre1