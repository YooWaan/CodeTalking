#!/bin/sh

kind=$1
perfdir="perf-data"
outfile=./${perfdir}/out-${kind}.perf
foldfile=./${perfdir}/fold-${kind}.perf
httpd=$2
bench_args=$3
wait_time=$4
dist_flame=$5

# for mac
#ps_format="-o pid,pcpu,rss,etime"
# ubuntu
ps_format="-o pid,pcpu,size,bsdtime"

backgroundab()
{
  echo "apache bench"
  ab $bench_args http://127.0.0.1:5100/
  echo "kill $pid"
  # kill httd server
  kill $pid
}

flame()
{
  sudo perf record -F 99 -a -g -p $pid
  sudo perf script > $outfile

  ./stackcollapse-perf.pl $outfile > $foldfile
  ./flamegraph.pl $foldfile > kernel_${kind}.svg

  rm $outfile $foldfile
}

wait_process()
{
  python -c "
import time; import subprocess
start_time = time.time()
try:
 while subprocess.check_output('ps -p $pid $ps_format | wc -l', shell=True).decode('utf-8').strip() == '2':
    print('%s %s' % (time.time()-start_time, subprocess.check_output('ps -p $pid $ps_format | tail -n 1 | grep -v CPU', shell=True).decode('utf-8').rstrip()))
except:
 pass
" > $dist_flame
}

# start httpd server
$httpd &
pid=$!

echo "$httpd :process: $pid"
echo "waiting... $httpd [process: $pid]. ab $bench_args"
sleep $wait_time

backgroundab &

if [ "${dist_flame}" = "yes" ] ; then
  flame
else
  wait_process
fi
