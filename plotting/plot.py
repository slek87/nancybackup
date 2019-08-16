#!/usr/bin/python3
# -*- coding: utf8 -*-

import os
import sys
import re
import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd
from mpl_toolkits.mplot3d import Axes3D
import numpy as np
from matplotlib import cm
from matplotlib.ticker import LinearLocator, FormatStrFormatter
import random

__author__ = 'Sai Lekyang'

markerList=["o", "v", "s", "<", "p", "h", "^", "D", "X", ">", "o", "v", "s", "<", "p", "h", "^", "D", "X", ">"]
totalMissing = 0
algoMissing = 0
unsolvedInstance = {}

def aggregateCvs(loc):
    global algoMissing, first

    alert = False
    i = 0
    found = []
    missing = []
    for file in os.listdir(loc):
        if 'csv' not in file:
            continue

        inst_arr = (str(file)).split('-')
        if inst_arr[0] == 'b2d100':
            inst_num = (inst_arr[1].split('.'))[0]
            found.append(int(inst_num))
        else:
            inst_num = inst_arr[0]
            found.append(int(inst_num))

        i += 1

    if 'Tree' in loc and i != 1000:
        missing = [i for i in range(1, 1001)]
        alert = True
    elif 'Tree' not in loc and i != 100:
        missing = [i for i in range(1, 101)]
        alert = True

    if alert:
        lookahead = loc.split('/')[-1]
        if first:
            print(' ' + str(loc.split('/')[-3]) + ' ' + str(loc.split('/')[-2]))

            first = False
        print('   ' + lookahead + ' ' + str(i) + '/' + str(len(missing)))
        for f in found:
            missing.remove(f)
        compress = ''
        for num, inst in enumerate(missing):
            if lookahead in unsolvedInstance:
                 unsolvedInstance[lookahead].append(str(inst))
            else:
                unsolvedInstance[lookahead] = []
                unsolvedInstance[lookahead].append(str(inst))


            if num == len(missing) - 1:
                compress = compress + str(inst)
            elif num == 0:
                compress = str(inst) + ' '
            elif inst - 1 == missing[num - 1] and inst + 1 == missing[num + 1]:
                compress = compress.strip()
                compress = compress + '-'
            else:
                compress = compress + str(inst) + ' '
    

        print('    Missing: ' + compress)
        algoMissing = algoMissing + len(missing)



def fixTitle(t):
    if t == 'HeavyTile':
        return 'Heavy Sliding Puzzle'
    if t == 'SlidingPuzzle':
        return 'Sliding Puzzle'
    if t == 'TreeWorld':
        return 'Random Binary Tree'
    if t == 'InverseTile':
        return 'Inverse Sliding Puzzle'
    return t

def fixName(a):
    if 'UCT' in a or 'WA' in a:
        a = a.replace('S', '*')
        a = a.replace('iep', '-IEP')
        a = a.replace('ie', '-IE')
        a = a.replace('nancy', '-Nancy')
    else:
        if a == 'RISK':
            a = 'Risk'
        elif a == 'FHAT':
            a = 'F-Hat'
        elif a == 'LSSLRTA':
            a = 'LSS-LRTA*'
        elif a == 'LSSLRTA':
            a = 'LSS-LRTA*'
            
    return a
def pointplot(df, n, j, title):
    sns.set(rc={'figure.figsize': (12, 8), 'font.size': 14, 'text.color': 'black'})
    ax = sns.pointplot(x='Lookahead', y='SolCost', data=df, hue = 'Algorithm', dodge=0.3, join=j, markers=markerList, errwidth=3, ci=95)
    ax.legend(loc='upper right')
    plt.title(title, fontsize=18)
    plt.ylabel('Solution Cost', color='black', fontsize=14)
    plt.xlabel('Node Expansion Limit', color='black', fontsize=14)
    plt.savefig(n, bbox_inches="tight", pad_inches=0)
    plt.close()
    plt.clf()
    plt.cla()
    return

def violinplot(df, n, j, title):
    sns.set(rc={'figure.figsize': (12, 8), 'font.size': 14, 'text.color': 'black'})
    # ax = sns.pointplot(x='Lookahead', y='SolCost', data=df, hue = 'Algorithm', dodge=0.3, join=j, markers=markerList, palette=sns.color_palette(["red"]), errwidth=3, ci=95)
    # ax.tick_params(colors='black', labelsize=12)
    # plt.setp(ax.lines, zorder=100)
    # plt.setp(ax.collections, zorder=100, label="")
    # ax.legend_.remove()

    ax = sns.violinplot(x='Lookahead', y='SolCost', data=df, hue = 'Algorithm')    
    ax.legend(loc='upper right')
    plt.title(title, fontsize=18)
    plt.ylabel('Solution Cost', color='black', fontsize=14)
    plt.xlabel('Node Expansion Limit', color='black', fontsize=14)
    plt.savefig(n, bbox_inches="tight", pad_inches=0)
    plt.close()
    plt.clf()
    plt.cla()
    return

def boxplot(df, n, j, title):
    sns.set(rc={'figure.figsize': (12, 8), 'font.size': 14, 'text.color': 'black'})
    ax = sns.boxplot(x='Lookahead', y='SolCost', data=df, hue = 'Algorithm')    
    ax.legend(loc='upper right')
    plt.title(title, fontsize=18)
    plt.ylabel('Solution Cost', color='black', fontsize=14)
    plt.xlabel('Node Expansion Limit', color='black', fontsize=14)
    plt.savefig(n, bbox_inches="tight", pad_inches=0)
    plt.close()
    plt.clf()
    plt.cla()
    return

uctArr = ['UCT','UCTie', 'UCTiep','UCTnancy','UCTS','UCTSie', 'UCTSiep', 'UCTSnancy']
guctArr = ['GUCT','GUCTie', 'GUCTiep','GUCTnancy','GUCTS','GUCTSie', 'GUCTSiep', 'GUCTSnancy']
wasArr = ['WAS', 'WASie', 'WASiep','WASnancy']
otherArr = ['RISK','FHAT','LSSLRTA','IE','IEP']

# PARAMS

uctArr_greedyStep = ['UCT-H','UCTie-H', 'UCTiep-H','UCTnancy-H','UCTS-H','UCTSie-H', 'UCTSiep-H', 'UCTSnancy-H']
guctArr_greedyStep = ['GUCT-H','GUCTie-H', 'GUCTiep-H','GUCTnancy-H','GUCTS-H','GUCTSie-H', 'GUCTSiep-H', 'GUCTSnancy-H']
DOMAIN = sys.argv[1]
OUTFILE = DOMAIN + '.pdf'
DIRECTORY = sys.argv[2]
ALGO_FILTER = ['UCTS-H', 'GUCT-H',  'GUCTS-H', 'UCT-H'  ]
FRONT_APPEND = 'guctArr' # Goes in front of the name of the pdf file being output


# First loop through all the algorithm folders to check of unsolved instances
# Missing instances will be shown in the output
# Unsolved instances will we plaved in a dict, and whne the csv turned in to dataframe, the instanses will be removed
# From the other algorithms for fair comparisons
for algo in os.listdir(DIRECTORY):
    if not algo in ALGO_FILTER:
            continue

    algoMissing = 0

    loc = DIRECTORY + '/' + algo 
    print(algo)

    for dom in os.listdir(loc):
        first = True
        if '.' in str(dom) or not dom == DOMAIN:
            continue


        for subfolder in os.listdir( loc + '/' + str(dom)):

            if 'Tile' in str(dom) or 'Sliding' in str(dom):
                for lookahead in os.listdir( loc + '/' + str(dom) + '/4x4/'):
                    aggregateCvs(loc + '/' + str(dom) + '/4x4/' + lookahead)
            elif 'Pancake' in str(dom):
                for lookahead in os.listdir( loc + '/' + str(dom) + '/10/'):
                    aggregateCvs(loc + '/' + str(dom) + '/10/' + lookahead)
            else:
                # for lookahead in os.listdir( loc + '/' + str(dom) ):
                aggregateCvs(loc + '/' + str(dom) + '/' + subfolder)

    if (algoMissing > 0):
        print ('  -TOTAL: ' + str(algoMissing) + '\n')
    totalMissing = totalMissing + algoMissing


print ('UNSOLVED TOTAL: ' + str(totalMissing) + '\n')






# Loop through each algorithm and get the csv files to be turned into dataframes
frames = []
for a in ALGO_FILTER:
    for algorithm in os.listdir(DIRECTORY):

        if not algorithm == a:
            continue
        
        for dom in os.listdir(DIRECTORY + '/' + str(algorithm)):
            if '.csv' in str(dom) and DOMAIN == dom.split('.')[0]:
                print(DIRECTORY + '/' + str(algorithm) + '/' + str(dom))
                df = pd.read_csv(DIRECTORY + '/' + str(algorithm) + '/' + str(dom), delimiter = ',')
                # algostr = df.iloc[0]['Algorithm']
                df['Algorithm'] = fixName(algorithm)



                # Remove rows that cannot be solved by all algorithms
                for lookahead, instances in unsolvedInstance.items():
                    for instance in instances:
                        if 'Tree' in dom:
                            instance = 'b2d100-' + instance + '.csv'
                        elif 'Pancake' in dom:
                            instance = instance + '-10.csv'
                        else:
                            instance = instance + '-4x4.csv'
                        df = df[(str(df.Lookahead) != lookahead) & (df.FileID != instance)]
                frames.append(df)



if len(frames) == 0:
    exit(0)



result = pd.concat(frames)      


# Filter out the following algorithms     
# result = result[result.Lookahead != 10]
# result = result[result.Lookahead != 30]
# result = result[result.Lookahead != 100]
# result = result[result.Lookahead != 300]
# result = result[result.Lookahead != 1000]

title = fixTitle(DOMAIN)

pointplot(result, FRONT_APPEND + OUTFILE,False, title)
# violinplot(result,FRONT_APPEND + 'Violin' + OUTFILE,False, title)
# boxplot(result,FRONT_APPEND + 'Box' + OUTFILE,False, title)




wasArr