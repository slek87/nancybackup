#!/bin/bash

if [ "$1" = "help" ] || [ "$1" = "-help" ] || [ "$1" = "?" ]
then
  echo "./test1.sh <starting instance #> <# of instances to test> <# of processes> <Domain Type> <lookahead values>"
  exit 1
fi

if (($# < 5))
then
  echo "./test1.sh <starting instance #> <# of instances to test> <# of processes> <Domain Type> <lookahead>"
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
lookahead=$5


numProcs=0

if [ "$domainType" = "SlidingPuzzle" ]
then
    dimensions=4
    mkdir -p /export/home/slk56/results/${domainType}/${dimensions}x${dimensions}
    instance=$firstInstance
    while ((instance < lastInstance))
    do
        file="../worlds/slidingTile/${instance}-${dimensions}x${dimensions}.st"
        if ((numProcs >= ${maxProcs}))
        then
        wait
        numProcs=0
        fi		  
        if [ -f /export/home/slk56/results/${domainType}/${dimensions}x${dimensions}/${instance}.csv ]
        then 
        let instance++
        else
        timeout 120 ./test1 ${domainType}  ${lookahead} /export/home/slk56/results/${domainType}/${dimensions}x${dimensions}/LA${lookahead}/${instance}.csv < ${file} &
        let instance++
        let numProcs++
        fi
    done
elif [ "$domainType" = "Pancake" ]
then
    dimensions=10
    mkdir -p /export/home/slk56/results/${domainType}/${dimensions}
    instance=$firstInstance
    while ((instance < lastInstance))
    do
	  file="../worlds/pancake/${dimensions}/${instance}-${dimensions}.pan"
      if ((numProcs >= ${maxProcs}))
      then
        wait
        numProcs=0
      fi		  
      if [ -f /export/home/slk56/results/${domainType}/${dimensions}/${instance}.json ]
	  then 
	    let instance++
	  else
      echo ${instance}
	    ./test1 ${domainType} /export/home/slk56/results/${domainType}/${dimensions}/${instance}.json < ${file}
	    let instance++
      let numProcs++
	  fi
    done
elif [ "$domainType" = "PancakeDPS" ]
then
    dimensions=16
    mkdir -p /export/home/slk56/results/${domainType}/${dimensions}
    instance=$firstInstance
    while ((instance < lastInstance))
    do
	  file="../worlds/pancake/${dimensions}/${instance}-${dimensions}.pan"
      if ((numProcs >= ${maxProcs}))
      then
        wait
        numProcs=0
      fi		  
      if [ -f /export/home/slk56/results/${domainType}/${dimensions}/${instance}.json ]
	  then 
	    let instance++
	  else
      echo ${instance}
	    ./test1 ${domainType} /export/home/slk56/results/${domainType}/${dimensions}/${instance}.json < ${file}
	    let instance++
      let numProcs++
	  fi
    done
else
  echo "Available domain"
  exit 1
fi
