CC=g++

all:  sliding tree pancake

: PuzzleTest.cpp 
	$(CC) -g -std=c++11 PuzzleTest.cpp -o Test

sliding: slidingPuzzleTest.cpp 
	$(CC) -g -std=c++11 slidingPuzzleTest.cpp -o slidingPuzzleTest

tree: treeTest.cpp 
	$(CC) -g -std=c++11 treeTest.cpp -o treeTest

pancake: pancakePuzzleTest.cpp 
	$(CC) -g -std=c++11 pancakePuzzleTest.cpp -o pancakePuzzleTest

clean:
	rm -f Test slidingPuzzleTest treeTest pancakePuzzleTest
