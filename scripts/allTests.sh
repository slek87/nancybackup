#!/bin/bash

algoArr=("UCT" "GUCT" "UCTS" "GUCTS" "UCTnancy" "GUCTnancy" "UCTSnancy" "GUCTSnancy" "UCTie" "GUCTie" "UCTSie" "GUCTSie" "WAS" "WASie" "WASnancy" "FHAT" "RISK" "IE" "LSSLRTA")

for algo in "${algoArr[@]}"
do
    echo "./trialTests.sh 1 100 1 SlidingPuzzle ${algo} "
    ./trialTests.sh 1 100 1 SlidingPuzzle ${algo} 
done

for algo in "${algoArr[@]}"
do
    echo "./trialTests.sh 1 100 1 Pancake ${algo} "
    ./trialTests.sh 1 100 1 Pancake ${algo} 10
done

for algo in "${algoArr[@]}"
do
    echo "./trialTests.sh 1 100 1 PancakeDPS ${algo} "
    ./trialTests.sh 1 100 1 PancakeDPS ${algo} 10
done

for algo in "${algoArr[@]}"
do
    echo "./trialTests.sh 1 1000 1 TreeWorld ${algo} "
    ./trialTests.sh 1 100 1 TreeWorld ${algo} 
done

for algo in "${algoArr[@]}"
do
    echo "./trialTests.sh 1 100 1 HeavyTile ${algo} "
    ./trialTests.sh 1 100 1 HeavyTile ${algo} 
done

for algo in "${algoArr[@]}"
do
    echo "./trialTests.sh 1 100 1 InverseTile ${algo} "
    ./nonTrialTests.sh 1 100 1 InverseTile ${algo} 
done



