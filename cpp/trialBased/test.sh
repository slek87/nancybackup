algorithm=$1
echo "${algorithm}"

timeout 11 ./thrt Pancake 10 ${algorithm} < worlds/9-10.pan
timeout 11 ./thrt Pancake 10 ${algorithm} < worlds/20-10.pan

timeout 11 ./thrt Pancake 30 ${algorithm} < worlds/85-10.pan
timeout 11 ./thrt Pancake 30 ${algorithm} < worlds/86-10.pan
timeout 11 ./thrt Pancake 30 ${algorithm} < worlds/87-10.pan

timeout 11 ./thrt Pancake 100 ${algorithm} < worlds/9-10.pan
timeout 11 ./thrt Pancake 100 ${algorithm} < worlds/85-10.pan
timeout 11 ./thrt Pancake 1000 ${algorithm} < worlds/86-10.pan
timeout 11 ./thrt Pancake 1000 ${algorithm} < worlds/87-10.pan

timeout 11 ./thrt PancakeDPS 10 ${algorithm} < worlds/9-10.pan
timeout 11 ./thrt PancakeDPS 10 ${algorithm} < worlds/20-10.pan
timeout 11 ./thrt PancakeDPS 10 ${algorithm} < worlds/85-10.pan
timeout 11 ./thrt PancakeDPS 10 ${algorithm} < worlds/86-10.pan
timeout 11 ./thrt PancakeDPS 10 ${algorithm} < worlds/87-10.pan

timeout 11 ./thrt PancakeDPS 30 ${algorithm} < worlds/9-10.pan
timeout 11 ./thrt PancakeDPS 30 ${algorithm} < worlds/20-10.pan
timeout 11 ./thrt PancakeDPS 30 ${algorithm} < worlds/76-10.pan
timeout 11 ./thrt PancakeDPS 30 ${algorithm} < worlds/85-10.pan
timeout 11 ./thrt PancakeDPS 30 ${algorithm} < worlds/86-10.pan
timeout 11 ./thrt PancakeDPS 30 ${algorithm} < worlds/87-10.pan

timeout 11 ./thrt PancakeDPS 100 ${algorithm} < worlds/9-10.pan
timeout 11 ./thrt PancakeDPS 100 ${algorithm} < worlds/85-10.pan
timeout 11 ./thrt PancakeDPS 100 ${algorithm} < worlds/86-10.pan
timeout 11 ./thrt PancakeDPS 100 ${algorithm} < worlds/87-10.pan

timeout 11 ./thrt PancakeDPS 1000 ${algorithm} < worlds/9-10.pan
timeout 11 ./thrt PancakeDPS 1000 ${algorithm} < worlds/20-10.pan
timeout 11 ./thrt PancakeDPS 1000 ${algorithm} < worlds/33-10.pan
timeout 11 ./thrt PancakeDPS 1000 ${algorithm} < worlds/86-10.pan
timeout 11 ./thrt PancakeDPS 1000 ${algorithm} < worlds/87-10.pan



# timeout 11 ./thrt SlidingPuzzle 10 ${algorithm} < worlds/1-4x4.st
# timeout 11 ./thrt SlidingPuzzle 10 ${algorithm} < worlds/2-4x4.st
# timeout 11 ./thrt SlidingPuzzle 10 ${algorithm} < worlds/3-4x4.st
# timeout 11 ./thrt SlidingPuzzle 10 ${algorithm} < worlds/4-4x4.st
# timeout 11 ./thrt SlidingPuzzle 10 ${algorithm} < worlds/5-4x4.st
timeout 11 ./thrt SlidingPuzzle 10 ${algorithm} < worlds/6-4x4.st
timeout 11 ./thrt SlidingPuzzle 10 ${algorithm} < worlds/7-4x4.st
timeout 11 ./thrt SlidingPuzzle 10 ${algorithm} < worlds/8-4x4.st

timeout 11 ./thrt SlidingPuzzle 30 ${algorithm} < worlds/1-4x4.st
timeout 11 ./thrt SlidingPuzzle 30 ${algorithm} < worlds/2-4x4.st
timeout 11 ./thrt SlidingPuzzle 30 ${algorithm} < worlds/3-4x4.st
timeout 11 ./thrt SlidingPuzzle 30 ${algorithm} < worlds/4-4x4.st
# timeout 11 ./thrt SlidingPuzzle 30 ${algorithm} < worlds/5-4x4.st
# timeout 11 ./thrt SlidingPuzzle 30 ${algorithm} < worlds/6-4x4.st
# timeout 11 ./thrt SlidingPuzzle 30 ${algorithm} < worlds/7-4x4.st
# timeout 11 ./thrt SlidingPuzzle 30 ${algorithm} < worlds/8-4x4.st

timeout 11 ./thrt SlidingPuzzle 300 ${algorithm} < worlds/1-4x4.st
timeout 11 ./thrt SlidingPuzzle 300 ${algorithm} < worlds/2-4x4.st
timeout 11 ./thrt SlidingPuzzle 300 ${algorithm} < worlds/3-4x4.st
timeout 11 ./thrt SlidingPuzzle 300 ${algorithm} < worlds/4-4x4.st
timeout 11 ./thrt SlidingPuzzle 300 ${algorithm} < worlds/5-4x4.st
# timeout 11 ./thrt SlidingPuzzle 300 ${algorithm} < worlds/6-4x4.st
# timeout 11 ./thrt SlidingPuzzle 300 ${algorithm} < worlds/7-4x4.st
# timeout 11 ./thrt SlidingPuzzle 300 ${algorithm} < worlds/8-4x4.st

echo "A"
timeout 11 ./thrt SlidingPuzzle 1000 ${algorithm} < worlds/1-4x4.st
echo "B"
timeout 11 ./thrt SlidingPuzzle 1000 ${algorithm} < worlds/2-4x4.st
echo "C"
timeout 11 ./thrt SlidingPuzzle 1000 ${algorithm} < worlds/3-4x4.st
echo "D"
timeout 11 ./thrt SlidingPuzzle 1000 ${algorithm} < worlds/4-4x4.st
# timeout 11 ./thrt SlidingPuzzle 1000 ${algorithm} < worlds/5-4x4.st
# timeout 11 ./thrt SlidingPuzzle 1000 ${algorithm} < worlds/6-4x4.st
# timeout 11 ./thrt SlidingPuzzle 1000 ${algorithm} < worlds/7-4x4.st
# timeout 11 ./thrt SlidingPuzzle 1000 ${algorithm} < worlds/8-4x4.st


echo "1"
timeout 11 ./thrt HeavyTile 10 ${algorithm} < worlds/7-4x4.st
echo "2"
timeout 11 ./thrt HeavyTile 10 ${algorithm} < worlds/8-4x4.st
echo "3"
timeout 11 ./thrt HeavyTile 30 ${algorithm} < worlds/1-4x4.st
echo "4"
timeout 11 ./thrt HeavyTile 30 ${algorithm} < worlds/2-4x4.st
echo "5"
timeout 11 ./thrt HeavyTile 300 ${algorithm} < worlds/7-4x4.st
echo "6"
timeout 11 ./thrt HeavyTile 300 ${algorithm} < worlds/8-4x4.st
echo "7"
timeout 11 ./thrt HeavyTile 1000 ${algorithm} < worlds/7-4x4.st
echo "8"
timeout 11 ./thrt HeavyTile 1000 ${algorithm} < worlds/8-4x4.st
echo "9"
timeout 11 ./thrt HeavyTile 1000 ${algorithm} < worlds/1-4x4.st
echo "10"
timeout 11 ./thrt HeavyTile 1000 ${algorithm} < worlds/2-4x4.st
echo "11"
timeout 11 ./thrt HeavyTile 1000 ${algorithm} < worlds/3-4x4.st