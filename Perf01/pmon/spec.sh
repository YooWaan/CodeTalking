#!/bin/sh

os=$(uname | tr [A-A] [a-z])

if [ "${os}" = "darwin" ]; then
	system_profiler SPHardwareDataType
else
	cat /proc/cpuinfo | grep -e 'processor\|model name' | sort | uniq
	cat /proc/meminfo | grep MemTotal
fi


