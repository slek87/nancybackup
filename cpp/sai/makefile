CC=g++ 

all: th as

th: trialbasedTest.cpp trialbased.h
	$(CC) -g -O3 -std=c++11 trialbasedTest.cpp -o th

as: offlineastarTest.cpp 
	$(CC) -g -O3 -std=c++11 offlineastarTest.cpp -o as
	
clean:
	rm -f th as
