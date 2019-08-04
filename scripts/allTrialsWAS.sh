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
pancakeFiles=100
firstInstance=0
algoArr=("WAS" "WASie" "WASnancy")

testSize=slidingPuzzleFiles
firstInstance=$(( (machineNumber - 1) * testSize / availableMachines + 1 ))
maxInstances=$((1 + testSize / availableMachines ))
for algo in "${algoArr[@]}"
do
    echo "./trialTestsB.sh ${firstInstance} ${maxInstances} 2 SlidingPuzzle ${algo} "
    ./trialTestsB.sh ${firstInstance} ${maxInstances} 2 SlidingPuzzle ${algo} 
done

for algo in "${algoArr[@]}"
do
    echo "./trialTestsB.sh ${firstInstance} ${maxInstances} 2 HeavyTile ${algo} "
    ./trialTestsB.sh ${firstInstance} ${maxInstances} 2 HeavyTile ${algo} 
done

testSize=treeWorldFiles
firstInstance=$(( (machineNumber - 1) * testSize / availableMachines + 1 ))
maxInstances=$((1 + testSize / availableMachines ))
for algo in "${algoArr[@]}"
do
    echo "./trialTestsB.sh ${firstInstance} ${maxInstances} 2 TreeWorld ${algo} "
    ./trialTestsB.sh ${firstInstance} ${maxInstances} 2 TreeWorld ${algo} 
done


testSize=pancakeFiles
firstInstance=$(( (machineNumber - 1) * testSize / availableMachines + 1 ))
maxInstances=$((1 + testSize / availableMachines ))
for algo in "${algoArr[@]}"
do
    echo "./trialTestsB.sh ${firstInstance} ${maxInstances} 2 Pancake ${algo} "
    ./trialTestsB.sh ${firstInstance} ${maxInstances} 2 Pancake ${algo} 10
done

for algo in "${algoArr[@]}"
do
    echo "./trialTestsB.sh ${firstInstance} ${maxInstances} 2 PancakeDPS ${algo} "
    ./trialTestsB.sh ${firstInstance} ${maxInstances} 2 PancakeDPS ${algo} 10
done

# testSize=slidingPuzzleFiles
# firstInstance=$(( (machineNumber - 1) * testSize / availableMachines + 1 ))
# maxInstances=$((1 + testSize / availableMachines ))
# for algo in "${algoArr[@]}"
# do
#     echo "./trialTestsB.sh ${firstInstance} ${maxInstances} 2 InverseTile ${algo} "
#     ./trialTestsB.sh ${firstInstance} ${maxInstances} 2 InverseTile ${algo} 
# done

