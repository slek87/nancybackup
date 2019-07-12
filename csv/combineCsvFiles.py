import sys
import os

directory = sys.argv[1]
outfileName = sys.argv[2]
outfileName = outfileName + '.csv'

lines = []

lines.append('Algorithm,World,SolCost,NodeGen,NodeExp,Lookahead,FileID\n')

try:
	subfolder = '/LA10'
	for file in os.listdir(directory + subfolder):
		with open(directory + subfolder +'/' + file) as f:
			for line in f:
				line = line.rstrip('\n')
				lines.append(line + ',' + file + '\n')
except:
        print("cannot deal with " + subfolder)
try:
	subfolder = '/LA30'
	for file in os.listdir(directory + subfolder):
		with open(directory + subfolder +'/' + file) as f:
			for line in f:
				line = line.rstrip('\n')
				lines.append(line + ',' + file + '\n')
except:
        print("cannot deal with " + subfolder)
try:   
	subfolder = '/LA100'
	for file in os.listdir(directory + subfolder):
		with open(directory + subfolder +'/' + file) as f:
			for line in f:
				line = line.rstrip('\n')
				lines.append(line + ',' + file + '\n')
except:
        print("cannot deal with " + subfolder)
try:
	subfolder = '/LA300'
	for file in os.listdir(directory + subfolder):
		with open(directory + subfolder +'/' + file) as f:
			for line in f:
				line = line.rstrip('\n')
				lines.append(line + ',' + file + '\n')
except:
        print("cannot deal with " + subfolder)
try:
	subfolder = '/LA1000'
	for file in os.listdir(directory + subfolder):
		with open(directory + subfolder +'/' + file) as f:
			for line in f:
				line = line.rstrip('\n')
				lines.append(line + ',' + file + '\n')
except:
        print("cannot deal with " + subfolder)
filename = open(outfileName,'w')
for l in lines:
    filename.write(l)
filename.close()
