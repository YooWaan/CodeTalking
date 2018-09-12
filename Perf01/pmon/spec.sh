#!/bin/bash

os=$(uname | tr [A-A] [a-z])

if [ "${os}" == "darwin" ]; then
	system_profiler SPHardwareDataType
else
	cat /proc/cpuinfo
	cat /proc/meminfo
fi


