algorithm=$1
echo "${algorithm}"
timeout 60 ./thrt-l SlidingPuzzle 10 ${algorithm} < worlds/1-4x4.st
timeout 60 ./thrt-l SlidingPuzzle 10 ${algorithm} < worlds/2-4x4.st
timeout 60 ./thrt-l SlidingPuzzle 10 ${algorithm} < worlds/3-4x4.st
timeout 60 ./thrt-l SlidingPuzzle 10 ${algorithm} < worlds/4-4x4.st
timeout 60 ./thrt-l SlidingPuzzle 10 ${algorithm} < worlds/5-4x4.st
timeout 60 ./thrt-l SlidingPuzzle 10 ${algorithm} < worlds/6-4x4.st
timeout 60 ./thrt-l SlidingPuzzle 10 ${algorithm} < worlds/7-4x4.st
timeout 60 ./thrt-l SlidingPuzzle 10 ${algorithm} < worlds/8-4x4.st

timeout 60 ./thrt-l SlidingPuzzle 30 ${algorithm} < worlds/1-4x4.st
timeout 60 ./thrt-l SlidingPuzzle 30 ${algorithm} < worlds/2-4x4.st
timeout 60 ./thrt-l SlidingPuzzle 30 ${algorithm} < worlds/3-4x4.st
timeout 60 ./thrt-l SlidingPuzzle 30 ${algorithm} < worlds/4-4x4.st
timeout 60 ./thrt-l SlidingPuzzle 30 ${algorithm} < worlds/5-4x4.st
timeout 60 ./thrt-l SlidingPuzzle 30 ${algorithm} < worlds/6-4x4.st
timeout 60 ./thrt-l SlidingPuzzle 30 ${algorithm} < worlds/7-4x4.st
timeout 60 ./thrt-l SlidingPuzzle 30 ${algorithm} < worlds/8-4x4.st

timeout 60 ./thrt-l SlidingPuzzle 300 ${algorithm} < worlds/1-4x4.st
timeout 60 ./thrt-l SlidingPuzzle 300 ${algorithm} < worlds/2-4x4.st
timeout 60 ./thrt-l SlidingPuzzle 300 ${algorithm} < worlds/3-4x4.st
timeout 60 ./thrt-l SlidingPuzzle 300 ${algorithm} < worlds/4-4x4.st
timeout 60 ./thrt-l SlidingPuzzle 300 ${algorithm} < worlds/5-4x4.st
timeout 60 ./thrt-l SlidingPuzzle 300 ${algorithm} < worlds/6-4x4.st
timeout 60 ./thrt-l SlidingPuzzle 300 ${algorithm} < worlds/7-4x4.st
timeout 60 ./thrt-l SlidingPuzzle 300 ${algorithm} < worlds/8-4x4.st

timeout 60 ./thrt-l SlidingPuzzle 1000 ${algorithm} < worlds/1-4x4.st
timeout 60 ./thrt-l SlidingPuzzle 1000 ${algorithm} < worlds/2-4x4.st
timeout 60 ./thrt-l SlidingPuzzle 1000 ${algorithm} < worlds/3-4x4.st
timeout 60 ./thrt-l SlidingPuzzle 1000 ${algorithm} < worlds/4-4x4.st
timeout 60 ./thrt-l SlidingPuzzle 1000 ${algorithm} < worlds/5-4x4.st
timeout 60 ./thrt-l SlidingPuzzle 1000 ${algorithm} < worlds/6-4x4.st
timeout 60 ./thrt-l SlidingPuzzle 1000 ${algorithm} < worlds/7-4x4.st
timeout 60 ./thrt-l SlidingPuzzle 1000 ${algorithm} < worlds/8-4x4.st