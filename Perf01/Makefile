## configuration


RESULT_DIR=result


## c options

GCC=g++
C_OPT=-std=c++11 -pthread

## targets

all: clean build do_sports graph
dev: build do_sports graph


## --------------------------------------------------------

clean: clean_bin
	@echo "clean"


clean_bin:
	@rm -f cpp/matrix
	@cd rust && cargo clean
	@cd java-scala && sbt clean

clean_result:
	@rm -f $(RESULT_DIR)


## --------------------------------------------------------

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


## --------------------------------------------------------

do_sports: do_prep do_amdar
	@echo "sports"

do_prep:
	@mkdir $(RESULT_DIR)

do_amdar: amdar_py amdar_go
	@echo "amdar"

amdar_py:
	@bash pmon/pmon 'python3 python/wc.py 100 400' > $(RESULT_DIR)/amdar_py.tsv

amdar_go:
	@bash pmon/pmon './golang/matrix 100 400' > $(RESULT_DIR)/amdar_go.tsv


## --------------------------------------------------------

graph:
	@echo "graph"
