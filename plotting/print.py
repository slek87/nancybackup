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
skipList = {} # If less than 95% of instance is unsolved, it gets skipped
algoGlobal = ''

def aggregateCvs(loc):
    global algoMissing, first, algoGlobal

    alert = False
    i = 0
    found = []
    missing = []
    lookahead = ''
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
        for indx, inst in enumerate(missing):
            if indx == len(missing) - 1:
                compress = compress + str(inst)
            elif indx == 0:
                compress = str(inst) + ' '
            elif inst - 1 == missing[indx - 1] and inst + 1 == missing[indx + 1]:
                compress = compress.strip()
                compress = compress + '-'
            else:
                compress = compress + str(inst) + ' '
    
        compress = re.sub('-+', '--', compress)
        print('    M: ' + compress)
        algoMissing = algoMissing + len(missing)
    else:
        print('   ' + loc.split('/')[-1] + ' ' + str(i))
    
    # By the time code gets here, the missing array contains all the unsolved instances for this algorithm/lookahead
    if ('Tree' in loc and len(missing) > 50) or ('Tree' not in loc and len(missing) > 5):
        if not algoGlobal in skipList:
            skipList[algoGlobal] = []
        skipList[algoGlobal].append(lookahead)
        print('[!] Not adding ' + algoGlobal + ' ' + lookahead + ' to commonly solved for this lookahead')
    else:
        # 95% was solved add it to the common list of filter
        if not lookahead in unsolvedInstance:
            unsolvedInstance[lookahead] = {}
        for inst in missing:
            print('[+] ' + lookahead + ' Adding ' + str(inst))
            unsolvedInstance[lookahead][str(inst)] = True


def fixTitle(t):
    if t == 'HeavyTile':
        return 'Heavy Sliding Puzzle'
    if t == 'SlidingPuzzle':
        return 'Sliding Puzzle'
    if t == 'TreeWorld':
        return 'Random Binary Tree'
    if t == 'InverseTile':
        return 'Inverse Sliding Puzzle'
    if t == 'SqrtTile':
        return 'Square Root Sliding Puzzle'
    return t

def fixName(a):
    if 'UCT' in a or 'WA' in a or 'AS' in a[0:2]:
        a = a.replace('S', '*')
        a = a.replace('iep', '-IEP')
        a = a.replace('ie', '-IE')
        a = a.replace('nancy', '-Nancy')
        a = a.replace('-', ' -')

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
    # ax.legend(loc='upper right')
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

uct = ['UCT','UCTie', 'UCTiep','UCTnancy']
ucts = ['UCTS','UCTSie', 'UCTSiep', 'UCTSnancy']
guct = ['GUCT','GUCTie', 'GUCTiep','GUCTnancy']
gucts = ['GUCTS','GUCTSie', 'GUCTSiep', 'GUCTSnancy']
aas = ['AS', 'ASie', 'ASiep','ASnancy']
was = ['WAS', 'WASie', 'WASiep','WASnancy']

other = ['RISK','FHAT','LSSLRTA','IE','IEP', 'IEPP']

# PARAMS

mix = ['UCTiep','UCTnancy', 'UCTSiep', 'UCTSnancy']

uctLearn = ['UCT-L','UCTie-L', 'UCTiep-L','UCTnancy-L']
uctsLearn = ['UCTS-L','UCTSie-L', 'UCTSiep-L', 'UCTSnancy-L']

guctLearn = ['GUCT-L','GUCTie-L', 'GUCTiep-L','GUCTnancy-L']
guctsLearn = ['GUCTS-L','GUCTSie-L', 'GUCTSiep-L', 'GUCTSnancy-L']

aasLearn = ['AS-L', 'ASie-L', 'ASiep-L','ASnancy-L']
wasLearn = ['WAS-L', 'WASie-L', 'WASiep-L','WASnancy-L']

best = ['WASiep', 'GUCTSiep', 'RISK', 'IE'] 
best2 = ['WASiep', 'GUCTSiep', 'RISK'] 

DOMAIN = sys.argv[1]
OUTFILE = DOMAIN 
DIRECTORY = sys.argv[2]
# ALL = ['UCT','UCTnancy','UCTie','UCTiep','UCTS','UCTSnancy','UCTSie','UCTSiep','GUCT','GUCTnancy','GUCTie','GUCTiep','GUCTS','GUCTSnancy','GUCTSie','GUCTSiep','AS','ASnancy','ASie','ASiep','WAS','WASie','WASiep','WASnancy','UCT-L','UCTnancy-L','UCTie-L','UCTiep-L','UCTS-L','UCTSnancy-L','UCTSie-L','UCTSiep-L','GUCT-L','GUCTnancy-L','GUCTie-L','GUCTiep-L','GUCTS-L','GUCTSnancy-L','GUCTSie-L','GUCTSiep-L','AS-L','ASnancy-L','ASie-L','ASiep-L','WAS-L','WASie-L','WASiep-L','WASnancy-L','UCT-H','UCTnancy-H','UCTie-H','UCTiep-H','UCTS-H','UCTSnancy-H','UCTSie-H','UCTSiep-H','GUCT-H','GUCTnancy-H','GUCTie-H','GUCTiep-H','GUCTS-H','GUCTSnancy-H','GUCTSie-H','GUCTSiep-H','AS-H','ASnancy-H','ASie-H','ASiep-H','WAS-H','WASie-H','WASiep-H','WASnancy-H','UCT-LH','UCTnancy-LH','UCTie-LH','UCTiep-LH','UCTS-LH','UCTSnancy-LH','UCTSie-LH','UCTSiep-LH','GUCT-LH','GUCTnancy-LH','GUCTie-LH','GUCTiep-LH','GUCTS-LH','GUCTSnancy-LH','GUCTSie-LH','GUCTSiep-LH','AS-LH','ASnancy-LH','ASie-LH','ASiep-LH','WAS-LH','WASie-LH','WASiep-LH','WASnancy-LH', 'RISK', 'LSSLRTA', 'FHAT', 'IE', 'IEP', 'IEPP']

ALL = ['UCT','UCTnancy','GUCTiep','UCTiep','UCTS','UCTSnancy','UCTSie','UCTSiep','GUCT','GUCTnancy','GUCTie','GUCTiep','GUCTS','GUCTSnancy','GUCTSie','GUCTSiep','AS','ASnancy','ASie','ASiep','WAS','WASie','WASiep','WASnancy','UCT-L','UCTnancy-L','UCTie-L','UCTiep-L','UCTS-L','UCTSnancy-L','UCTSie-L','UCTSiep-L','GUCT-L','GUCTnancy-L','GUCTie-L','GUCTiep-L','GUCTS-L','GUCTSnancy-L','GUCTSie-L','GUCTSiep-L','AS-L','ASnancy-L','ASie-L','ASiep-L','WAS-L','WASie-L','WASiep-L','WASnancy-L', 'RISK', 'LSSLRTA', 'FHAT', 'IE', 'IEP', 'IEPP']


FRONT_APPEND = 'aas' + '_' # Goes in front of the name of the pdf file being output
FINEFILTER = []
ALGO_FILTER = aas + was
PLOT = True

# if not PLOT:
#     ALGO_FILTER = ALL

# First loop through all the algorithm folders to check of unsolved instances
# Missing instances will be shown in the output
# Unsolved instances will we plaved in a dict, and whne the csv turned in to dataframe, the instanses will be removed
# From the other algorithms for fair comparisons
for algo in os.listdir(DIRECTORY):
    if not algo in ALGO_FILTER:
            continue
    if len(FINEFILTER) > 0 and str(algo) in FINEFILTER:
        continue

    algoMissing = 0
    algoGlobal = algo
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
        print ('===[TOTAL] ' + str(algoMissing) + '\n')
    totalMissing = totalMissing + algoMissing


print ('UNSOLVED TOTAL: ' + str(totalMissing) + '\n')






# Loop through each algorithm and get the csv files to be turned into dataframes
frames = []
for a in ALGO_FILTER:
    for algorithm in os.listdir(DIRECTORY):

        if not algorithm == a:
            continue

        if PLOT and algorithm in skipList:
            if len(skipList[algorithm]) == 5:
                print('[!] Skipping ' + algorithm + ' entirely for plotting')
                continue

        if len(FINEFILTER) > 0 and str(algorithm) in FINEFILTER:
            continue
        for dom in os.listdir(DIRECTORY + '/' + str(algorithm)):
            if '.csv' in str(dom) and DOMAIN == dom.split('.')[0]:
                print(DIRECTORY + '/' + str(algorithm) + '/' + str(dom))
                df = pd.read_csv(DIRECTORY + '/' + str(algorithm) + '/' + str(dom), delimiter = ',')
                # algostr = df.iloc[0]['Algorithm']
                # Remove rows that cannot be solved by all algorithms
                # Remove solved < 95%
                if algorithm in skipList:
                        for lookahead in skipList[algorithm]:
                            # print('Skipping ' + algorithm + ' ' + lookahead)
                            intLookahead = int(lookahead[2:])
                            # indexNames = df[ (df['Lookahead'] == intLookahead) & (df['Algorithm'] == algorithm) ].index
                            df.loc[(df.Lookahead == intLookahead) & (df.Algorithm == algorithm),'SolCost'] = 0
                            indexNames = df[ (df['Lookahead'] == intLookahead) ].index
                            df.loc[indexNames,'SolCost'] = 0

                            if (PLOT):
                                indexNames = df[ (df['Lookahead'] == intLookahead) & (df['Algorithm'] == algorithm) ].index
                                df.drop(indexNames , inplace=True)
                
                            
                for lookahead, instances in unsolvedInstance.items():
                    for instance, val in instances.items():
                        if 'Tree' in dom:
                            instance = 'b2d100-' + instance + '.csv'
                        elif 'Pancake' in dom:
                            instance = instance + '-10.csv'
                        else:
                            instance = instance + '-4x4.csv'
                        intLookahead = int(lookahead[2:])
                        indexNames = df[ (df['Lookahead'] == intLookahead) & (df['FileID'] == instance) ].index
                        print('[-] ' + lookahead + ' ' + instance)
                        df.drop(indexNames , inplace=True)
                


                # df = df[df.Lookahead != 10]
                # df = df[df.Lookahead != 30]
                # df = df[df.Lookahead != 100]
                # df = df[df.Lookahead != 300]
                # df = df[df.Lookahead != 1000]

                # df.SolCost = df.SolCost.round(2)

                df['Algorithm'] = fixName(algorithm)
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

for indx, inst in enumerate(skipList):
    print(inst)
    print(skipList[inst])


if (PLOT):
    result = result[result.SolCost != 0]
    title = fixTitle(DOMAIN)
    pointplot(result, FRONT_APPEND + OUTFILE + '.pdf', False, title)
    violinplot(result,FRONT_APPEND  + OUTFILE + '_vio.pdf', False, title)
    boxplot(result,FRONT_APPEND  + OUTFILE + '_box.pdf', False, title)
else:
    # del result['Lookahead']
    del result['NodeGen']
    del result['NodeExp']

    table = pd.pivot_table(result, values='SolCost', index=['Algorithm'], columns=['Lookahead'], aggfunc=np.mean)
    table = np.round(table, 2)

    # result = result.groupby('Algorithm').mean()

    # with pd.option_context('display.max_rows', None, 'display.max_columns', None):  # more options can be specified also
    #     print(result)
    print(table.to_latex(index=True))
