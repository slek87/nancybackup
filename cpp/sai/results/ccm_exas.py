
import json
import sys
import os

directory = sys.argv[1]

lines = []

lines.append('A* cost, A* nodes gen, A* nodes ex, THTS-A* cost, THTS-A* nodes gen, THTS-A* nodes ex, THTS-A*-L cost, THTS-A*-L nodes gen, THTS-A*-L nodes ex\n')

for file in os.listdir(directory):
    with open(directory + '/' + file) as json_data:
        data = json.load(json_data)
        row = ''
        algo = 'A*'
        for p in data[algo]:
            row = row + str(p) + ','
        algo = 'THTS-A*'
        for p in data[algo]:
            row = row + str(p) + ','
        algo = 'THTS-A*-L'
        for p in data[algo]:
            row = row + str(p) + ','
        row = row + '\n'
        lines.append(row)
        
filename = open('result.csv','w')
for l in lines:
    filename.write(l)
filename.close()