CC=g++ 

all: th thrt thrtl

th: trialbasedTest.cpp TrialBased.h
	$(CC) -g -O3 -std=c++11 trialbasedTest.cpp -o th
	
thrt: trialbasedTestRT.cpp TrialBasedRealTimeSearch.h
	$(CC) -g -O3 -std=c++11 trialbasedTestRT.cpp -o thrt

thrts: trialbasedTestRT.cpp TrialBasedRealTimeSearch.h
	$(CC) -g -O3 -static -std=c++11 trialbasedTestRT.cpp -o thrt

thrtl: trialbasedTestRTL.cpp TrialBasedRealTimeSearchL.h
	$(CC) -g -O3 -std=c++11 trialbasedTestRTL.cpp -o thrtl

clean:
	rm -f th thrt thrtl
