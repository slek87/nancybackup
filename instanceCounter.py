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
    i = 0
    for file in os.listdir(directory):
        i += 1
    print('\t' + directory + ' ' + str(i) + ' lines')

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


