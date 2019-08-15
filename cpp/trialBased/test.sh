algorithm=$1
echo -ne "${algorithm}"

timeout 11 ./thrt Pancake 10 ${algorithm} < worlds/9-10.pan
echo -ne "."
timeout 11 ./thrt Pancake 10 ${algorithm} < worlds/20-10.pan

echo -ne "."
timeout 11 ./thrt Pancake 30 ${algorithm} < worlds/85-10.pan
echo -ne "."
timeout 11 ./thrt Pancake 30 ${algorithm} < worlds/86-10.pan
echo -ne "."
timeout 11 ./thrt Pancake 30 ${algorithm} < worlds/87-10.pan

echo -ne "."
timeout 11 ./thrt Pancake 100 ${algorithm} < worlds/9-10.pan
echo -ne "."
timeout 11 ./thrt Pancake 100 ${algorithm} < worlds/85-10.pan
echo -ne "."
timeout 11 ./thrt Pancake 1000 ${algorithm} < worlds/86-10.pan
echo -ne "."
timeout 11 ./thrt Pancake 1000 ${algorithm} < worlds/87-10.pan

echo -ne "."
timeout 11 ./thrt PancakeDPS 10 ${algorithm} < worlds/9-10.pan
echo -ne "."
timeout 11 ./thrt PancakeDPS 10 ${algorithm} < worlds/20-10.pan
echo -ne "."
timeout 11 ./thrt PancakeDPS 10 ${algorithm} < worlds/85-10.pan
echo -ne "."
timeout 11 ./thrt PancakeDPS 10 ${algorithm} < worlds/86-10.pan
echo -ne "."
timeout 11 ./thrt PancakeDPS 10 ${algorithm} < worlds/87-10.pan

echo -ne "."
timeout 11 ./thrt PancakeDPS 30 ${algorithm} < worlds/9-10.pan
echo -ne "."
timeout 11 ./thrt PancakeDPS 30 ${algorithm} < worlds/20-10.pan
echo -ne "."
timeout 11 ./thrt PancakeDPS 30 ${algorithm} < worlds/76-10.pan
echo -ne "."
timeout 11 ./thrt PancakeDPS 30 ${algorithm} < worlds/85-10.pan
echo -ne "."
timeout 11 ./thrt PancakeDPS 30 ${algorithm} < worlds/86-10.pan
echo -ne "."
timeout 11 ./thrt PancakeDPS 30 ${algorithm} < worlds/87-10.pan

echo -ne "."
timeout 11 ./thrt PancakeDPS 100 ${algorithm} < worlds/9-10.pan
echo -ne "."
timeout 11 ./thrt PancakeDPS 100 ${algorithm} < worlds/85-10.pan
echo -ne "."
timeout 11 ./thrt PancakeDPS 100 ${algorithm} < worlds/86-10.pan
echo -ne "."
timeout 11 ./thrt PancakeDPS 100 ${algorithm} < worlds/87-10.pan

echo -ne "."
timeout 11 ./thrt PancakeDPS 1000 ${algorithm} < worlds/9-10.pan
echo -ne "."
timeout 11 ./thrt PancakeDPS 1000 ${algorithm} < worlds/20-10.pan
echo -ne "."
timeout 11 ./thrt PancakeDPS 1000 ${algorithm} < worlds/33-10.pan
echo -ne "."
timeout 11 ./thrt PancakeDPS 1000 ${algorithm} < worlds/86-10.pan
echo -ne "."
timeout 11 ./thrt PancakeDPS 1000 ${algorithm} < worlds/87-10.pan



# timeout 11 ./thrt SlidingPuzzle 10 ${algorithm} < worlds/1-4x4.st
# timeout 11 ./thrt SlidingPuzzle 10 ${algorithm} < worlds/2-4x4.st
# timeout 11 ./thrt SlidingPuzzle 10 ${algorithm} < worlds/3-4x4.st
# timeout 11 ./thrt SlidingPuzzle 10 ${algorithm} < worlds/4-4x4.st
# timeout 11 ./thrt SlidingPuzzle 10 ${algorithm} < worlds/5-4x4.st
echo -ne "."
timeout 11 ./thrt SlidingPuzzle 10 ${algorithm} < worlds/6-4x4.st
echo -ne "."
timeout 11 ./thrt SlidingPuzzle 10 ${algorithm} < worlds/7-4x4.st
echo -ne "."
timeout 11 ./thrt SlidingPuzzle 10 ${algorithm} < worlds/8-4x4.st

echo -ne "."
timeout 11 ./thrt SlidingPuzzle 30 ${algorithm} < worlds/1-4x4.st
echo -ne "."
timeout 11 ./thrt SlidingPuzzle 30 ${algorithm} < worlds/2-4x4.st
echo -ne "."
timeout 11 ./thrt SlidingPuzzle 30 ${algorithm} < worlds/3-4x4.st
echo -ne "."
timeout 11 ./thrt SlidingPuzzle 30 ${algorithm} < worlds/4-4x4.st
# timeout 11 ./thrt SlidingPuzzle 30 ${algorithm} < worlds/5-4x4.st
# timeout 11 ./thrt SlidingPuzzle 30 ${algorithm} < worlds/6-4x4.st
# timeout 11 ./thrt SlidingPuzzle 30 ${algorithm} < worlds/7-4x4.st
# timeout 11 ./thrt SlidingPuzzle 30 ${algorithm} < worlds/8-4x4.st

echo -ne "."
timeout 11 ./thrt SlidingPuzzle 300 ${algorithm} < worlds/1-4x4.st
echo -ne "."
timeout 11 ./thrt SlidingPuzzle 300 ${algorithm} < worlds/2-4x4.st
echo -ne "."
timeout 11 ./thrt SlidingPuzzle 300 ${algorithm} < worlds/3-4x4.st
echo -ne "."
timeout 11 ./thrt SlidingPuzzle 300 ${algorithm} < worlds/4-4x4.st
echo -ne "."
timeout 11 ./thrt SlidingPuzzle 300 ${algorithm} < worlds/5-4x4.st
# timeout 11 ./thrt SlidingPuzzle 300 ${algorithm} < worlds/6-4x4.st
# timeout 11 ./thrt SlidingPuzzle 300 ${algorithm} < worlds/7-4x4.st
# timeout 11 ./thrt SlidingPuzzle 300 ${algorithm} < worlds/8-4x4.st

echo -ne "A "
timeout 11 ./thrt SlidingPuzzle 1000 ${algorithm} < worlds/1-4x4.st
echo -ne "B "
timeout 11 ./thrt SlidingPuzzle 1000 ${algorithm} < worlds/2-4x4.st
echo -ne "C "
timeout 11 ./thrt SlidingPuzzle 1000 ${algorithm} < worlds/3-4x4.st
echo -ne "D "
timeout 11 ./thrt SlidingPuzzle 1000 ${algorithm} < worlds/4-4x4.st
# timeout 11 ./thrt SlidingPuzzle 1000 ${algorithm} < worlds/5-4x4.st
# timeout 11 ./thrt SlidingPuzzle 1000 ${algorithm} < worlds/6-4x4.st
# timeout 11 ./thrt SlidingPuzzle 1000 ${algorithm} < worlds/7-4x4.st
# timeout 11 ./thrt SlidingPuzzle 1000 ${algorithm} < worlds/8-4x4.st


echo -ne "E "
timeout 11 ./thrt HeavyTile 10 ${algorithm} < worlds/7-4x4.st
echo -ne "F "
timeout 11 ./thrt HeavyTile 10 ${algorithm} < worlds/8-4x4.st
echo -ne "G "
timeout 11 ./thrt HeavyTile 30 ${algorithm} < worlds/1-4x4.st
echo -ne "H "
timeout 11 ./thrt HeavyTile 30 ${algorithm} < worlds/2-4x4.st
echo -ne "I "
timeout 11 ./thrt HeavyTile 300 ${algorithm} < worlds/7-4x4.st
echo -ne "J "
timeout 11 ./thrt HeavyTile 300 ${algorithm} < worlds/8-4x4.st
echo -ne "K "
timeout 11 ./thrt HeavyTile 1000 ${algorithm} < worlds/7-4x4.st
echo -ne "L "
timeout 11 ./thrt HeavyTile 1000 ${algorithm} < worlds/8-4x4.st
echo -ne "M "
timeout 11 ./thrt HeavyTile 1000 ${algorithm} < worlds/1-4x4.st
echo -ne "N "
timeout 11 ./thrt HeavyTile 1000 ${algorithm} < worlds/2-4x4.st
echo -ne "O "
timeout 11 ./thrt HeavyTile 1000 ${algorithm} < worlds/3-4x4.st