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
algoArr=("LSSLRTA")

testSize=slidingPuzzleFiles
firstInstance=1

maxInstances=$((testSize / availableMachines ))
if ((machineNumber > 1))
then
    firstInstance=$((maxInstances * (machineNumber - 1)))
fi
maxInstances=$((maxInstances+3))


# for algo in "${algoArr[@]}"
# do
#     echo "./nonTrialTests.sh ${firstInstance} ${maxInstances} 1 SlidingPuzzle ${algo} "
#     ./nonTrialTests.sh ${firstInstance} ${maxInstances} 1 SlidingPuzzle ${algo} 
# done


# for algo in "${algoArr[@]}"
# do
#     echo "./nonTrialTests.sh ${firstInstance} ${maxInstances} 1 HeavyTile ${algo} "
#     ./nonTrialTests.sh ${firstInstance} ${maxInstances} 1 HeavyTile ${algo} 
# done




testSize=pancakeFiles
maxInstances=$((testSize / availableMachines ))
if ((machineNumber > 1))
then
    firstInstance=$((maxInstances * (machineNumber - 1)))
fi
maxInstances=$((maxInstances+3))
# for algo in "${algoArr[@]}"
# do
#     echo "./nonTrialTests.sh ${firstInstance} ${maxInstances} 1 Pancake ${algo} 10"
#     ./nonTrialTests.sh ${firstInstance} ${maxInstances} 1 Pancake ${algo} 10
# done

for algo in "${algoArr[@]}"
do
    echo "./nonTrialTests.sh ${firstInstance} ${maxInstances} 1 PancakeDPS ${algo} 10"
    ./nonTrialTests.sh ${firstInstance} ${maxInstances} 1 PancakeDPS ${algo} 10
done




# testSize=treeWorldFiles
# maxInstances=$((testSize / availableMachines ))
# if ((machineNumber > 1))
# then
#     firstInstance=$((maxInstances * (machineNumber - 1)))
# fi
# maxInstances=$((maxInstances+3))
# for algo in "${algoArr[@]}"
# do
#     echo "./nonTrialTests.sh ${firstInstance} ${maxInstances} 1 PancakeDPS ${algo} "
#     ./nonTrialTests.sh ${firstInstance} ${maxInstances} 1 TreeWorld ${algo} 
# done
