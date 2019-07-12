#!/usr/bin/python3
# -*- coding: utf8 -*-

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


df = pd.read_csv(data, delimiter = ',')

pointplot(df,outfileName,False, data.split('.')[0])



