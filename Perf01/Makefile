## configuration



## c options

GCC=g++
C_OPT=-std=c++11 -pthread

## targets

all: clean build do_sports graph
dev: build do_sports graph

clean: clean_bin
	@echo "clean"


clean_bin:
	@rm -f cpp/matrix
	@cd rust && cargo clean
	@cd java-scala && sbt clean

build: bin_cpp bin_rust jar_sbt
	@echo "build"


bin_cpp:
	@cd cpp && $(GCC) $(C_OPT) matrix.cpp -o matrix

bin_rust:
	@cd rust && cargo install --root target/install

jar_sbt:
	@cd java-scala && sbt assembly

bin_go:
	@cd golang && go build -o matrix matrix.go 

do_sports: do_amdar
	@echo "sports"

do_amdar:
	@echo "amdar"

amdar_py:
	bash pmon/pmon 'python3 python/wc.py'

graph:
	@echo "graph"
