#!/bin/bash

algoArr=("WAS" "WASie" "WASnancy")

for algo in "${algoArr[@]}"
do
    echo "./expansionTest.sh 1 100 1 SlidingPuzzle ${algo} "
    ./expansionTest.sh 1 100 1 SlidingPuzzle ${algo} 
done

for algo in "${algoArr[@]}"
do
    echo "./expansionTest.sh 1 100 1 HeavyTile ${algo} "
    ./expansionTest.sh 1 100 1 HeavyTile ${algo} 
done

for algo in "${algoArr[@]}"
do
    echo "./expansionTest.sh 1 1000 1 TreeWorld ${algo} "
    ./expansionTest.sh 1 100 1 TreeWorld ${algo} 
done

for algo in "${algoArr[@]}"
do
    echo "./expansionTest.sh 1 100 1 Pancake ${algo} "
    ./expansionTest.sh 1 100 1 Pancake ${algo} 10
done

for algo in "${algoArr[@]}"
do
    echo "./expansionTest.sh 1 100 1 PancakeDPS ${algo} "
    ./expansionTest.sh 1 100 1 PancakeDPS ${algo} 10
done

# testSize=slidingPuzzleFiles
# firstInstance=$(( (machineNumber - 1) * testSize / availableMachines + 1 ))
# maxInstances=$((1 + testSize / availableMachines ))
# for algo in "${algoArr[@]}"
# do
#     echo "./expansionTest.sh 1 100 1 InverseTile ${algo} "
#     ./expansionTest.sh 1 100 1 InverseTile ${algo} 
# done

