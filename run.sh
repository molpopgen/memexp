#!/bin/bash

nsamples=500000000

for maxcap in 20000000 10000000 5000000
do
    maxinc=`echo "$maxcap / 5" | bc -l`
    echo "C++"
    /usr/bin/time -f "%e %M" ./memexp 666 $nsamples 0 0
    /usr/bin/time -f "%e %M" ./memexp 666 $nsamples $maxcap $maxinc
    echo "C"
    /usr/bin/time -f "%e %M" ./memexpc 666 $nsamples 0 0
    /usr/bin/time -f "%e %M" ./memexpc 666 $nsamples $maxcap $maxinc
done
