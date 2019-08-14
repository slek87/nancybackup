algorithm=$1
echo "${algorithm}"
timeout 120 ./thrt HeavyTile 10 ${algorithm} < worlds/1-4x4.st
timeout 120 ./thrt HeavyTile 10 ${algorithm} < worlds/2-4x4.st
timeout 120 ./thrt HeavyTile 10 ${algorithm} < worlds/3-4x4.st
# timeout 120 ./thrt HeavyTile 10 ${algorithm} < worlds/4-4x4.st
# timeout 120 ./thrt HeavyTile 10 ${algorithm} < worlds/5-4x4.st
# timeout 120 ./thrt HeavyTile 10 ${algorithm} < worlds/6-4x4.st
# timeout 120 ./thrt HeavyTile 10 ${algorithm} < worlds/7-4x4.st
# timeout 120 ./thrt HeavyTile 10 ${algorithm} < worlds/8-4x4.st

timeout 120 ./thrt HeavyTile 30 ${algorithm} < worlds/1-4x4.st
timeout 120 ./thrt HeavyTile 30 ${algorithm} < worlds/2-4x4.st
timeout 120 ./thrt HeavyTile 30 ${algorithm} < worlds/3-4x4.st
# timeout 120 ./thrt HeavyTile 30 ${algorithm} < worlds/4-4x4.st
# timeout 120 ./thrt HeavyTile 30 ${algorithm} < worlds/5-4x4.st
# timeout 120 ./thrt HeavyTile 30 ${algorithm} < worlds/6-4x4.st
# timeout 120 ./thrt HeavyTile 30 ${algorithm} < worlds/7-4x4.st
# timeout 120 ./thrt HeavyTile 30 ${algorithm} < worlds/8-4x4.st

# timeout 120 ./thrt HeavyTile 300 ${algorithm} < worlds/1-4x4.st
# timeout 120 ./thrt HeavyTile 300 ${algorithm} < worlds/2-4x4.st
# timeout 120 ./thrt HeavyTile 300 ${algorithm} < worlds/3-4x4.st
# timeout 120 ./thrt HeavyTile 300 ${algorithm} < worlds/4-4x4.st
# timeout 120 ./thrt HeavyTile 300 ${algorithm} < worlds/5-4x4.st
# timeout 120 ./thrt HeavyTile 300 ${algorithm} < worlds/6-4x4.st
# timeout 120 ./thrt HeavyTile 300 ${algorithm} < worlds/7-4x4.st
# timeout 120 ./thrt HeavyTile 300 ${algorithm} < worlds/8-4x4.st

timeout 120 ./thrt HeavyTile 1000 ${algorithm} < worlds/1-4x4.st
timeout 120 ./thrt HeavyTile 1000 ${algorithm} < worlds/2-4x4.st
timeout 120 ./thrt HeavyTile 1000 ${algorithm} < worlds/3-4x4.st
# timeout 120 ./thrt HeavyTile 1000 ${algorithm} < worlds/4-4x4.st
# timeout 120 ./thrt HeavyTile 1000 ${algorithm} < worlds/5-4x4.st
# timeout 120 ./thrt HeavyTile 1000 ${algorithm} < worlds/6-4x4.st
# timeout 120 ./thrt HeavyTile 1000 ${algorithm} < worlds/7-4x4.st
# timeout 120 ./thrt HeavyTile 1000 ${algorithm} < worlds/8-4x4.st