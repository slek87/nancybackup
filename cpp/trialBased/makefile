CC=g++ 

all: th thrt thrt1

th: trialbasedTest.cpp TrialBased.h
	$(CC) -g -O3 -std=c++11 trialbasedTest.cpp -o th
	
thrt: trialbasedTestRT.cpp TrialBasedRealTimeSearch.h
	$(CC) -g -O3 -std=c++11 trialbasedTestRT.cpp -o thrt

thrts: trialbasedTestRT.cpp TrialBasedRealTimeSearch.h
	$(CC) -g -O3 -static -std=c++11 trialbasedTestRT.cpp -o thrt

thrt1: trialbasedTestRT_1.cpp TrialBasedRealTimeSearch_1.h
	$(CC) -g -O3 -std=c++11 trialbasedTestRT_1.cpp -o thrt1

clean:
	rm -f th thrt
