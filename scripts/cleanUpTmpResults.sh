#!/bin/bash
dir=$1
FILES=${dir}/*
lookahead=("LA10" "LA30" "LA100" "LA300" "LA1000")
for f in $FILES
do
    echo ${f}
    for l in "${lookahead[@]}"
    do
        for (( i=1; i <= 100; i++ )); do
            if [ -f ${f}/Pancake/10/${l}/${i}.tmp ] 
            then 
                echo "rm ${f}/Pancake/10/${l}/${i}.tmp"
                rm ${f}/Pancake/10/${l}/${i}.tmp
            fi

            if [ -f ${f}/PancakeDPS/10/${l}/${i}.tmp ] 
            then 
                echo "rm ${f}/PancakeDPS/10/${l}/${i}.tmp"
                rm ${f}/PancakeDPS/10/${l}/${i}.tmp
            fi

            if [ -f ${f}/SlidingPuzzle/4x4/${l}/${i}.tmp ] 
            then 
                echo "rm ${f}/SlidingPuzzle/4x4/${l}/${i}.tmp"
                rm ${f}/SlidingPuzzle/4x4/${l}/${i}.tmp
            fi

            if [ -f ${f}/SlidingPuzzle/4x4/${l}/${i}.tmp ] 
            then 
                echo "rm ${f}/SlidingPuzzle/4x4/${l}/${i}.tmp"
                rm ${f}/SlidingPuzzle/4x4/${l}/${i}.tmp
            fi

            if [ -f ${f}/HeavyTile/4x4/${l}/${i}.tmp ] 
            then 
                echo "rm ${f}/HeavyTile/4x4/${l}/${i}.tmp"
                rm ${f}/HeavyTile/4x4/${l}/${i}.tmp
            fi

            if [ -f ${f}/InverseTile/4x4/${l}/${i}.tmp ] 
            then 
                echo "rm ${f}/InverseTile/4x4/${l}/${i}.tmp"
                rm ${f}/InverseTile/4x4/${l}/${i}.tmp
            fi

        done

        for (( i=1; i <= 1000; i++ )); do
            if [ -f ${f}/TreeWorld/${l}/${i}.tmp ] 
            then 
                echo "rm ${f}/TreeWorld/${l}/${i}.tmp"
                rm ${f}/TreeWorld/${l}/${i}.tmp
            fi
        done
    done

done