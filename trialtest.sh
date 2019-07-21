#!/bin/bash

if [ "$1" = "help" ] || [ "$1" = "-help" ] || [ "$1" = "?" ]
then
  echo "./executable [starting instance #] [# of instances to test] [# of processes] [Domain Type] [TrialBased Algorithm] [Decision Algorithm]"
  exit 1
fi

if (($# < 4))
then
  echo "./executable [starting instance #] [# of instances to test] [# of processes] [Domain Type] [TrialBased Algorithm] [Decision Algorithm]"
  exit 1
fi

# Which instance to start testing on
firstInstance=$1

# The maximum number of instances to test on
maxInstances=$2
lastInstance=$(( $firstInstance + $maxInstances ))

# Max number of background processes to start, should probably not be more than the number of cores on the machine
maxProcs=$3

# The domain to run on
domainType=$4
# lookahead=$5
lookaheadArr=(10 30 100 300 1000)

trialAlgorithm=$5
decisionAlgorithm=$6

numProcs=0

echo "At Algorithm ${trialAlgorithm}"
for lookahead in "${lookaheadArr[@]}"
do
    echo "At lookahead ${lookahead}"
    if [ "$domainType" = "SlidingPuzzle" ] ||  [ "$domainType" = "HeavyTile" ]
    then
        dimensions=4
        mkdir -p ./results/${domainType}/${dimensions}x${dimensions}/LA${lookahead}
        instance=$firstInstance
        while ((instance < lastInstance))
        do
            echo "${instance}-${dimensions}x${dimensions}"
            file="../../worlds/slidingTile/${instance}-${dimensions}x${dimensions}.st"
            if ((numProcs >= ${maxProcs}))
            then
                wait
                numProcs=0
            fi		  
            if [ -f ./results/${domainType}/${dimensions}x${dimensions}/LA${lookahead}/${instance}-${dimensions}x${dimensions}.csv ]
            then 
                let instance++
            else
                if (( instance + 1 == lastInstance ))
                then
                    timeout 30 ./expansionTest ${domainType} ${lookahead} ${trialAlgorithm} ${decisionAlgorithm}  ./results/${domainType}/${dimensions}x${dimensions}/LA${lookahead}/${instance}-${dimensions}x${dimensions}.csv < ${file}
                else
                    timeout 30 ./expansionTest ${domainType} ${lookahead} ${trialAlgorithm} ${decisionAlgorithm}  ./results/${domainType}/${dimensions}x${dimensions}/LA${lookahead}/${instance}-${dimensions}x${dimensions}.csv < ${file} &
                fi
                let instance++
                let numProcs++
            fi
        done
    elif [ "$domainType" = "TreeWorld" ]
    then
        mkdir -p ./results/${domainType}/LA${lookahead}
        instance=$firstInstance
        while ((instance < lastInstance))
        do
        echo "b2d100-${instance}"
        file="../../worlds/treeWorld/b2d100-${instance}.tw"
        if ((numProcs >= ${maxProcs}))
        then
            wait
            numProcs=0
        fi		  
        if [ -f ./results/${domainType}/LA${lookahead}/b2d100-${instance}.csv ]
        then 
            let instance++
        else
            if (( instance + 1 == lastInstance ))
            then
                timeout 30 ./expansionTest ${domainType} ${lookahead} ${trialAlgorithm} ${decisionAlgorithm}  ./results/${domainType}/LA${lookahead}/b2d100-${instance}.csv < ${file}
            else
                timeout 30 ./expansionTest ${domainType} ${lookahead} ${trialAlgorithm} ${decisionAlgorithm}  ./results/${domainType}/LA${lookahead}/b2d100-${instance}.csv < ${file} &
            fi
            let instance++
            let numProcs++
        fi
        done
    elif [ "$domainType" = "Pancake" ] ||  [ "$domainType" = "PancakeDPS" ]
    then
        if (($# < 5))
        then
        echo "./executable [starting instance #] [# of instances to test] [# of processes] [Domain Type] [Pancake Size]"
        exit 1
        fi
        dimensions=$7
        mkdir -p ./results/${domainType}/${dimensions}/LA${lookahead}
        instance=$firstInstance
        while ((instance < lastInstance))
        do
        file="../../worlds/pancake/${dimensions}/${instance}-${dimensions}.pan"
        if ((numProcs >= ${maxProcs}))
        then
            wait
            numProcs=0
        fi		  
        if [ -f ./results/${domainType}/${dimensions}/LA${lookahead}/${instance}-${dimensions}.csv ]
        then 
            let instance++
        else
        echo "${instance}-${dimensions}"
        if (( instance + 1 == lastInstance ))
            then
                timeout 30 ./expansionTest ${domainType} ${lookahead} ${trialAlgorithm} ${decisionAlgorithm}  ./results/${domainType}/${dimensions}/LA${lookahead}/${instance}-${dimensions}.csv < ${file}
            else
                timeout 30 ./expansionTest ${domainType} ${lookahead} ${trialAlgorithm} ${decisionAlgorithm}  ./results/${domainType}/${dimensions}/LA${lookahead}/${instance}-${dimensions}.csv < ${file} &
            fi

            let instance++
        let numProcs++
        fi
        done
    else
    echo "Error"
    exit 1
    fi
done