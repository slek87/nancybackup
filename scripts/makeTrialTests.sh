#!/bin/bash

if (($# == 1))
then
    outFile=$1
    g++ -std=c++11 ../cpp/trialBased/trialbasedTestRT.cpp -o ../../build_release/${outFile}
    chmod a+x ../../build_release/${outFile}
else
    g++ -std=c++11 ../cpp/trialBased/trialbasedTestRT.cpp -o ../../build_release/trialBasedTest
    chmod a+x ../../build_release/trialBasedTest
fi