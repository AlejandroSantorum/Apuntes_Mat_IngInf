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
array_slow_times = []
array_fast_times = []
for i in range(M):
	array_sizes.append(0)
	array_slow_times.append(0)
	array_fast_times.append(0)

# Reading data
file_in = open(filename_in, "r")
lines = file_in.readlines()
n_lines = len(lines)
i = 0
for line in lines:
	data = line.split()
	array_sizes[i] = int(data[0])
	array_slow_times[i] += float(data[1])
	array_fast_times[i] += float(data[2])
	i = (i+1)%M

# Calculating mean values
n_sums = (n_lines/M)
for i in range(M):
	array_slow_times[i] /= n_sums
	array_fast_times[i] /= n_sums

# Saving mean values into the specified file
file_out = open(filename_out, "w")
for i in range(M):
	file_out.write(str(array_sizes[i]) + " " + str(array_slow_times[i]) +\
					 " " +str(array_fast_times[i])+ "\n")