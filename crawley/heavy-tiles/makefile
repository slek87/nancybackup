CC=gcc
CFLAGS=-ansi -pedantic -Wall -Werror

SRC=	astar.c		\
	tiles.c		\
	mdist.c		\
	htable.c	\
	heap.c		\
	node.c		\
	system.c

all: tiles-solver tiles-solver_debug

tiles-solver: $(SRC)
	$(CC) $(CFLAGS) -DNDEBUG -O2 $^ -o tiles-solver


tiles-solver_debug: $(SRC)
	$(CC) $(CFLAGS) -g $^ -o tiles-solver_debug

clean:
	rm -f tiles-solver tiles-solver_debug
	rm -f *.o

