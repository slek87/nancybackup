#!/bin/bash


algoArr=("UCT" "GUCT" "UCTS" "GUCTS" "UCTnancy" "GUCTnancy" "UCTSnancy" "GUCTSnancy" "UCTie" "GUCTie" "UCTSie" "GUCTSie" "WAS" "WASie" "WASnancy")

for algo in "${algoArr[@]}"
do
    ./expansionTest3.sh 1 100 1 HeavyTile ${algo} 10
done