#!/bin/bash

algoArr=("UCT-L" "GUCT-L" "UCTS-L" "GUCTS-L" "UCTnancy-L" "GUCTnancy-L" "UCTSnancy-L" "GUCTSnancy-L" "UCTie-L" "GUCTie-L" "UCTSie-L" "GUCTSie-L" "UCTiep-L" "GUCTiep-L" "UCTSiep-L" "GUCTSiep-L" "WAS-L" "WASie-L" "WASiep-L" "WASnancy-L" "UCT" "GUCT" "UCTS" "GUCTS" "UCTnancy" "GUCTnancy" "UCTSnancy" "GUCTSnancy" "UCTie" "GUCTie" "UCTSie" "GUCTSie" "UCTiep" "GUCTiep" "UCTSiep" "GUCTSiep" "WAS" "WASie" "WASiep" "WASnancy" "FHAT" "RISK" "IE" "IEP" "LSSLRTA")
# algoArr=("UCT" "GUCT" "UCTS" "GUCTS" "UCTnancy" "GUCTnancy" "UCTSnancy" "GUCTSnancy" "UCTie" "GUCTie" "UCTSie" "GUCTSie" "UCTiep" "GUCTiep" "UCTSiep" "GUCTSiep" "WAS" "WASie" "WASiep" "WASnancy" "FHAT" "RISK" "IE" "IEP" "LSSLRTA")
default=true

domainType="All"
reverse=""
tout=300
limitunsolved=3

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

    if [ ${!i} == "-l" ]; then
        if [ $((i+1)) -le "$#" ]; then
            var=$((i+1))
            limitunsolved=${!var}
        fi
    fi
done



if [ "$domainType" = "All" ] 
then
    for algo in "${algoArr[@]}"
    do
        echo "./expansionTest${reverse}.sh 1 100 1 SlidingPuzzle ${algo} ${tout} ${limitunsolved} "
        ./expansionTest${reverse}.sh 1 100 1 SlidingPuzzle ${algo} ${tout} ${limitunsolved} 
        if [ $? -eq 1 ]
        then
            exit 1
        fi
    done

    for algo in "${algoArr[@]}"
    do
        echo "./expansionTest${reverse}.sh 1 100 1 Pancake ${algo} ${tout} ${limitunsolved} "
        ./expansionTest${reverse}.sh 1 100 1 Pancake ${algo} ${tout} ${limitunsolved} 10
        if [ $? -eq 1 ]
        then
            exit 1
        fi
    done

    for algo in "${algoArr[@]}"
    do
        echo "./expansionTest${reverse}.sh 1 100 1 PancakeDPS ${algo} ${tout} ${limitunsolved} "
        ./expansionTest${reverse}.sh 1 100 1 PancakeDPS ${algo} ${tout} ${limitunsolved}
        if [ $? -eq 1 ]
        then
            exit 1
        fi
    done

    for algo in "${algoArr[@]}"
    do
        echo "./expansionTest${reverse}.sh 1 1000 1 TreeWorld ${algo} ${tout} ${limitunsolved} "
        ./expansionTest${reverse}.sh 1 1000 1 TreeWorld ${algo} ${tout} ${limitunsolved}
        if [ $? -eq 1 ]
        then
            exit 1
        fi
    done

    for algo in "${algoArr[@]}"
    do
        echo "./expansionTest${reverse}.sh 1 100 1 HeavyTile ${algo} ${tout} ${limitunsolved} "
        ./expansionTest${reverse}.sh 1 100 1 HeavyTile ${algo} ${tout} ${limitunsolved} 
        if [ $? -eq 1 ]
        then
            exit 1
        fi
    done

    for algo in "${algoArr[@]}"
    do
        echo "./expansionTest${reverse}.sh 1 100 1 InverseTile ${algo} ${tout} ${limitunsolved} "
        ./expansionTest${reverse}.sh 1 100 1 InverseTile ${algo} ${tout} ${limitunsolved} 
        if [ $? -eq 1 ]
        then
            exit 1
        fi
    done
elif [ "$domainType" = "SlidingPuzzle" ] ||  [ "$domainType" = "HeavyTile" ] ||  [ "$domainType" = "InverseTile" ] || [ "$domainType" = "Pancake" ] ||  [ "$domainType" = "PancakeDPS" ] 
then
    for algo in "${algoArr[@]}"
    do
        echo "./expansionTest${reverse}.sh 1 1000 1 ${domainType} ${algo} ${tout} ${limitunsolved} "
        ./expansionTest${reverse}.sh 1 100 1 ${domainType} ${algo} ${tout} ${limitunsolved}
        if [ $? -eq 1 ]
        then
            exit 1
        fi
    done
elif [ "$domainType" = "TreeWorld" ] 
then
    for algo in "${algoArr[@]}"
    do
        echo "./expansionTest${reverse}.sh 1 100 1 ${domainType} ${algo} ${tout} ${limitunsolved} "
        ./expansionTest${reverse}.sh 1 100 1 ${domainType} ${algo} ${tout} ${limitunsolved} 
        if [ $? -eq 1 ]
        then
            exit 1
        fi
    done
else
    echo "Invalid domain!"
    exit 1
fi





