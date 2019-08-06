#!/bin/bash

algoArr=("UCT" "GUCT" "UCTS" "GUCTS" "UCTnancy" "GUCTnancy" "UCTSnancy" "GUCTSnancy" "UCTie" "GUCTie" "UCTSie" "GUCTSie" "WAS" "WASie" "WASnancy" "FHAT" "RISK" "IE" "LSSLRTA")

default=true

domainType="All"
reverse=""

for (( i=1; i <= "$#"; i++ )); do
    if [ ${!i} == "-d" ]; then
        if [ $((i+1)) -le "$#" ]; then
            var=$((i+1))
            domainType=${!var}
        fi
    fi

    if [ ${!i} == "-r" ]; then
        reverse="Rev"
    fi
done



if [ "$domainType" = "All" ] 
then
    for algo in "${algoArr[@]}"
    do
        echo "./expansionTest${reverse}.sh 1 100 1 SlidingPuzzle ${algo} "
        ./expansionTest${reverse}.sh 1 100 1 SlidingPuzzle ${algo} 
        wait
    done

    for algo in "${algoArr[@]}"
    do
        echo "./expansionTest${reverse}.sh 1 100 1 Pancake ${algo} "
        ./expansionTest${reverse}.sh 1 100 1 Pancake ${algo} 10
        wait
    done

    for algo in "${algoArr[@]}"
    do
        echo "./expansionTest${reverse}.sh 1 100 1 PancakeDPS ${algo} "
        ./expansionTest${reverse}.sh 1 100 1 PancakeDPS ${algo} 10
        wait
    done

    for algo in "${algoArr[@]}"
    do
        echo "./expansionTest${reverse}.sh 1 1000 1 TreeWorld ${algo} "
        ./expansionTest${reverse}.sh 1 100 1 TreeWorld ${algo}
        wait
    done

    for algo in "${algoArr[@]}"
    do
        echo "./expansionTest${reverse}.sh 1 100 1 HeavyTile ${algo} "
        ./expansionTest${reverse}.sh 1 100 1 HeavyTile ${algo} 
        wait
    done

    for algo in "${algoArr[@]}"
    do
        echo "./expansionTest${reverse}.sh 1 100 1 InverseTile ${algo} "
        ./nonexpansionTest${reverse}.sh 1 100 1 InverseTile ${algo} 
        wait
    done
fi


if [ "$domainType" = "SlidingPuzzle" ] ||  [ "$domainType" = "HeavyTile" ] ||  [ "$domainType" = "InverseTile" ] || [ "$domainType" = "Pancake" ] ||  [ "$domainType" = "PancakeDPS" ] 
then
    for algo in "${algoArr[@]}"
    do
        echo "./expansionTest${reverse}.sh 1 1000 1 ${domainType} ${algo} "
        ./expansionTest${reverse}.sh 1 100 1 ${domainType} ${algo} 10
        wait
    done
elif [ "$domainType" = "TreeWorld" ] then
    for algo in "${algoArr[@]}"
    do
        echo "./expansionTest${reverse}.sh 1 100 1 ${domainType} ${algo} "
        ./expansionTest${reverse}.sh 1 100 1 ${domainType} ${algo} 
        wait
    done
else
    echo "Invalid domain!"
    exit 1
fi





