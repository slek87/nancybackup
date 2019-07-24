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
algoArr=("UCT" "GUCT" "UCTS" "GUCTS" "UCTN" "GUCTN" "UCTIE" "GUCTIE")
decArr=("-" "minimin" "nancy")

testSize=slidingPuzzleFiles
firstInstance=1

maxInstances=$((testSize / availableMachines ))
if ((machineNumber > 1))
then
    firstInstance=$((maxInstances * (machineNumber - 1)))
fi
maxInstances=$((maxInstances+3))

for dec in "${decArr[@]}"
do
    for algo in "${algoArr[@]}"
    do
        echo "./trialTests.sh ${firstInstance} ${maxInstances} 1 SlidingPuzzle ${algo} ${dec}"
        ./trialTests.sh ${firstInstance} ${maxInstances} 1 SlidingPuzzle ${algo} ${dec}
    done
done


maxInstances=$((testSize / availableMachines ))
if ((machineNumber > 1))
then
    firstInstance=$((maxInstances * (machineNumber - 1)))
fi
maxInstances=$((maxInstances+3))

for dec in "${decArr[@]}"
do
    for algo in "${algoArr[@]}"
    do
        echo "./trialTests.sh ${firstInstance} ${maxInstances} 1 HeavyTile ${algo} ${dec}"
        ./trialTests.sh ${firstInstance} ${maxInstances} 1 HeavyTile ${algo} ${dec}
    done
done



testSize=pancakeFiles
maxInstances=$((testSize / availableMachines ))
if ((machineNumber > 1))
then
    firstInstance=$((maxInstances * (machineNumber - 1)))
fi
maxInstances=$((maxInstances+3))

for dec in "${decArr[@]}"
do
    for algo in "${algoArr[@]}"
    do
        echo "./trialTests.sh ${firstInstance} ${maxInstances} 1 Pancake ${algo} ${dec}"
        ./trialTests.sh ${firstInstance} ${maxInstances} 1 Pancake ${algo} ${dec}
    done
done

maxInstances=$((testSize / availableMachines ))
if ((machineNumber > 1))
then
    firstInstance=$((maxInstances * (machineNumber - 1)))
fi
maxInstances=$((maxInstances+3))

for dec in "${decArr[@]}"
do
    for algo in "${algoArr[@]}"
    do
        echo "./trialTests.sh ${firstInstance} ${maxInstances} 1 PancakeDPS ${algo} ${dec}"
        ./trialTests.sh ${firstInstance} ${maxInstances} 1 PancakeDPS ${algo} ${dec}
    done
done



testSize=treeWorldFiles
maxInstances=$((testSize / availableMachines ))
if ((machineNumber > 1))
then
    firstInstance=$((maxInstances * (machineNumber - 1)))
fi
maxInstances=$((maxInstances+3))

for dec in "${decArr[@]}"
do
    for algo in "${algoArr[@]}"
    do
        echo "./trialTests.sh ${firstInstance} ${maxInstances} 1 PancakeDPS ${algo} ${dec}"
        ./trialTests.sh ${firstInstance} ${maxInstances} 1 TreeWorld ${algo} ${dec}
    done
done