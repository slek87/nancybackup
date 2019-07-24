#!/usr/bin/python3
# -*- coding: utf8 -*-

# This script aggregate .csv files to the algorithm base folder
# To use it, it takes a directory as the only argument
# That directory should contain the folder of different algorithms
# which contains the results of different domains

import sys
import os


# outfileName = outfileName + '.csv'
lines = []
base = sys.argv[1]

def clearLine():
    lines.clear()
    lines.append('Algorithm,World,SolCost,NodeGen,NodeExp,Lookahead,FileID\n')

def aggregateCvs(directory):
    for file in os.listdir(directory):
        with open(directory +'/' + file) as f:
            for line in f:
                line = line.rstrip('\n')
                lines.append(line + ',' + file + '\n')

for algo in os.listdir(base):
    loc = base + algo 
    print(algo)
    print('loc' + loc)
    for domain in os.listdir(loc):
        if '.' in str(domain):
            continue

        clearLine()

        print(domain)
        print('\tloc' + loc + '/' + domain)

        for subfolder in os.listdir( loc + '/' + str(domain)):
            if 'Heavy' in str(domain) or 'Sliding' in str(domain):
                for lookahead in os.listdir( loc + '/' + str(domain) + '/4x4/'):
                    aggregateCvs(loc + '/' + str(domain) + '/4x4/' + lookahead)
            else:
                for lookahead in os.listdir( loc + '/' + str(domain)):
                    aggregateCvs(loc + '/' + str(domain) + '/' + lookahead)

        filename = loc + '/' + domain + '.csv' 
        out = open(filename, 'w')
        for l in lines:
            out.write(l)
        out.close()