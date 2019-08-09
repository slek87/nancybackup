#!/bin/bash

# algoArr=("UCT" "GUCT" "UCTS" "GUCTS" "UCTnancy" "GUCTnancy" "UCTSnancy" "GUCTSnancy" "UCTie" "GUCTie" "UCTSie" "GUCTSie" "WAS" "WASie" "WASnancy" "FHAT" "RISK" "IE" "IEP" "LSSLRTA")
algoArr=("IEP" "IE")


default=true

domainType="All"
reverse=""
tout=180

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

    if [ ${!i} == "-t" ]; then
        if [ $((i+1)) -le "$#" ]; then
            var=$((i+1))
            tout=${!var}
        fi
    fi
done



if [ "$domainType" = "All" ] 
then
    for algo in "${algoArr[@]}"
    do
        echo "./expansionTest${reverse}.sh 1 100 1 SlidingPuzzle ${algo} ${tout} "
        ./expansionTest${reverse}.sh 1 100 1 SlidingPuzzle ${algo} ${tout} 
        wait
    done

    for algo in "${algoArr[@]}"
    do
        echo "./expansionTest${reverse}.sh 1 100 1 Pancake ${algo} ${tout} "
        ./expansionTest${reverse}.sh 1 100 1 Pancake ${algo} ${tout} 10
        wait
    done

    for algo in "${algoArr[@]}"
    do
        echo "./expansionTest${reverse}.sh 1 100 1 PancakeDPS ${algo} ${tout} "
        ./expansionTest${reverse}.sh 1 100 1 PancakeDPS ${algo} ${tout}
        wait
    done

    for algo in "${algoArr[@]}"
    do
        echo "./expansionTest${reverse}.sh 1 1000 1 TreeWorld ${algo} ${tout} "
        ./expansionTest${reverse}.sh 1 1000 1 TreeWorld ${algo} ${tout}
        wait
    done

    for algo in "${algoArr[@]}"
    do
        echo "./expansionTest${reverse}.sh 1 100 1 HeavyTile ${algo} ${tout} "
        ./expansionTest${reverse}.sh 1 100 1 HeavyTile ${algo} ${tout} 
        wait
    done

    for algo in "${algoArr[@]}"
    do
        echo "./expansionTest${reverse}.sh 1 100 1 InverseTile ${algo} ${tout} "
        # ./expansionTest${reverse}.sh 1 100 1 InverseTile ${algo} ${tout} 
        wait
    done
elif [ "$domainType" = "SlidingPuzzle" ] ||  [ "$domainType" = "HeavyTile" ] ||  [ "$domainType" = "InverseTile" ] || [ "$domainType" = "Pancake" ] ||  [ "$domainType" = "PancakeDPS" ] 
then
    for algo in "${algoArr[@]}"
    do
        echo "./expansionTest${reverse}.sh 1 1000 1 ${domainType} ${algo} ${tout} "
        ./expansionTest${reverse}.sh 1 100 1 ${domainType} ${algo} ${tout}
        wait
    done
elif [ "$domainType" = "TreeWorld" ] 
then
    for algo in "${algoArr[@]}"
    do
        echo "./expansionTest${reverse}.sh 1 100 1 ${domainType} ${algo} ${tout} "
        ./expansionTest${reverse}.sh 1 100 1 ${domainType} ${algo} ${tout} 
        wait
    done
else
    echo "Invalid domain!"
    exit 1
fi





