algorithm=$1
d=$2

lookaheadArr=(10 30 100 300 1000)
for lookahead in "${lookaheadArr[@]}"
do
    echo ${lookahead}
    echo -n "1 "
    timeout 60 ./thrt SlidingPuzzle ${algorithm} ${lookahead} ${d}  < worlds/1-4x4.st
    echo -n "2 "
    timeout 60 ./thrt SlidingPuzzle ${algorithm} ${lookahead} ${d} < worlds/2-4x4.st
    echo -n "3 "
    timeout 60 ./thrt SlidingPuzzle ${algorithm} ${lookahead} ${d} < worlds/3-4x4.st
    echo -n "4 "
    timeout 60 ./thrt SlidingPuzzle ${algorithm} ${lookahead} ${d} < worlds/4-4x4.st
    echo -n "5 "
    timeout 60 ./thrt SlidingPuzzle ${algorithm} ${lookahead} ${d} < worlds/5-4x4.st
done
