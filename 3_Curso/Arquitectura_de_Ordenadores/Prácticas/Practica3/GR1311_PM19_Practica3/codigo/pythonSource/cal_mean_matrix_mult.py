import sys

# Getting input parameters
#	- filename_in = filename of the input values (for each line: matrix_size slow_exec_time fast_exec_time)
#	- M = number of different matrix sizes (i.e. ((Nfinal-Ninicial)/Nstep)+1)
#	- filename_out = filename of the mean values fo each matrix size
filename_in_times = str(sys.argv[1])
filename_in_caches = str(sys.argv[2])
M = int(sys.argv[3])
filename_out = str(sys.argv[4])

# Initializing data arrays
array_sizes = []
array_normal_times = []
array_trans_times = []
for i in range(M):
	array_sizes.append(0)
	array_normal_times.append(0)
	array_trans_times.append(0)

# Reading data of times
file_in_times = open(filename_in_times, "r")
lines = file_in_times.readlines()
n_lines = len(lines)
i = 0
for line in lines:
	data = line.split()
	array_sizes[i] = int(data[0])
	array_normal_times[i] += float(data[1])
	array_trans_times[i] += float(data[2])
	i = (i+1)%M

# Calculating mean values
n_sums = (n_lines/M)
for i in range(M):
	array_normal_times[i] /= n_sums
	array_trans_times[i] /= n_sums

#Reading data of cache misses
file_in_caches = open(filename_in_caches, "r")
lines2 = file_in_caches.readlines()

# Saving mean values into the specified file
file_out = open(filename_out, "w")
for i in range(M):
	data2 = lines2[i].split()
	file_out.write(str(array_sizes[i]) + " " + str(array_normal_times[i]) + " " \
				  +str(data2[1]) + " " + str(data2[2]) + " " \
				  +str(array_trans_times[i]) + " " + str(data2[3]) + " " \
				  +str(data2[4]) + "\n")
