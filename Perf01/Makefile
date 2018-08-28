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
	@mkdir -p $(RESULT_DIR)

do_amdar: amdar_py amdar_go
	@echo "amdar"

amdar_py: do_prep
	@bash pmon/pmon 'python3 python/wc.py 100 400' > $(RESULT_DIR)/amdar_py.tsv

amdar_go: do_prep
	@bash pmon/pmon './golang/matrix 100 400' > $(RESULT_DIR)/amdar_go.tsv

amdar_scala: do_prep
	@bash pmon/pmon 'java -cp ./java-scala/target/scala-2.12/wc-ja-assembly-0.1.0-SNAPSHOT.jar example.SMain 1 400' > $(RESULT_DIR)/amdar_scala.tsv


## --------------------------------------------------------

graph:
	@echo "graph"
