#!/usr/bin/python3
# -*- coding: utf8 -*-

# This script aggregate .csv files to the algorithm base folder
# To use it, it takes a directory as the only argument
# That directory should contain the folder of different algorithms
# which contains the results of different domains

import sys
import os


# outfileName = outfileName + '.csv'
base = sys.argv[1]

def aggregateCvs(directory):
    alert = False
    i = 0
    found = []
    missing = []
    for file in os.listdir(directory):
        inst_arr = (str(file)).split('-')
        if inst_arr[0] == 'b2d100':
            inst_num = (inst_arr[1].split('.'))[0]
            found.append(int(inst_num))
        else:
            inst_num = inst_arr[0]
            found.append(int(inst_num))

        i += 1

    if 'Tree' in directory and i != 1000:
        missing = [i for i in range(1, 1001)]
        alert = True
    elif 'Tree' not in directory and i != 100:
        missing = [i for i in range(1, 101)]
        alert = True

    if alert:
        print('\t    ' + directory.split('/')[-1] + ' ' + str(i) + '/' + str(len(missing)))
        for f in found:
            missing.remove(f)
        print('\t    Missing: ' + str(missing))
        

for algo in os.listdir(base):
    loc = base + algo 
    print(algo)
    for domain in os.listdir(loc):
        if '.' in str(domain):
            continue

        print('\t' + domain)

        for subfolder in os.listdir( loc + '/' + str(domain)):

            if 'Tile' in str(domain) or 'Sliding' in str(domain):
                for lookahead in os.listdir( loc + '/' + str(domain) + '/4x4/'):
                    aggregateCvs(loc + '/' + str(domain) + '/4x4/' + lookahead)
            elif 'Pancake' in str(domain):
                for lookahead in os.listdir( loc + '/' + str(domain) + '/10/'):
                    aggregateCvs(loc + '/' + str(domain) + '/10/' + lookahead)
            else:
                # for lookahead in os.listdir( loc + '/' + str(domain) ):
                aggregateCvs(loc + '/' + str(domain) + '/' + subfolder)


