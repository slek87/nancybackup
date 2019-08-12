#!/bin/bash

algoArr=("UCT-H" "GUCT-H" "UCTS-H" "GUCTS-H" "UCTnancy-H" "GUCTnancy-H" "UCTSnancy-H" "GUCTSnancy-H" "UCTie-H" "GUCTie-H" "UCTSie-H" "GUCTSie-H" "UCTiep-H" "GUCTiep-H" "UCTSiep-H" "GUCTSiep-H" "WAS-H" "WASie-H" "WASiep-H" "WASnancy-H" "UCT-F" "GUCT-F" "UCTS-F" "GUCTS-F" "UCTnancy-F" "GUCTnancy-F" "UCTSnancy-F" "GUCTSnancy-F" "UCTie-F" "GUCTie-F" "UCTSie-F" "GUCTSie-F" "UCTiep-F" "GUCTiep-F" "UCTSiep-F" "GUCTSiep-F" "WAS-F" "WASie-F" "WASiep-F" "WASnancy-F" "FHAT" "RISK" "IE" "IEP" "LSSLRTA")

default=true

domainType="All"
reverse=""
tout=180

if [ "$1" = "help" ] || [ "$1" = "-help" ] || [ "$1" = "?" ] || [ "$1" = "-h" ]
then
  echo "./makepancakes.sh [-d domain] [-t timelimit] [-r test in reverse order]"
  echo "Default: runs all domain in ascending order of instances with timelimit of 180ms" 

  exit 1
fi

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
        if [ $? -eq 1 ]
        then
            exit 1
        fi
    done

    for algo in "${algoArr[@]}"
    do
        echo "./expansionTest${reverse}.sh 1 100 1 Pancake ${algo} ${tout} "
        ./expansionTest${reverse}.sh 1 100 1 Pancake ${algo} ${tout} 10
        if [ $? -eq 1 ]
        then
            exit 1
        fi
    done

    for algo in "${algoArr[@]}"
    do
        echo "./expansionTest${reverse}.sh 1 100 1 PancakeDPS ${algo} ${tout} "
        ./expansionTest${reverse}.sh 1 100 1 PancakeDPS ${algo} ${tout}
        if [ $? -eq 1 ]
        then
            exit 1
        fi
    done

    for algo in "${algoArr[@]}"
    do
        echo "./expansionTest${reverse}.sh 1 1000 1 TreeWorld ${algo} ${tout} "
        ./expansionTest${reverse}.sh 1 1000 1 TreeWorld ${algo} ${tout}
        if [ $? -eq 1 ]
        then
            exit 1
        fi
    done

    for algo in "${algoArr[@]}"
    do
        echo "./expansionTest${reverse}.sh 1 100 1 HeavyTile ${algo} ${tout} "
        ./expansionTest${reverse}.sh 1 100 1 HeavyTile ${algo} ${tout} 
        if [ $? -eq 1 ]
        then
            exit 1
        fi
    done

    for algo in "${algoArr[@]}"
    do
        echo "./expansionTest${reverse}.sh 1 100 1 InverseTile ${algo} ${tout} "
        ./expansionTest${reverse}.sh 1 100 1 InverseTile ${algo} ${tout} 
        if [ $? -eq 1 ]
        then
            exit 1
        fi
    done
elif [ "$domainType" = "SlidingPuzzle" ] ||  [ "$domainType" = "HeavyTile" ] ||  [ "$domainType" = "InverseTile" ] || [ "$domainType" = "Pancake" ] ||  [ "$domainType" = "PancakeDPS" ] 
then
    for algo in "${algoArr[@]}"
    do
        echo "./expansionTest${reverse}.sh 1 1000 1 ${domainType} ${algo} ${tout} "
        ./expansionTest${reverse}.sh 1 100 1 ${domainType} ${algo} ${tout}
        if [ $? -eq 1 ]
        then
            exit 1
        fi
    done
elif [ "$domainType" = "TreeWorld" ] 
then
    for algo in "${algoArr[@]}"
    do
        echo "./expansionTest${reverse}.sh 1 100 1 ${domainType} ${algo} ${tout} "
        ./expansionTest${reverse}.sh 1 100 1 ${domainType} ${algo} ${tout} 
        if [ $? -eq 1 ]
        then
            exit 1
        fi
    done
else
    echo "Invalid domain!"
    exit 1
fi





