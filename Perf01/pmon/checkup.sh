#!/bin/bash



function metrics()
{
   fnm=$(basename $1)
   msg=$(awk 'BEGIN{cpu=0;mem=0;time="";} {cpu=($3> cpu) ? $3:cpu; mem=($4 > mem) ? $4 : mem;time=$1;} END{printf("%s %d %d", time, cpu, mem);}' $1)
   echo $msg $fnm
}


for f in "$@"; do
   metrics $f
done

