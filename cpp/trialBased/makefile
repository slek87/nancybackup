CC=g++ 

all: th thrt

th: trialbasedTest.cpp TrialBased.h
	$(CC) -g -O3 -std=c++11 trialbasedTest.cpp -o th
	
thrt: trialbasedTestRT.cpp TrialBasedRealTimeSearch.h
	$(CC) -g -O3 -std=c++11 trialbasedTestRT.cpp -o thrt
	
clean:
	rm -f th thrt
