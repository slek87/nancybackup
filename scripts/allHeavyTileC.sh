#!/bin/bash

algoArr=("UCT" "GUCT" "UCTS" "GUCTS" "UCTnancy" "GUCTnancy" "UCTSnancy" "GUCTSnancy" "UCTie" "GUCTie" "UCTSie" "GUCTSie")
for algo in "${algoArr[@]}"
do
    echo "./trialTestsC.sh 1 100 1 HeavyTile ${algo} "
    ./trialTestsC.sh 1 100 1 HeavyTile ${algo} 
done


algoArr=("FHAT RISK IE LSSLRTA")
for algo in "${algoArr[@]}"
do
    echo "./trialTestsC.sh 1 100 1 HeavyTile ${algo} "
    ./trialTestsC.sh 1 100 1 HeavyTile ${algo} 
done

