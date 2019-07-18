CC=g++ 

all: risk fhat lsslrta ie 

static: risk_s fhat_s lsslrta_s ie_s

risk: expansionTestRisk.cpp
	$(CC) -g -O3 -std=c++11 expansionTestRisk.cpp -o expansionTestRisk

risk_s: expansionTestRisk.cpp
	$(CC) -g -static -O3 expansionTestRisk.cpp -o expansionTestRisk_s	

fhat: expansionTestFHat.cpp
	$(CC) -g -O3 -std=c++11 expansionTestFHat.cpp -o expansionTestFHat

fhat_s: expansionTestFHat.cpp
	$(CC) -g -static -O3 expansionTestFHat.cpp -o expansionTestFHat_s	

lsslrta: expansionTestLSSLRTA.cpp
	$(CC) -g -O3 -std=c++11 expansionTestLSSLRTA.cpp -o expansionTestLSSLRTA

lsslrta_s: expansionTestLSSLRTA.cpp
	$(CC) -g -static -O3 expansionTestLSSLRTA.cpp -o expansionTestLSSLRTA_s	

ie: expansionTestIE.cpp
	$(CC) -g -O3 -std=c++11 expansionTestIE.cpp -o expansionTestIE

ie_s: expansionTestIE.cpp
	$(CC) -g -static -O3 expansionTestIE.cpp -o expansionTestIE_s	

clean:
	rm -f risk risk_s fhat fhat_s lsslrta lsslrta_s ie ie_s
