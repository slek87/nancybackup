#!/usr/bin/python3
# -*- coding: utf8 -*-

import sys
import os


# outfileName = outfileName + '.csv'
lines = []
lines.append('Algorithm,World,SolCost,NodeGen,NodeExp,Lookahead,FileID\n')


def clearLine():
    lines.clear()
    lines.append('Algorithm,World,SolCost,NodeGen,NodeExp,Lookahead,FileID\n')

def aggregateCvs(directory):
    for file in os.listdir(directory):
        with open(directory +'/' + file) as f:
            for line in f:
                line = line.rstrip('\n')
                lines.append(line + ',' + file + '\n')

for file in os.listdir('.'):
    if '.' in str(file):
        continue

    outfileName = str(file)
    print(outfileName)

    if 'Tree' in str(file):
        for subfolder in os.listdir(str(file)):
            print(str(subfolder))
            aggregateCvs(str(file) + '/' + str(subfolder))
        filename = open(outfileName + '.csv', 'w')

    else:
        for subfolder in os.listdir(str(file)):
            print(str(subfolder))
            for subsubfolder in os.listdir(str(file) + '/' + str(subfolder)):
                print(str(subsubfolder))
                aggregateCvs(str(file) + '/' + str(subfolder) + '/' + str(subsubfolder))
            filename = open(outfileName + str(subfolder) + '.csv', 'w')

    for l in lines:
        filename.write(l)
    filename.close()
    clearLine()