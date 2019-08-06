#!/bin/bash

if [ "$1" = "help" ] || [ "$1" = "-help" ] || [ "$1" = "?" ]
then
  echo "./executable [starting instance #] [# of instances to test] [# of processes] [Domain Type] [TrialBased Algorithm]"
  exit 1
fi

if (($# < 4))
then
  echo "./executable [starting instance #] [# of instances to test] [# of processes] [Domain Type] [TrialBased Algorithm]"
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

algorithm=$5

numProcs=0

for lookahead in "${lookaheadArr[@]}"
do
    echo "Domain:${domainType} Lookahead:${lookahead} Algorithm:${algorithm}"
    if [ "$domainType" = "SlidingPuzzle" ] ||  [ "$domainType" = "HeavyTile" ] ||  [ "$domainType" = "InverseTile" ]
    then
        if [ "$domainType" = "InverseTile" ] || [ "$domainType" = "HeavyTile" ]
            then
            if (( lookahead == 300 )) || (( lookahead == 1000 ))
            then
                exit 0
            fi
        fi

        dimensions=4
        mkdir -p ../../results/${algorithm}2/${domainType}/${dimensions}x${dimensions}/LA${lookahead}
        instance=$lastInstance
        while ((instance > 0))
        do
            echo "${instance}-${dimensions}x${dimensions}"
            file="../../worlds/slidingTile/${instance}-${dimensions}x${dimensions}.st"
  
            if [ -f ../../results/${algorithm}2/${domainType}/${dimensions}x${dimensions}/LA${lookahead}/${instance}-${dimensions}x${dimensions}.csv ] || [ -f ../../results/${algorithm}2/${domainType}/${dimensions}x${dimensions}/LA${lookahead}/${instance} ]
            then 
                let instance--
            else
                echo "A" > ../../results/${algorithm}2/${domainType}/${dimensions}x${dimensions}/LA${lookahead}/${instance}
                if [[ $algorithm == *"UCT"* ]] || [[ $algorithm == *"WAS"* ]]
                then
                    timeout 270 ../../build_release/trialBasedTest2 ${domainType} ${lookahead} ${algorithm}   ../../results/${algorithm}2/${domainType}/${dimensions}x${dimensions}/LA${lookahead}/${instance}-${dimensions}x${dimensions}.csv < ${file}
                else
                    timeout 270 ../../build_release/${algorithm}expansionTest ${domainType} ${lookahead}  ../../results/${algorithm}2/${domainType}/${dimensions}x${dimensions}/LA${lookahead}/${instance}-${dimensions}x${dimensions}.csv < ${file}
                fi
                rm ../../results/${algorithm}2/${domainType}/${dimensions}x${dimensions}/LA${lookahead}/${instance}
                let instance--
            fi
        done
    elif [ "$domainType" = "TreeWorld" ]
    then
        mkdir -p ../../results/${algorithm}2/${domainType}/LA${lookahead}
        instance=$lastInstance
        while ((instance > 0))
        do
            echo "b2d100-${instance}"
            file="../../worlds/treeWorld/b2d100-${instance}.tw"
        
            if [ -f ../../results/${algorithm}2/${domainType}/LA${lookahead}/b2d100-${instance}.csv ] || [ -f ../../results/${algorithm}2/${domainType}/LA${lookahead}/{instance} ]
            then 
                let instance--
            else
                echo "A" > ../../results/${algorithm}2/${domainType}/LA${lookahead}/${instance}
                if [[ $algorithm == *"UCT"* ]] || [[ $algorithm == *"WAS"* ]]
                then
                    timeout 270 ../../build_release/trialBasedTest2 ${domainType} ${lookahead} ${algorithm}   ../../results/${algorithm}2/${domainType}/LA${lookahead}/b2d100-${instance}.csv < ${file}
                else
                    timeout 270 ../../build_release/${algorithm}expansionTest ${domainType} ${lookahead}  ../../results/${algorithm}2/${domainType}/LA${lookahead}/b2d100-${instance}.csv < ${file}
                fi
                rm ../../results/${algorithm}2/${domainType}/LA${lookahead}/${instance}
                let instance--
            fi
        done
    elif [ "$domainType" = "Pancake" ] ||  [ "$domainType" = "PancakeDPS" ]
    then
        if (($# < 5))
        then
            echo "./executable [starting instance #] [# of instances to test] [# of processes] [Domain Type] [Pancake Size]"
            exit 1
        fi
            dimensions=$6
            mkdir -p ../../results/${algorithm}2/${domainType}/${dimensions}/LA${lookahead}
            instance=$lastInstance
        while ((instance > 0))
        do
            echo "${instance}-${dimensions}"
            file="../../worlds/pancake/${dimensions}/${instance}-${dimensions}.pan"
        
            if [ -f ../../results/${algorithm}2/${domainType}/${dimensions}/LA${lookahead}/${instance}-${dimensions}.csv ] || [ -f ../../results/${algorithm}2/${domainType}/${dimensions}/LA${lookahead}/${instance} ]
            then 
                let instance--
            else
                echo "A" > ../../results/${algorithm}2/${domainType}/${dimensions}/LA${lookahead}/${instance}
                if [[ $algorithm == *"UCT"* ]] || [[ $algorithm == *"WAS"* ]]
                then
                    timeout 270 ../../build_release/trialBasedTest2 ${domainType} ${lookahead} ${algorithm}   ../../results/${algorithm}2/${domainType}/${dimensions}/LA${lookahead}/${instance}-${dimensions}.csv < ${file}
                else
                    timeout 270 ../../build_release/${algorithm}expansionTest ${domainType} ${lookahead}  ../../results/${algorithm}2/${domainType}/${dimensions}/LA${lookahead}/${instance}-${dimensions}.csv < ${file}
                fi
                rm ../../results/${algorithm}2/${domainType}/${dimensions}/LA${lookahead}/${instance}
                let instance--
            fi
        done
    else
    echo "Error"
    exit 1
    fi
done