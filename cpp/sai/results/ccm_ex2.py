
import json
import sys
import os

directory = sys.argv[1]

lines = []

lines.append('WA* cost, WA* nodes gen, WA* nodes ex, GUCT cost, GUCT nodes gen, GUCT nodes ex, GUCT* cost, GUCT* nodes gen, GUCT* nodes ex\n')

for file in os.listdir(directory):
    with open(directory + '/' + file) as json_data:
        data = json.load(json_data)
        row = ''
        algo = 'WA*'
        for p in data[algo]:
            row = row + str(p) + ','
        algo = 'GUCT'
        for p in data[algo]:
            row = row + str(p) + ','
        algo = 'GUCT*'
        for p in data[algo]:
            row = row + str(p) + ','
        row = row + '\n'
        lines.append(row)
        
filename = open('result.csv','w')
for l in lines:
    filename.write(l)
filename.close()