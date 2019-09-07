#!/bin/sh

kind=$1
perfdir="perf-data"
outfile=./${perfdir}/out-${kind}.perf
foldfile=./${perfdir}/fold-${kind}.perf
memstack=./${perfdir}/mem-${kind}.stack
scnt=stackcount-bpfcc
cmd=$2
hertz=99

perf_kernel() {
#	$cmd &
#	pid=$!
#	sudo perf record -F $hertz -a -g -p $pid
	sudo perf record -F 99 -a -g -- $cmd
	sudo perf script > $outfile

	# fold out
	./stackcollapse-perf.pl $outfile > $foldfile

	# svg out
	./flamegraph.pl $foldfile > kernel_${kind}.svg
	# grep cpuid $foldfile | ./flamegraph.pl --title "${kind}" > cpu_${kind}.svg

	# save perf data file
	sudo chown $USER: perf.data
	mv perf.data ${perfdir}/kernel-${kind}-record.data
}

perf_mem() {
	$cmd &
	pid=$!
	echo "$cmd [${pid}]"
	# for linux
	sudo perf record -F $hertz -a -g -e syscalls:sys_enter_brk -p $pid
	sudo perf script > $memstack
	./stackcollapse-perf.pl < $memstack | ./flamegraph.pl --color=mem --title="brk() ${kind}" --countname="calls" > ${perfdir}/mem-${kind}-out.svg

	# save perf data file
	sudo chown $USER: perf.data
	mv perf.data ${perfdir}/mem-${kind}-record.data
}


stackcnt_mem() {
	$cmd &
	pid=$!

	sudo $scnt -p $pid -U c:malloc
}

#echo "perf_mem: ${kind}"
# perf_mem
#stackcnt_mem
echo "perf_kernel: ${kind}"
perf_kernel
