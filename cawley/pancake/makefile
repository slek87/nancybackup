CC=gcc
CFLAGS=-ansi -pedantic -Wall -Werror

all:pancake

pancake: pancake.c main.c
	$(CC) $(CFLAGS) -DNDEBUG -O2 pancake.c main.c -o pancake
	
clean:
	rm -f pancake
	rm -f *.o

