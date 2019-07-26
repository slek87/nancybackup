CC=g++ 

all: risk fhat lsslrta ie 

risk: expansionTestRisk.cpp
	$(CC) -g -O3 -std=c++11 expansionTestRisk.cpp -o RISKexpansionTest

fhat: expansionTestFHat.cpp
	$(CC) -g -O3 -std=c++11 expansionTestFHat.cpp -o FHATexpansionTest

lsslrta: expansionTestLSSLRTA.cpp
	$(CC) -g -O3 -std=c++11 expansionTestLSSLRTA.cpp -o LSSLRTAexpansionTest

ie: expansionTestIE.cpp
	$(CC) -g -O3 -std=c++11 expansionTestIE.cpp -o IEexpansionTest


clean:
	rm -f risk risk_s fhat fhat_s lsslrta lsslrta_s ie ie_s
