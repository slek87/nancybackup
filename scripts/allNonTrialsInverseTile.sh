#!/bin/bash

if (($# < 1))
then
  echo "./executable [total #] [machine #] "
  exit 1
fi
availableMachines=$1
machineNumber=$2
slidingPuzzleFiles=100
treeWorldFiles=1000
pancakeFiles=200
# dec="-"
algoArr=("FHAT RISK IE")

testSize=slidingPuzzleFiles
firstInstance=1

maxInstances=$((testSize / availableMachines ))
if ((machineNumber > 1))
then
    firstInstance=$((maxInstances * (machineNumber - 1)))
fi
maxInstances=$((maxInstances+3))


for algo in "${algoArr[@]}"
do
    echo "./nonTrialTests2.sh ${firstInstance} ${maxInstances} 1 InverseTile ${algo} "
    ./nonTrialTests2.sh ${firstInstance} ${maxInstances} 1 InverseTile ${algo} 
done

