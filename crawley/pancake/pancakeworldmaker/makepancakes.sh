#!/bin/bash

if [ "$1" = "help" ] || [ "$1" = "-help" ] || [ "$1" = "?" ] || [ "$1" = "-h" ]
then
  echo "./makepancakes.sh [-s pancake size] [-t # of tests] [-o output dir]"
  echo "Default: size:16 tests:1000 output:16"

  exit 1
fi

#!/bin/bash
s="16"
t=1000
o="16"
default_address=true



for (( i=1; i <= "$#"; i++ )); do
    if [ ${!i} == "-s" ]; then
        if [ $((i+1)) -le "$#" ]; then
            var=$((i+1))
            s=${!var}
        fi
    fi

    if [ ${!i} == "-t" ]; then
        if [ $((i+1)) -le "$#" ]; then
            var=$((i+1))
            t=${!var}
        fi
    fi

    if [ ${!i} == "-o" ]; then
        if [ $((i+1)) -le "$#" ]; then
            var=$((i+1))
            o=${!var}
            default_address=false
        fi
    fi

done



if [ "$default_address" = true ] ; then
    o="$s"
fi

mkdir -p "$o"

for (( i=1; i <= "$t"; i++ )); do
    ./pancakemaker "$s" > "$o/$i-$s.pan"
done
