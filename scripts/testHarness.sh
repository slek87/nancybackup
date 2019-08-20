#!/bin/bash

# algoArr=("UCT-L" "GUCT-L" "UCTS-L" "GUCTS-L" "UCTnancy-L" "GUCTnancy-L" "UCTSnancy-L" "GUCTSnancy-L" "UCTie-L" "GUCTie-L" "UCTSie-L" "GUCTSie-L" "UCTiep-L" "GUCTiep-L" "UCTSiep-L" "GUCTSiep-L" "WAS-L" "WASie-L" "WASiep-L" "WASnancy-L" "UCT" "GUCT" "UCTS" "GUCTS" "UCTnancy" "GUCTnancy" "UCTSnancy" "GUCTSnancy" "UCTie" "GUCTie" "UCTSie" "GUCTSie" "UCTiep" "GUCTiep" "UCTSiep" "GUCTSiep" "WAS" "WASie" "WASiep" "WASnancy" "FHAT" "RISK" "IE" "IEP" "LSSLRTA")




# algoArr=("FHAT" "LSSLRTA" "IE" "IEP" "IEPP" "RISK" "UCT" "UCTnancy" "UCTie" "UCTiep" "UCTS" "UCTSnancy" "UCTSie" "UCTSiep" "GUCT" "GUCTnancy" "GUCTie" "GUCTiep" "GUCTS" "GUCTSnancy" "GUCTSie" "GUCTSiep" "AS" "ASnancy" "ASie" "ASiep" "WAS" "WASie" "WASiep" "WASnancy" "UCT-L" "UCTnancy-L" "UCTie-L" "UCTiep-L" "UCTS-L" "UCTSnancy-L" "UCTSie-L" "UCTSiep-L" "GUCT-L" "GUCTnancy-L" "GUCTie-L" "GUCTiep-L" "GUCTS-L" "GUCTSnancy-L" "GUCTSie-L" "GUCTSiep-L" "AS-L" "ASnancy-L" "ASie-L" "ASiep-L" "WAS-L" "WASie-L" "WASiep-L" "WASnancy-L" "UCT-H" "UCTnancy-H" "UCTie-H" "UCTiep-H" "UCTS-H" "UCTSnancy-H" "UCTSie-H" "UCTSiep-H" "GUCT-H" "GUCTnancy-H" "GUCTie-H" "GUCTiep-H" "GUCTS-H" "GUCTSnancy-H" "GUCTSie-H" "GUCTSiep-H" "AS-H" "ASnancy-H" "ASie-H" "ASiep-H" "WAS-H" "WASie-H" "WASiep-H" "WASnancy-H" "UCT-LH" "UCTnancy-LH" "UCTie-LH" "UCTiep-LH" "UCTS-LH" "UCTSnancy-LH" "UCTSie-LH" "UCTSiep-LH" "GUCT-LH" "GUCTnancy-LH" "GUCTie-LH" "GUCTiep-LH" "GUCTS-LH" "GUCTSnancy-LH" "GUCTSie-LH" "GUCTSiep-LH" "AS-LH" "ASnancy-LH" "ASie-LH" "ASiep-LH" "WAS-LH" "WASie-LH" "WASiep-LH" "WASnancy-LH")
algoArr=("FHAT" "LSSLRTA" "IE" "IEP" "IEPP" "RISK" "UCT" "UCTnancy" "UCTie" "UCTiep" "UCTS" "UCTSnancy" "UCTSie" "UCTSiep" "GUCT" "GUCTnancy" "GUCTie" "GUCTiep" "GUCTS" "GUCTSnancy" "GUCTSie" "GUCTSiep" "AS" "ASnancy" "ASie" "ASiep" "WAS" "WASie" "WASiep" "WASnancy" "UCT-L" "UCTnancy-L" "UCTie-L" "UCTiep-L" "UCTS-L" "UCTSnancy-L" "UCTSie-L" "UCTSiep-L" "GUCT-L" "GUCTnancy-L" "GUCTie-L" "GUCTiep-L" "GUCTS-L" "GUCTSnancy-L" "GUCTSie-L" "GUCTSiep-L" "AS-L" "ASnancy-L" "ASie-L" "ASiep-L" "WAS-L" "WASie-L" "WASiep-L" "WASnancy-L")

# algoArr=("AS-H" "ASie-H" "ASiep" "ASiep-H" "GUCT" "GUCT-H" "GUCTS-H" "GUCTSie-H" "GUCTSiep" "GUCTSiep-H" "GUCTSnancy" "GUCTie" "GUCTie-H" "GUCTiep" "GUCTiep-H" "GUCTnancy" "UCT-H" "UCTS-H" "UCTSie-H" "UCTSiep" "UCTSiep-H" "UCTSnancy-H" "UCTie-H" "UCTiep" "UCTiep-H" "UCTnancy")

# algoArr=("RISK")

default=true

domainType="All"
reverse=""
tout=300
limitunsolved=3
specificAlgo=""

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

    if [ ${!i} == "-a" ]; then
        if [ $((i+1)) -le "$#" ]; then
            var=$((i+1))
            specificAlgo=${!var}
        fi
    fi
done

if [ ! "$specificAlgo" = "" ] 
then
    if [ "$domainType" = "All" ] 
    then
        echo "Specify a domain"
        exit 1
    fi
    echo "./expansionTest${reverse}.sh 1 100 1 ${domainType} ${specificAlgo} ${tout} ${limitunsolved} "
    ./expansionTest${reverse}.sh 1 100 1 ${domainType} ${specificAlgo} ${tout} ${limitunsolved} 
    exit 1
fi

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

    for algo in "${algoArr[@]}"
    do
        echo "./expansionTest${reverse}.sh 1 100 1 SqrtTile ${algo} ${tout} ${limitunsolved} "
        ./expansionTest${reverse}.sh 1 100 1 SqrtTile ${algo} ${tout} ${limitunsolved} 
        if [ $? -eq 1 ]
        then
            exit 1
        fi
    done

elif [ "$domainType" = "SlidingPuzzle" ] ||  [ "$domainType" = "HeavyTile" ] ||  [ "$domainType" = "InverseTile" ]  ||  [ "$domainType" = "SqrtTile" ] || [ "$domainType" = "Pancake" ] ||  [ "$domainType" = "PancakeDPS" ] 
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
        ./expansionTest${reverse}.sh 1 1000 1 ${domainType} ${algo} ${tout} ${limitunsolved} 
        if [ $? -eq 1 ]
        then
            exit 1
        fi
    done
else
    echo "Invalid domain!"
    exit 1
fi





