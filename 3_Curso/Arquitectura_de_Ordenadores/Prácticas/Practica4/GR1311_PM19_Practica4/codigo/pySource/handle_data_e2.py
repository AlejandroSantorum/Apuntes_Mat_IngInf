import sys

# Getting input parameters:
#	- fname_serie = filename of standard escalar prod data
#	- fname_par = filename of paralellized escalar prod data
#	- M = number of different vector sizes
#	- n_cores = number of cores
#	- fout = filename of the handled data
#	- fext = extention of files
fname_serie = str(sys.argv[1])
fname_par = str(sys.argv[2])
M = int(sys.argv[3])
n_cores = int(sys.argv[4])
fout = str(sys.argv[5])
fext = str(sys.argv[6])

# Initializing arrays
sizes = []
times = []
for i in range(M):
	sizes.append(0)
	times.append(0)

# Reading standard escalar prod data
fserie = open(fname_serie, "r")
lines = fserie.readlines()
n_lines = len(lines)
i=0
for line in lines:
	data = line.split()
	sizes[i] = int(data[0])
	times[i] += float(data[1])
	i = (i+1)%M

# Calculating mean valures for standard escalar prod data
n_sums = n_lines/M
for i in range(M):
	times[i] /= n_sums

foutS = open(fout+"0"+fext, "w")
for i in range(M):
	foutS.write(str(sizes[i]) + " " + str(times[i]) + "\n")
fserie.close()
foutS.close()

# Handling data for paralellized escalar prod
fserie = open(fout+"0"+fext, "r")
linesSerie = fserie.readlines()
fpar = open(fname_par, "r")
lines = fpar.readlines()
n_lines = len(lines)
dpc = n_lines/n_cores # data per core
n_sums = (dpc/M)
for k in range(n_cores):
	sizes = []
	times = []
	for i in range(M):
		sizes.append(0)
		times.append(0)

	for i in range(dpc):
		line = lines[i+(k*dpc)]
		data = line.split()
		sizes[i%M] =  int(data[1])
		times[i%M] = float(data[2])

	for i in range(M):
		times[i] /= n_sums

	foutP = open(fout+str(k+1)+fext, "w")
	for i in range(M):
		foutP.write(str(sizes[i]) + " " + str(times[i]) + " " + str(float(linesSerie[i].split()[1])/times[i]) + "\n")
	foutP.close()
fpar.close()
fserie.close()