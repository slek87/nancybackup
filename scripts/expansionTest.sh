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
timelimit=$6

numProcs=0
notSolved=0
for lookahead in "${lookaheadArr[@]}"
do
    if (( notSolved > 2 ))
    then
         echo "Few instances cannot be solved within the time limit(${timelimit} s) , perhaps try try larger timeout?"
         exit 1
    fi

    echo "Domain:${domainType} Lookahead:${lookahead} Algorithm:${algorithm}"
    if [ "$domainType" = "SlidingPuzzle" ] ||  [ "$domainType" = "HeavyTile" ] ||  [ "$domainType" = "InverseTile" ]
    then
        if [ "$domainType" = "InverseTile" ]
            then
            if (( lookahead == 1000 ))
            then
                exit 0
            fi
        fi
        dimensions=4
        mkdir -p ../../results/${algorithm}/${domainType}/${dimensions}x${dimensions}/LA${lookahead}
        instance=1
        while ((instance < lastInstance))
        do
            file="../../worlds/slidingTile/${instance}-${dimensions}x${dimensions}.st"
  
            if [ -f ../../results/${algorithm}/${domainType}/${dimensions}x${dimensions}/LA${lookahead}/${instance}-${dimensions}x${dimensions}.csv ] || [ -f ../../results/${algorithm}/${domainType}/${dimensions}x${dimensions}/LA${lookahead}/${instance}.tmp ]
            then 
                let instance++
            else
                echo "${instance}-${dimensions}x${dimensions}"
                echo "A" > ../../results/${algorithm}/${domainType}/${dimensions}x${dimensions}/LA${lookahead}/${instance}.tmp
                if [[ $algorithm == *"UCT"* ]] || [[ $algorithm == *"WAS"* ]]
                then
                    timeout ${timelimit} ../../build_release/trialBasedTest ${domainType} ${lookahead} ${algorithm}   ../../results/${algorithm}/${domainType}/${dimensions}x${dimensions}/LA${lookahead}/${instance}-${dimensions}x${dimensions}.csv < ${file}
                else
                    timeout ${timelimit} ../../build_release/${algorithm}expansionTest ${domainType} ${lookahead}  ../../results/${algorithm}/${domainType}/${dimensions}x${dimensions}/LA${lookahead}/${instance}-${dimensions}x${dimensions}.csv < ${file}
                fi
                wait

                if [ ! -f ../../results/${algorithm}/${domainType}/${dimensions}x${dimensions}/LA${lookahead}/${instance}-${dimensions}x${dimensions}.csv ]
                then
                    echo "Time limit(${timelimit} s) reached: ${instance}"
                    let notSolved++
                fi

                rm ../../results/${algorithm}/${domainType}/${dimensions}x${dimensions}/LA${lookahead}/${instance}.tmp
                let instance++
            fi
        done
    elif [ "$domainType" = "TreeWorld" ]
    then
        mkdir -p ../../results/${algorithm}/${domainType}/LA${lookahead}
        instance=1
        while ((instance < lastInstance))
        do
            file="../../worlds/treeWorld/b2d100-${instance}.tw"
        
            if [ -f ../../results/${algorithm}/${domainType}/LA${lookahead}/b2d100-${instance}.csv ] || [ -f ../../results/${algorithm}/${domainType}/LA${lookahead}/${instance}.tmp ]
            then 
                let instance++
            else
                echo "b2d100-${instance}"
                echo "A" > ../../results/${algorithm}/${domainType}/LA${lookahead}/${instance}.tmp
                if [[ $algorithm == *"UCT"* ]] || [[ $algorithm == *"WAS"* ]]
                then
                    timeout ${timelimit} ../../build_release/trialBasedTest ${domainType} ${lookahead} ${algorithm}   ../../results/${algorithm}/${domainType}/LA${lookahead}/b2d100-${instance}.csv < ${file}
                else
                    timeout ${timelimit} ../../build_release/${algorithm}expansionTest ${domainType} ${lookahead}  ../../results/${algorithm}/${domainType}/LA${lookahead}/b2d100-${instance}.csv < ${file}
                fi
                wait

                if [ ! -f ../../results/${algorithm}/${domainType}/LA${lookahead}/b2d100-${instance}.csv ]
                then
                    echo "Time limit(${timelimit} s)  reached: ${instance}"
                    let notSolved++
                fi

                rm ../../results/${algorithm}/${domainType}/LA${lookahead}/${instance}.tmp
                let instance++
            fi
        done
    elif [ "$domainType" = "Pancake" ] ||  [ "$domainType" = "PancakeDPS" ]
    then
        if (($# < 5))
        then
            echo "./executable [starting instance #] [# of instances to test] [# of processes] [Domain Type] [Pancake Size]"
            exit 1
        fi
            dimensions=10
            mkdir -p ../../results/${algorithm}/${domainType}/${dimensions}/LA${lookahead}
            instance=1
        while ((instance < lastInstance))
        do
            file="../../worlds/pancake/${dimensions}/${instance}-${dimensions}.pan"
        
            if [ -f ../../results/${algorithm}/${domainType}/${dimensions}/LA${lookahead}/${instance}-${dimensions}.csv ] || [ -f ../../results/${algorithm}/${domainType}/${dimensions}/LA${lookahead}/${instance}.tmp ]
            then 
                let instance++
            else
                echo "${instance}-${dimensions}"
                echo "A" > ../../results/${algorithm}/${domainType}/${dimensions}/LA${lookahead}/${instance}.tmp
                if [[ $algorithm == *"UCT"* ]] || [[ $algorithm == *"WAS"* ]]
                then
                    timeout ${timelimit} ../../build_release/trialBasedTest ${domainType} ${lookahead} ${algorithm}   ../../results/${algorithm}/${domainType}/${dimensions}/LA${lookahead}/${instance}-${dimensions}.csv < ${file}
                else
                    timeout ${timelimit} ../../build_release/${algorithm}expansionTest ${domainType} ${lookahead}  ../../results/${algorithm}/${domainType}/${dimensions}/LA${lookahead}/${instance}-${dimensions}.csv < ${file}
                fi
                wait

                if [ ! -f ../../results/${algorithm}/${domainType}/${dimensions}/LA${lookahead}/${instance}-${dimensions}.csv ]
                then
                    echo "Time limit(${timelimit} s)  reached: ${instance}"
                    let notSolved++
                fi

                rm ../../results/${algorithm}/${domainType}/${dimensions}/LA${lookahead}/${instance}.tmp
                let instance++
            fi
        done
    else
    echo "Error"
    exit 1
    fi
done