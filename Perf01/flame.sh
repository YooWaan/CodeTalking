#!/bin/sh

kind=$1
outfile=out-${kind}.perf
foldfile=fold-${kind}.perf

# for linux
sudo perf record -F 99 -a -g -- $2
sudo perf script > $outfile

# fold out
./stackcollapse-perf.pl $outfile > $foldfile

# svg out
./flamegraph.pl $foldfile > kernek_${kind}.svg
grep cpuid $foldfile | ./flamegraph.pl > cpu_${kind}.svg
