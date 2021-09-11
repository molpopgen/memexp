#!/bin/bash

nsamples=100000000
maxcap=`echo "$nsamples / 5" | bc -l`
maxinc=5000000

echo "C++"
/usr/bin/time -f "%e %M" ./memexp 666 $nsamples 0 0
/usr/bin/time -f "%e %M" ./memexp 666 $nsamples $maxcap $maxinc
echo "C"
/usr/bin/time -f "%e %M" ./memexpc 666 $nsamples 0 0
/usr/bin/time -f "%e %M" ./memexpc 666 $nsamples $maxcap $maxinc
