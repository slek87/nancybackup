CC=g++ 

all: th thrt thrtdhe

th: trialbasedTest.cpp TrialBased.h
	$(CC) -g -O3 -std=c++11 trialbasedTest.cpp -o th
	
thrt: trialbasedTestRT.cpp TrialBasedRealTimeSearch.h
	$(CC) -g -O3 -std=c++11 trialbasedTestRT.cpp -o thrt

thrts: trialbasedTestRT.cpp TrialBasedRealTimeSearch.h
	$(CC) -g -O3 -static -std=c++11 trialbasedTestRT.cpp -o thrt

thrtdhe: trialbasedTestRTDHE.cpp TrialBasedRealTimeSearchDHE.h
	$(CC) -g -O3 -std=c++11 trialbasedTestRTDHE.cpp -o thrtdhe

clean:
	rm -f th thrt thrtdhe
