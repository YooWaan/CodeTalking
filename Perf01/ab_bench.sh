#!/bin/sh

kind=$1
outfile=out-${kind}.perf
foldfile=fold-${kind}.perf
httpd=$2
bench_args=$3

# start httpd server
$httpd &
pid=$!

sleep 2
echo "waiting... $httpd [process: $pid]. ab $bench_args"
sudo perf record -F 99 -a -g -p $pid &

# run ab command
ab $bench_args http://127.0.0.1:5100/

sudo perf script > $outfile
./stackcollapse-perf.pl $outfile > $foldfile
./flamegraph.pl $foldfile > kernel_${kind}.svg

# kill httd server
kill $pid
rm $outfile $foldfile
