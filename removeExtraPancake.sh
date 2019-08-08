#!/bin/bash
FILES=/home/csg/slk56/cs898_project/results/*
lookahead=("LA10" "LA30" "LA100" "LA300" "LA1000")
for f in $FILES
do

    echo "$f"

    for l in "${lookahead[@]}"
    do
        rm ${f}/Pancake/10/${l}/{101..200}-10.csv
    done


    for l in "${lookahead[@]}"
    do
        rm ${f}/PancakeDPS/10/${l}/{101..200}-10.csv
    done

done