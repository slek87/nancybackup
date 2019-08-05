#!/bin/bash
dir=$1
FILES=${dir}/*
lookahead=("LA10" "LA30" "LA100" "LA300" "LA1000")
for algo in $FILES
do
    for l in "${lookahead[@]}"
    do
        rm ${f}/Pancake/10/${l}/{1..100}
        rm ${f}/PancakeDPS/10/${l}/{1..100}
        rm ${f}/SlidingPuzzle/4x4/${l}/{1..100}
        rm ${f}/HeavyTile/4x4/${l}/{1..100}
        rm ${f}/TreeWorld/${l}/{1..1000}

    done

done