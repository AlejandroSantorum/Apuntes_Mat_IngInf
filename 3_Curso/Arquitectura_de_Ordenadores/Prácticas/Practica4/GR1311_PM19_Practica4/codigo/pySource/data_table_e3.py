import sys

# Getting input parameters:
#	- fin = filename of input data
#	- n_reps = number of reps
#	- m_thr = number of threads
#	- size1 = matrix 10 s size
#	- size2 = matrix 1 min size
#	- fout = filename of output data after processing
fin_name = str(sys.argv[1])
n_reps = int(sys.argv[2])
n_thr = int(sys.argv[3])
size1 = int(sys.argv[4])
size2 = int(sys.argv[5])
fout_name = str(sys.argv[6])

# Opening data files
fin = open(fin_name, "r")
lines = fin.readlines()
n_lines = len(lines)
n_lines_per_thr = (n_lines-n_reps)/n_thr
fout = open(fout_name, "w")

# Processing data
ser1 = 0.0
ser2 = 0.0
for i in range(n_reps):
	line = lines[i]
	data = line.split()
	ser1 += float(data[0])
	ser2 += float(data[1])
ser1 /= n_reps
ser2 /= n_reps
fout.write("------------------ I N F O ----------------------\n")
fout.write("MATRIX SIZES: size1 = "+str(size1)+"		size2 = "+str(size2)+"\n")
fout.write("NUMBER OF REPETITIONS: "+str(n_reps)+"\n")
fout.write("-------------------------------------------------\n");
fout.write("STANDARD: time1 = "+str(ser1)+" 		time2 = "+str(ser2)+"\n")

for k in range(n_thr):
	par1_1 = 0.0
	par1_2 = 0.0
	par2_1 = 0.0
	par2_2 = 0.0
	par3_1 = 0.0
	par3_2 = 0.0
	j=0
	while(j<n_lines_per_thr):
		index = n_reps + (k*n_lines_per_thr) + j
		line = lines[index]
		data = line.split()
		par1_1 += float(data[1])
		par1_2 += float(data[2])
		line = lines[index+1]
		data = line.split()
		par2_1 = float(data[1])
		par2_2 = float(data[2])
		line = lines[index+2]
		data = line.split()
		par3_1 = float(data[1])
		par3_2 = float(data[2])
		j += 3

	par1_1 /= n_reps
	par1_2 /= n_reps
	par2_1 /= n_reps
	par2_2 /= n_reps
	par3_1 /= n_reps
	par3_2 /= n_reps

	fout.write("NUMBER OF THREADS for the data below: "+str(k+1)+"\n");
	fout.write("Par1 size1 time = "+str(par1_1)+"		Par1 size2 time = "+str(par1_2)+"\n")
	fout.write("Par2 size1 time = "+str(par2_1)+"		Par2 size2 time = "+str(par2_2)+"\n")
	fout.write("Par3 size1 time = "+str(par3_1)+"		Par3 size2 time = "+str(par3_2)+"\n")
	fout.write("Par1 size1 speedUp = "+str(ser1/par1_1)+"		Par1 size2 speedUp = "+str(ser2/par1_2)+"\n")
	fout.write("Par2 size1 speedUp = "+str(ser1/par2_1)+"		Par2 size2 speedUp = "+str(ser2/par2_2)+"\n")
	fout.write("Par3 size1 speedUp = "+str(ser1/par3_1)+"		Par3 size2 speedUp = "+str(ser2/par3_2)+"\n")

fin.close()
fout.close()