CC=g++ 

all: risk fhat lsslrta ie iep iepp

risk: expansionTestRisk.cpp
	$(CC) -g -O3 -std=c++11 expansionTestRisk.cpp -o RISKexpansionTest

fhat: expansionTestFHat.cpp
	$(CC) -g -O3 -std=c++11 expansionTestFHat.cpp -o FHATexpansionTest

lsslrta: expansionTestLSSLRTA.cpp
	$(CC) -g -O3 -std=c++11 expansionTestLSSLRTA.cpp -o LSSLRTAexpansionTest

ie: expansionTestIE.cpp
	$(CC) -g -O3 -std=c++11 expansionTestIE.cpp -o IEexpansionTest

iep: expansionTestIEP.cpp
	$(CC) -g -O3 -std=c++11 expansionTestIEP.cpp -o IEPexpansionTest

iepp: expansionTestIEPP.cpp
	$(CC) -g -O3 -std=c++11 expansionTestIEPP.cpp -o IEPPexpansionTest
	
clean:
	rm -f risk  fhat  lsslrta  ie iep iepp
