CC=g++ 

all: th as exas ex1 ex2

ex1: ex1.cpp trialbased.h
	$(CC) -g -O3 -std=c++11 ex1.cpp -o ex1
	
ex2: ex2.cpp trialbased.h
	$(CC) -g -O3 -std=c++11 ex2.cpp -o ex2

exas: exas.cpp trialbased.h offlineastar.h
	$(CC) -g -O3 -std=c++11 exas.cpp -o exas

th: trialbasedTest.cpp trialbased.h
	$(CC) -g -O3 -std=c++11 trialbasedTest.cpp -o th

as: offlineastarTest.cpp offlineastar.h
	$(CC) -g -O3 -std=c++11 offlineastarTest.cpp -o as
	
clean:
	rm -f th as exas ex1 ex2
