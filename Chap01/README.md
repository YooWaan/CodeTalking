Chap 01
===========

## Overview





## Memo


### Go

- setup  export GOPATH=/Users/ryo.terunuma/works/Study/CodeTalking/Chap01/GoLang

- build go install <package name>


### C

- setup GYP_GENERATORS=ninja gyp hello.gyp --toplevel-dir=. --depth=0

- build ninja



### concurrency

- Add option "cflags_cc = -std=c++11" to concurreny CLang

.
### dependecny

- run
  $ go build github.com/pborman/uuid
  $ go get github.com/pborman/uuid

