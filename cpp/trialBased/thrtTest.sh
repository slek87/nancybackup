algorithm=$1
echo "${algorithm}"
timeout 60 ./thrt SlidingPuzzle ${algorithm} 10 < worlds/1-4x4.st
timeout 60 ./thrt SlidingPuzzle ${algorithm} 30 < worlds/1-4x4.st
timeout 60 ./thrt SlidingPuzzle ${algorithm} 100 < worlds/1-4x4.st
timeout 60 ./thrt SlidingPuzzle ${algorithm} 300 < worlds/1-4x4.st

echo "f"
timeout 60 ./thrt SlidingPuzzle ${algorithm} 10 f < worlds/1-4x4.st
timeout 60 ./thrt SlidingPuzzle ${algorithm} 30 f < worlds/1-4x4.st
timeout 60 ./thrt SlidingPuzzle ${algorithm} 100 f < worlds/1-4x4.st
timeout 60 ./thrt SlidingPuzzle ${algorithm} 300 f < worlds/1-4x4.st

echo "fhat"
timeout 60 ./thrt SlidingPuzzle ${algorithm} 10 fhat < worlds/1-4x4.st
timeout 60 ./thrt SlidingPuzzle ${algorithm} 30 fhat < worlds/1-4x4.st
timeout 60 ./thrt SlidingPuzzle ${algorithm} 100 fhat < worlds/1-4x4.st
timeout 60 ./thrt SlidingPuzzle ${algorithm} 300 fhat < worlds/1-4x4.st

echo "nancy"
timeout 60 ./thrt SlidingPuzzle ${algorithm} 10 nancy < worlds/1-4x4.st
timeout 60 ./thrt SlidingPuzzle ${algorithm} 30 nancy < worlds/1-4x4.st
timeout 60 ./thrt SlidingPuzzle ${algorithm} 100 nancy < worlds/1-4x4.st
timeout 60 ./thrt SlidingPuzzle ${algorithm} 300 nancy < worlds/1-4x4.st

echo "${algorithm}"
timeout 60 ./thrt SlidingPuzzle ${algorithm} 10 < worlds/3-4x4.st
timeout 60 ./thrt SlidingPuzzle ${algorithm} 30 < worlds/3-4x4.st
timeout 60 ./thrt SlidingPuzzle ${algorithm} 100 < worlds/3-4x4.st
timeout 60 ./thrt SlidingPuzzle ${algorithm} 300 < worlds/3-4x4.st

echo "f"
timeout 60 ./thrt SlidingPuzzle ${algorithm} 10 f < worlds/3-4x4.st
timeout 60 ./thrt SlidingPuzzle ${algorithm} 30 f < worlds/3-4x4.st
timeout 60 ./thrt SlidingPuzzle ${algorithm} 100 f < worlds/3-4x4.st
timeout 60 ./thrt SlidingPuzzle ${algorithm} 300 f < worlds/3-4x4.st

echo "fhat"
timeout 60 ./thrt SlidingPuzzle ${algorithm} 10 fhat < worlds/3-4x4.st
timeout 60 ./thrt SlidingPuzzle ${algorithm} 30 fhat < worlds/3-4x4.st
timeout 60 ./thrt SlidingPuzzle ${algorithm} 100 fhat < worlds/3-4x4.st
timeout 60 ./thrt SlidingPuzzle ${algorithm} 300 fhat < worlds/3-4x4.st

echo "nancy"
timeout 60 ./thrt SlidingPuzzle ${algorithm} 10 nancy < worlds/3-4x4.st
timeout 60 ./thrt SlidingPuzzle ${algorithm} 30 nancy < worlds/3-4x4.st
timeout 60 ./thrt SlidingPuzzle ${algorithm} 100 nancy < worlds/3-4x4.st
timeout 60 ./thrt SlidingPuzzle ${algorithm} 300 nancy < worlds/3-4x4.st
