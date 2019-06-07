#!/bin/bash

if [ "$1" = "help" ] || [ "$1" = "-help" ] || [ "$1" = "?" ]
then
  echo "./ex2.sh <starting instance #> <# of instances to test> <# of processes> <Domain Type>"
  exit 1
fi

if (($# < 4))
then
  echo "./ex2.sh <starting instance #> <# of instances to test> <# of processes> <Domain Type>"
  exit 1
fi

# Which instance to start testing on
firstInstance=$1

# The maximum number of instances to test on
maxInstances=$2
lastInstance=$(( $firstInstance + $maxInstances ))

# Max number of background processes to start, should probably not be more than the number of cores on the machine
maxProcs=$3

# The domain to run on
domainType=$4

numProcs=0

if [ "$domainType" = "SlidingPuzzle" ] || [ "$domainType" = "HeavyTile" ] || [ "$domainType" = "InverseTile" ]
then
    dimensions=4
    mkdir -p results/ex2/${domainType}/${dimensions}x${dimensions}
    instance=$firstInstance
    while ((instance < lastInstance))
    do
        file="../../../worlds/slidingTile/${instance}-${dimensions}x${dimensions}.st"
        if ((numProcs >= ${maxProcs}))
        then
        wait
        numProcs=0
        fi		  
        if [ -f results/ex2/${domainType}/${dimensions}x${dimensions}/${instance}.json ]
        then 
        let instance++
        else
        ./ex2 ${domainType} results/ex2/${domainType}/${dimensions}x${dimensions}/${instance}.json < ${file} &
        let instance++
        let numProcs++
        fi
    done
elif [ "$domainType" = "Pancake" ]
then
    dimensions=24
    mkdir -p results/ex2/${domainType}/${dimensions}
    instance=$firstInstance
    while ((instance < lastInstance))
    do
	  file="../../../worlds/pancake/${dimensions}/${instance}-${dimensions}.pan"
      if ((numProcs >= ${maxProcs}))
      then
        wait
        numProcs=0
      fi		  
      if [ -f results/ex2/${domainType}/${dimensions}/${instance}.json ]
	  then 
	    let instance++
	  else
      echo ${instance}
	    ./ex2 ${domainType} results/ex2/${domainType}/${dimensions}/${instance}.json < ${file}
	    let instance++
      let numProcs++
	  fi
    done
elif [ "$domainType" = "PancakeDPS" ]
then
    dimensions=24
    mkdir -p results/ex2/${domainType}/${dimensions}
    instance=$firstInstance
    while ((instance < lastInstance))
    do
	  file="../../../worlds/pancake/${dimensions}/${instance}-${dimensions}.pan"
      if ((numProcs >= ${maxProcs}))
      then
        wait
        numProcs=0
      fi		  
      if [ -f results/ex2/${domainType}/${dimensions}/${instance}.json ]
	  then 
	    let instance++
	  else
      echo ${instance}
	    ./ex2 ${domainType} results/ex2/${domainType}/${dimensions}/${instance}.json < ${file}
	    let instance++
      let numProcs++
	  fi
    done
else
  echo "Available domain"
  exit 1
fi
