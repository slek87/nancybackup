#!/bin/bash

if (($# == 1))
then
    arg=$1
    if [ "$arg" = "static" ] 
    then
        g++ -std=c++11 -O3 -static ../cpp/trialBased/trialbasedTestRT.cpp -o ../../build_release/trialBasedTest
        g++ -std=c++11 -O3 -static ../cpp/expansionTestFHat.cpp -o ../../build_release/FHATexpansionTest
        g++ -std=c++11 -O3 -static ../cpp/expansionTestIE.cpp -o ../../build_release/IEexpansionTest
        g++ -std=c++11 -O3 -static ../cpp/expansionTestIEP.cpp -o ../../build_release/IEPexpansionTest
        g++ -std=c++11 -O3 -static ../cpp/expansionTestLSSLRTA.cpp -o ../../build_release/LSSLRTAexpansionTest
        g++ -std=c++11 -O3 -static ../cpp/expansionTestRisk.cpp -o ../../build_release/RISKexpansionTest
        g++ -std=c++11 -O3 -static ../cpp/expansionTestIEPP.cpp -o ../../build_release/IEPPexpansionTest

    fi
else
    g++ -std=c++11 -O3  ../cpp/trialBased/trialbasedTestRT.cpp -o ../../build_release/trialBasedTest
    g++ -std=c++11 -O3  ../cpp/expansionTestFHat.cpp -o ../../build_release/FHATexpansionTest
    g++ -std=c++11 -O3  ../cpp/expansionTestIE.cpp -o ../../build_release/IEexpansionTest
    g++ -std=c++11 -O3  ../cpp/expansionTestIEP.cpp -o ../../build_release/IEPexpansionTest
    g++ -std=c++11 -O3  ../cpp/expansionTestIEPP.cpp -o ../../build_release/IEPPexpansionTest
    g++ -std=c++11 -O3  ../cpp/expansionTestLSSLRTA.cpp -o ../../build_release/LSSLRTAexpansionTest
    g++ -std=c++11 -O3  ../cpp/expansionTestRisk.cpp -o ../../build_release/RISKexpansionTest

fi

chmod a+x ../../build_release/trialBasedTest
chmod a+x ../../build_release/FHATexpansionTest
chmod a+x ../../build_release/IEexpansionTest
chmod a+x ../../build_release/IEPexpansionTest
chmod a+x ../../build_release/LSSLRTAexpansionTest
chmod a+x ../../build_release/RISKexpansionTest