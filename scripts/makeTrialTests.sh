#!/bin/bash

if (($# == 1))
then
    arg=$1
    if [ "$arg" = "static" ] 
    then
        g++ -std=c++11 -O3 -static ../cpp/trialBased/trialbasedTestRT.cpp -o ../../build_release/trialBasedTest
        chmod a+x ../../build_release/trialBasedTest
    else
        outFile=$1
        g++ -std=c++11 -O3 ../cpp/trialBased/trialbasedTestRT.cpp -o ../../build_release/${outFile}
        chmod a+x ../../build_release/${outFile}
    fi
else
    g++ -std=c++11 -O3 ../cpp/trialBased/trialbasedTestRT.cpp -o ../../build_release/trialBasedTest
    chmod a+x ../../build_release/trialBasedTest
fi