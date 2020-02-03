import sys

# Getting input parameters:
#	- fin = filename of input data
#	- n_reps = number of reps
#	- fout = filename of output data after processing
fin_name = str(sys.argv[1])
n_reps = int(sys.argv[2])
fout_name = str(sys.argv[3])

# Opening input file and initializing arrays
fin = open(fin_name, "r")
lines = fin.readlines()
n_lines = len(lines)
M = n_lines/n_reps
sizes = []
timesS = []
timesP = []
for i in range(M):
	sizes.append(0)
	timesS.append(0.0)
	timesP.append(0.0)

i=0
for line in lines:
	data = line.split()
	sizes[i] = int(data[0])
	timesS[i] += float(data[1])
	timesP[i] += float(data[2])
	i = (i+1)%M

for i in range(M):
	timesS[i] /= n_reps
	timesP[i] /= n_reps

fout = open(fout_name, "w")
for i in range(M):
	fout.write(str(sizes[i])+" "+str(timesS[i])+" "+str(timesP[i])+" "+str(round((timesS[i]/timesP[i]), 2))+"\n")

fin.close()
fout.close()