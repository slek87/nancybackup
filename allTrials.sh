arg=$1
dec="-"
algoArr=("UCT" "GUCT" "UCTS" "GUCTS")


for algo in "${algoArr[@]}"
do
    cd ${algo}
    if [ "$arg" = "1" ]
    then
        ./trialtest.sh 1 10 2 SlidingPuzzle ${algo} ${dec} 
        ./trialtest.sh 1 10 2 HeavyTile ${algo} ${dec} 
        ./trialtest.sh 1 100 2 TreeWorld ${algo} ${dec}
        ./trialtest.sh 1 20 2 Pancake ${algo} ${dec} 10 
        ./trialtest.sh 1 20 2 PancakeDPS ${algo} ${dec} 10 

    elif [ "$arg" = "2" ]
    then
        ./trialtest.sh 10 10 2 SlidingPuzzle ${algo} ${dec}
        ./trialtest.sh 10 10 2 HeavyTile ${algo} ${dec}
        ./trialtest.sh 100 100 2 TreeWorld ${algo} ${dec}
        ./trialtest.sh 20 20 2 Pancake ${algo} ${dec} 10  
        ./trialtest.sh 20 20 2 PancakeDPS ${algo} ${dec} 10  

    elif [ "$arg" = "3" ]
    then
        ./trialtest.sh 20 10 2 SlidingPuzzle ${algo} ${dec}
        ./trialtest.sh 20 10 2 HeavyTile ${algo} ${dec}
        ./trialtest.sh 200 100 2 TreeWorld ${algo} ${dec}
        ./trialtest.sh 40 20 2 Pancake ${algo} ${dec} 10  
        ./trialtest.sh 40 20 2 PancakeDPS ${algo} ${dec} 10  

    elif [ "$arg" = "4" ]
    then
        ./trialtest.sh 30 10 2 SlidingPuzzle ${algo} ${dec}
        ./trialtest.sh 30 10 2 HeavyTile ${algo} ${dec}
        ./trialtest.sh 300 100 2 TreeWorld ${algo} ${dec}
        ./trialtest.sh 60 20 2 Pancake ${algo} ${dec} 10  
        ./trialtest.sh 60 20 2 PancakeDPS ${algo} ${dec} 10  

    elif [ "$arg" = "5" ]
    then
        ./trialtest.sh 40 10 2 SlidingPuzzle ${algo} ${dec}
        ./trialtest.sh 40 10 2 HeavyTile ${algo} ${dec}
        ./trialtest.sh 400 100 2 TreeWorld ${algo} ${dec}
        ./trialtest.sh 80 20 2 Pancake ${algo} ${dec} 10  
        ./trialtest.sh 80 20 2 PancakeDPS ${algo} ${dec} 10  

    elif [ "$arg" = "6" ]
    then
        ./trialtest.sh 20 10 2 SlidingPuzzle ${algo} ${dec}
        ./trialtest.sh 20 10 2 HeavyTile ${algo} ${dec}
        ./trialtest.sh 200 100 2 TreeWorld ${algo} ${dec}
        ./trialtest.sh 100 20 2 Pancake ${algo} ${dec} 10  
        ./trialtest.sh 100 20 2 PancakeDPS ${algo} ${dec} 10  

    elif [ "$arg" = "7" ]
    then
        ./trialtest.sh 60 10 2 SlidingPuzzle ${algo} ${dec}
        ./trialtest.sh 60 10 2 HeavyTile ${algo} ${dec}
        ./trialtest.sh 600 100 2 TreeWorld ${algo} ${dec}
        ./trialtest.sh 120 20 2 Pancake ${algo} ${dec} 10  
        ./trialtest.sh 120 20 2 PancakeDPS ${algo} ${dec} 10  

    elif [ "$arg" = "8" ]
    then
        ./trialtest.sh 70 10 2 SlidingPuzzle ${algo} ${dec}
        ./trialtest.sh 70 10 2 HeavyTile ${algo} ${dec}
        ./trialtest.sh 700 100 2 TreeWorld ${algo} ${dec}
        ./trialtest.sh 140 20 2 Pancake ${algo} ${dec} 10  
        ./trialtest.sh 140 20 2 PancakeDPS ${algo} ${dec} 10  

    elif [ "$arg" = "9" ]
    then
        ./trialtest.sh 80 10 2 SlidingPuzzle ${algo} ${dec}
        ./trialtest.sh 80 10 2 HeavyTile ${algo} ${dec}
        ./trialtest.sh 800 100 2 TreeWorld ${algo} ${dec}
        ./trialtest.sh 160 20 2 Pancake ${algo} ${dec} 10  
        ./trialtest.sh 160 20 2 PancakeDPS ${algo} ${dec} 10  

    elif [ "$arg" = "10" ]
    then
        ./trialtest.sh 90 11 2 SlidingPuzzle ${algo} ${dec}
        ./trialtest.sh 90 11 2 HeavyTile ${algo} ${dec}
        ./trialtest.sh 900 101 2 TreeWorld ${algo} ${dec}
        ./trialtest.sh 180 51 2 Pancake ${algo} ${dec} 10  
        ./trialtest.sh 180 51 2 PancakeDPS ${algo} ${dec} 10  
    fi
    cd ..
done




