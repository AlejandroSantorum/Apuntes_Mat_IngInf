import sys

# Getting input parameters
#	- filename_in = filename of the input values (for each line: matrix_size slow_exec_time fast_exec_time)
#	- M = number of different matrix sizes (i.e. ((Nfinal-Ninicial)/Nstep)+1)
#	- filename_out = filename of the mean values fo each matrix size
filename_in = str(sys.argv[1])
M = int(sys.argv[2])
filename_out = str(sys.argv[3])

# Initializing data arrays
array_sizes = []
array_normal_times = []
array_normalMR = []
array_normalMW = []
array_trans_times = []
array_transMR = []
array_transMW = []
for i in range(M):
	array_sizes.append(0)
	array_normal_times.append(0)
	array_normalMR.append(0)
	array_normalMW.append(0)
	array_trans_times.append(0)
	array_transMR.append(0)
	array_transMW.append(0)

# Reading data
file_in = open(filename_in, "r")
lines = file_in.readlines()
n_lines = len(lines)
i = 0
for line in lines:
	data = line.split()
	array_sizes[i] = int(data[0])
	array_normal_times[i] = float(data[1])
	array_normalMR[i] += float(data[2])
	array_normalMW[i] += float(data[3])
	array_trans_times[i] = float(data[4])
	array_transMR[i] += float(data[5])
	array_transMW[i] += float(data[6])
	i = (i+1)%M

# Calculating mean values
n_sums = (n_lines/M)
for i in range(M):
	array_normal_times[i] /= n_sums
	array_normalMR[i] /= n_sums
	array_normalMW[i] /= n_sums
	array_trans_times[i] /= n_sums
	array_transMR[i] /= n_sums
	array_transMW[i] /= n_sums

# Saving mean values into the specified file
file_out = open(filename_out, "w")
for i in range(M):
	file_out.write(str(array_sizes[i]) + " " + str(array_normal_times[i]) + " " \
				  +str(array_normalMR[i]) + " " +str(array_normalMW[i]) + " " \
				  +str(array_trans_times[i]) + " " + str(array_transMR[i]) + " " \
				  +str(array_transMW[i]) + "\n")
