#!/bin/bash


algoArr=("UCT" "GUCT" "UCTS" "GUCTS" "UCTnancy" "GUCTnancy" "UCTSnancy" "GUCTSnancy" "UCTie" "GUCTie" "UCTSie" "GUCTSie" "WAS" "WASie" "WASnancy")

for algo in "${algoArr[@]}"
do
    ./expansionTest2.sh 1 100 1 SlidingPuzzle ${algo} 
done

for algo in "${algoArr[@]}"
do
    ./expansionTest2.sh 1 100 1 Pancake ${algo} 10
done

for algo in "${algoArr[@]}"
do
    ./expansionTest2.sh 1 100 1 PancakeDPS ${algo} 10
done

for algo in "${algoArr[@]}"
do
    ./expansionTest2.sh 1 1000 1 TreeWorld ${algo} 10
done

for algo in "${algoArr[@]}"
do
    ./expansionTest2.sh 1 100 1 HeavyTile ${algo} 10
done