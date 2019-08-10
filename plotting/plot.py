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

# simply put this file in the same directory and the result folder

markerList=["o", "v", "s", "<", "p", "h", "^", "D", "X", ">", "o", "v", "s", "<", "p", "h", "^", "D", "X", ">"]

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

domain = sys.argv[1]
outfileName = domain + '.pdf'
directory = sys.argv[2]


uctArr = ['UCT','UCTie', 'UCTiep','UCTnancy','UCTS','UCTSie', 'UCTSiep', 'UCTSnancy']
guctArr = ['GUCT','GUCTie', 'GUCTiep','GUCTnancy','GUCTS','GUCTSie', 'GUCTSiep', 'GUCTSnancy']
wasArr = ['WAS', 'WASie', 'WASiep','WASnancy']
otherArr = ['RISK','FHAT','LSSLRTA','IE', 'IEP']


# PARAMS
printRange = otherArr
frontTextAppend = '_O' # Goes in front of the name of the pdf file being output

frames = []
for a in printRange:
    for algorithm in os.listdir(directory):
        if not algorithm == a:
            continue
        for dom in os.listdir(directory + '/' + str(algorithm)):
            if '.csv' in str(dom) and dom.split('.')[0] == domain:
                print(directory + '/' + str(algorithm) + '/' + str(dom))
                df = pd.read_csv(directory + '/' + str(algorithm) + '/' + str(dom), delimiter = ',')
                # algostr = df.iloc[0]['Algorithm']
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

title = fixTitle(domain)

pointplot(result, frontTextAppend + outfileName,False, title)
# violinplot(result,frontTextAppend + 'Violin' + outfileName,False, title)
# boxplot(result,frontTextAppend + 'Box' + outfileName,False, title)




