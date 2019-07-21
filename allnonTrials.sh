arg=$1
algoArr=("FHAT" "IE" "LSSLRTA" "RISK")


for algo in "${algoArr[@]}"
do  
    echo ${algo}
    cd ${algo}
    ./nontrialtest.sh 1 100 2 SlidingPuzzle
    echo ${algo}
    ./nontrialtest.sh 1 100 2 HeavyTile
    echo ${algo}

    ./nontrialtest.sh 1 1000 2 TreeWorld 
    echo ${algo}

    ./nontrialtest.sh 1 200 2 Pancake 
    echo ${algo}

    ./nontrialtest.sh 1 200 2 PancakeDPS
    cd ..
done




