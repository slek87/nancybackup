import matplotlib.pyplot as plt
import pandas as pd
import json
import seaborn as sns
from os import listdir

def makeViolinPlot(width, height, xAxis, yAxis, dataframe, dodge, hue, orderList, hueOrderList, xLabel, yLabel, outputName):
    sns.set(rc={'figure.figsize': (width, height), 'font.size': 26, 'text.color': 'black'})
    ax = sns.pointplot(x=xAxis, y=yAxis, hue=hue, order=orderList, hue_order=hueOrderList, data=dataframe, join=False, dodge=dodge, palette=sns.color_palette(["red"]), markers="_", errwidth=3, ci=95)
    ax.tick_params(colors='black', labelsize=12)
    plt.setp(ax.lines, zorder=100)
    plt.setp(ax.collections, zorder=100, label="")
    ax.legend_.remove()
    
    sns.violinplot(x=xAxis, y=yAxis, hue=hue, order=orderList, hue_order=hueOrderList, data=dataframe, palette="Set2")    

    plt.ylabel(yLabel, color='black', fontsize=18)
    plt.xlabel(xLabel, color='black', fontsize=18)
    plt.savefig(outputName, bbox_inches="tight", pad_inches=0)
    
    plt.close()
    plt.clf()
    plt.cla()
    return

def makeDifferencePlot(width, height, xAxis, yAxis, dataframe, dodge, hue, orderList, hueOrderList, xLabel, yLabel, outputName, markerList):
    sns.set(rc={'figure.figsize': (width, height), 'font.size': 26, 'text.color': 'black'})
    ax = sns.pointplot(x=xAxis, y=yAxis, hue=hue, order=orderList, hue_order=hueOrderList, data=dataframe, ci=95, errwidth=3, join=False, dodge=dodge, palette="Set2", markers=markerList)
    ax.tick_params(colors='black', labelsize=12)
    plt.ylabel(yLabel, color='black', fontsize=18)
    plt.xlabel(xLabel, color='black', fontsize=18)
    plt.savefig(outputName, bbox_inches="tight", pad_inches=0)
    plt.close()
    plt.clf()
    plt.cla()
    return

markers=["o", "v", "s", "<", "p", "h", "^", "D", "X", ">", "o", "v", "s", "<", "p", "h", "^", "D", "X", ">"]

# Hard coded result directories
resultDirs = {"16"}
limits = [10, 30, 100, 300, 500]
# algorithms = ["A*", "F-Hat", "BFS", "Risk", "LSS-LRTA*", "Random", "Random Sampling"]
algorithms = ["A*", "F-Hat", "Risk", "LSS-LRTA*"]

instance = []
lookAheadVals = []
algorithm = []
solutionCost = []
differenceCost = []

print("reading in data...")

domain = 'Pancake'


for dir in resultDirs:
    for file in listdir("../../../results/" +  domain + "/expansionTests/Nancy/" + dir):
        with open("../../../results/" + domain + "/expansionTests/Nancy/" + dir + "/" + file) as json_data:
            resultData = json.load(json_data)
            for algo in algorithms:
                instance.append(str(dir))
                lookAheadVals.append(resultData["Lookahead"])
                algorithm.append(algo)
                solutionCost.append(resultData[algo])
                differenceCost.append(resultData[algo] - resultData["A*"])
                if (resultData[algo] < resultData["A*"]):
                    print(file)


df = pd.DataFrame({
    "instance":instance,
    "Node Expansion Limit":lookAheadVals,
    "Solution Cost":solutionCost,
    "Algorithm":algorithm
})

dfDiff = pd.DataFrame({
    "instance":instance,
    "Node Expansion Limit":lookAheadVals,
    "Algorithm Cost - A* Cost":differenceCost,
    "Algorithm":algorithm
})

algorithmsExpA = algorithms

algorithmsExpB = ["A*", "F-Hat", "BFS", "Random", "Random Sampling"]

algorithmsExpC = ["A*", "F-Hat", "BFS", "Risk", "Random", "Random Sampling"]

print("building plots...")

for instance in resultDirs:
    sns.set(rc={'figure.figsize': (11, 8), 'font.size': 26, 'text.color': 'black'})
    instanceDataExp = df.loc[df["instance"] == instance]
    instanceDataDiffExp = dfDiff.loc[dfDiff["instance"] == instance]

    makeViolinPlot(13, 10, "Node Expansion Limit", "Solution Cost", instanceDataExp, 0.4, "Algorithm", limits, algorithmsExpA, "Node Expansion Limit", "Solution Cost", "../../../plots/Experiment2AViolin" + instance + ".pdf")

    makeDifferencePlot(13, 10, "Node Expansion Limit", "Algorithm Cost - A* Cost", instanceDataDiffExp, 0.35, "Algorithm", limits, algorithmsExpA, "Node Expansion Limit", "Algorithm Cost - A* Cost", "../../../plots/Experiment2ADifference" + instance + ".pdf", markers)

    '''
    makeViolinPlot(13, 10, "Node Expansion Limit", "Solution Cost", instanceDataExp, 0.53, "Algorithm", limits, algorithmsExpB, "Node Expansion Limit", "Solution Cost", "../../../plots/Experiment2BViolin" + instance + ".pdf")

    makeDifferencePlot(13, 10, "Node Expansion Limit", "Algorithm Cost - A* Cost", instanceDataDiffExp, 0.35, "Algorithm", limits, algorithmsExpB, "Node Expansion Limit", "Algorithm Cost - A* Cost", "../../../plots/Experiment2BDifference" + instance + ".pdf", markers)

    makeViolinPlot(13, 10, "Node Expansion Limit", "Solution Cost", instanceDataExp, 0.59, "Algorithm", limits, algorithmsExpC, "Node Expansion Limit", "Solution Cost", "../../../plots/Experiment2CViolin" + instance + ".pdf")

    makeDifferencePlot(13, 10, "Node Expansion Limit", "Algorithm Cost - A* Cost", instanceDataDiffExp, 0.35, "Algorithm", limits, algorithmsExpC, "Node Expansion Limit", "Algorithm Cost - A* Cost", "../../../plots/Experiment2CDifference" + instance + ".pdf", markers)

    makeDifferencePlot(13, 10, "Node Expansion Limit", "Algorithm Cost - A* Cost", instanceDataDiffExp, 0.35, "Algorithm", limits, algorithmsExpC, "Node Expansion Limit", "Algorithm Cost - A* Cost", "../../../plots/Experiment2CDifference" + instance + "AAAI19Slides.pdf", markers)
    '''