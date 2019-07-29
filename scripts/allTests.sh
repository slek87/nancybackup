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
    echo "./trialTests.sh ${firstInstance} ${maxInstances} 1 SlidingPuzzle ${algo} "
    ./trialTests.sh ${firstInstance} ${maxInstances} 1 SlidingPuzzle ${algo} 
done

for algo in "${algoArr[@]}"
do
    echo "./trialTests.sh ${firstInstance} ${maxInstances} 1 HeavyTile ${algo} "
    ./trialTests.sh ${firstInstance} ${maxInstances} 1 HeavyTile ${algo} 
done



testSize=pancakeFiles
firstInstance=$(( (machineNumber - 1) * testSize / availableMachines + 1 ))
maxInstances=$((1 + testSize / availableMachines ))
for algo in "${algoArr[@]}"
do
    echo "./trialTests.sh ${firstInstance} ${maxInstances} 1 Pancake ${algo} "
    ./trialTests.sh ${firstInstance} ${maxInstances} 1 Pancake ${algo} 10
done

for algo in "${algoArr[@]}"
do
    echo "./trialTests.sh ${firstInstance} ${maxInstances} 1 PancakeDPS ${algo} "
    ./trialTests.sh ${firstInstance} ${maxInstances} 1 PancakeDPS ${algo} 10
done



testSize=treeWorldFiles
firstInstance=$(( (machineNumber - 1) * testSize / availableMachines + 1 ))
maxInstances=$((1 + testSize / availableMachines ))
for algo in "${algoArr[@]}"
do
    echo "./trialTests.sh ${firstInstance} ${maxInstances} 1 TreeWorld ${algo} "
    ./trialTests.sh ${firstInstance} ${maxInstances} 1 TreeWorld ${algo} 
done



# testSize=slidingPuzzleFiles
# firstInstance=$(( (machineNumber - 1) * testSize / availableMachines + 1 ))
# maxInstances=$((1 + testSize / availableMachines ))
# for algo in "${algoArr[@]}"
# do
#     echo "./trialTests.sh ${firstInstance} ${maxInstances} 1 InverseTile ${algo} "
#     ./trialTests.sh ${firstInstance} ${maxInstances} 1 InverseTile ${algo} 
# done




# Starting non real-time search

algoArr=("FHAT RISK IE LSSLRTA")

testSize=slidingPuzzleFiles
firstInstance=$(( (machineNumber - 1) * testSize / availableMachines + 1 ))
maxInstances=$((1 + testSize / availableMachines ))
for algo in "${algoArr[@]}"
do
    echo "./nonTrialTests.sh ${firstInstance} ${maxInstances} 1 SlidingPuzzle ${algo} "
    ./nonTrialTests.sh ${firstInstance} ${maxInstances} 1 SlidingPuzzle ${algo} 
done

for algo in "${algoArr[@]}"
do
    echo "./nonTrialTests.sh ${firstInstance} ${maxInstances} 1 HeavyTile ${algo} "
    ./nonTrialTests.sh ${firstInstance} ${maxInstances} 1 HeavyTile ${algo} 
done




testSize=pancakeFiles
firstInstance=$(( (machineNumber - 1) * testSize / availableMachines + 1 ))
maxInstances=$((1 + testSize / availableMachines ))
for algo in "${algoArr[@]}"
do
    echo "./nonTrialTests.sh ${firstInstance} ${maxInstances} 1 Pancake ${algo} 10"
    ./nonTrialTests.sh ${firstInstance} ${maxInstances} 1 Pancake ${algo} 10
done

for algo in "${algoArr[@]}"
do
    echo "./nonTrialTests.sh ${firstInstance} ${maxInstances} 1 PancakeDPS ${algo} 10"
    ./nonTrialTests.sh ${firstInstance} ${maxInstances} 1 PancakeDPS ${algo} 10
done




testSize=treeWorldFiles
firstInstance=$(( (machineNumber - 1) * testSize / availableMachines + 1 ))
maxInstances=$((1 + testSize / availableMachines ))
for algo in "${algoArr[@]}"
do
    echo "./nonTrialTests.sh ${firstInstance} ${maxInstances} 1 PancakeDPS ${algo} "
    ./nonTrialTests.sh ${firstInstance} ${maxInstances} 1 TreeWorld ${algo} 
done



firstInstance=$(( (machineNumber - 1) * testSize / availableMachines + 1 ))
maxInstances=$((1 + testSize / availableMachines ))
for algo in "${algoArr[@]}"
do
    echo "./nonTrialTests.sh ${firstInstance} ${maxInstances} 1 SlidingPuzzle ${algo} "
    ./nonTrialTests.sh ${firstInstance} ${maxInstances} 1 SlidingPuzzle ${algo} 
done



# firstInstance=$(( (machineNumber - 1) * testSize / availableMachines + 1 ))
# maxInstances=$((1 + testSize / availableMachines ))
# for algo in "${algoArr[@]}"
# do
#     echo "./nonTrialTests.sh ${firstInstance} ${maxInstances} 1 InverseTile ${algo} "
#     ./nonTrialTests.sh ${firstInstance} ${maxInstances} 1 InverseTile ${algo} 
# done