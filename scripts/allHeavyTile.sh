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

# Starting trial based real-time search

algoArr=("UCT" "GUCT" "UCTS" "GUCTS" "UCTnancy" "GUCTnancy" "UCTSnancy" "GUCTSnancy" "UCTie" "GUCTie" "UCTSie" "GUCTSie")

testSize=slidingPuzzleFiles
firstInstance=$(( (machineNumber - 1) * testSize / availableMachines + 1 ))
maxInstances=$((1 + testSize / availableMachines ))


for algo in "${algoArr[@]}"
do
    echo "./trialTests.sh ${firstInstance} ${maxInstances} 2 HeavyTile ${algo} "
    ./trialTests.sh ${firstInstance} ${maxInstances} 2 HeavyTile ${algo} 
done


algoArr=("FHAT RISK IE LSSLRTA")

testSize=slidingPuzzleFiles
firstInstance=$(( (machineNumber - 1) * testSize / availableMachines + 1 ))
maxInstances=$((1 + testSize / availableMachines ))


for algo in "${algoArr[@]}"
do
    echo "./nonTrialTests.sh ${firstInstance} ${maxInstances} 2 HeavyTile ${algo} "
    ./nonTrialTests.sh ${firstInstance} ${maxInstances} 2 HeavyTile ${algo} 
done

