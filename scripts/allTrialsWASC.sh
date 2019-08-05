#!/bin/bash

algoArr=("WAS" "WASie" "WASnancy")

for algo in "${algoArr[@]}"
do
    echo "./trialTestsC.sh 1 100 1 SlidingPuzzle ${algo} "
    ./trialTestsC.sh 1 100 1 SlidingPuzzle ${algo} 
done

for algo in "${algoArr[@]}"
do
    echo "./trialTestsC.sh 1 100 1 HeavyTile ${algo} "
    ./trialTestsC.sh 1 100 1 HeavyTile ${algo} 
done

for algo in "${algoArr[@]}"
do
    echo "./trialTestsC.sh 1 1000 1 TreeWorld ${algo} "
    ./trialTestsC.sh 1 100 1 TreeWorld ${algo} 
done

for algo in "${algoArr[@]}"
do
    echo "./trialTestsC.sh 1 100 1 Pancake ${algo} "
    ./trialTestsC.sh 1 100 1 Pancake ${algo} 10
done

for algo in "${algoArr[@]}"
do
    echo "./trialTestsC.sh 1 100 1 PancakeDPS ${algo} "
    ./trialTestsC.sh 1 100 1 PancakeDPS ${algo} 10
done

# testSize=slidingPuzzleFiles
# firstInstance=$(( (machineNumber - 1) * testSize / availableMachines + 1 ))
# maxInstances=$((1 + testSize / availableMachines ))
# for algo in "${algoArr[@]}"
# do
#     echo "./trialTestsC.sh 1 100 1 InverseTile ${algo} "
#     ./trialTestsC.sh 1 100 1 InverseTile ${algo} 
# done

