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

def pointplot(df, n, j, title):
    sns.set(rc={'figure.figsize': (16, 12), 'font.size': 14, 'text.color': 'black'})
    sns.pointplot(x='Lookahead', y='SolCost', data=df, hue = 'Algorithm', dodge=0.3, join=j, markers=markerList)
    plt.title(title, fontsize=20)
    plt.ylabel('$Solution Cost$', color='black', fontsize=12)
    plt.xlabel('Node Expansion Limit', color='black', fontsize=12)
    plt.savefig(n, bbox_inches="tight", pad_inches=0)
    plt.close()
    plt.clf()
    plt.cla()
    return

data = sys.argv[1]
outfileName = data.split('.')[0] + '.pdf'


frames = []
for folder in os.listdir('results'):
    for file in os.listdir('results/' + str(folder)):
        if '.csv' in str(file) and data in str(file):
            df = pd.read_csv('results/' + str(folder) + '/' + str(file), delimiter = ',')
            algo = df.iloc[0]['Algorithm']
            df['Algorithm'] = str(folder)
            frames.append(df)

result = pd.concat(frames)       
# Filter out the following algorithms     
result = result[result.Lookahead != 10]
result = result[result.Lookahead != 30]

# result = result[result.Algorithm != 'UCTS']
# result = result[result.Algorithm != 'AS']
pointplot(result,outfileName,False, data.split('.')[0])



