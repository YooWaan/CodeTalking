#!/bin/sh

function line()
{
    for f in `ls $1`; do
        echo $f `cat $f | awk '{if (length($0) > 0) { print $0;}}' | grep -v "#\|\/\/" | wc -l`
    done
}

line 'python/*.py'
line 'cpp/*.cpp'
line 'java-scala/src/main/java/example/*.java'
line 'java-scala/src/main/scala/example/*.scala'
line 'rust/src/*.rs'
line 'golang/*.go'
