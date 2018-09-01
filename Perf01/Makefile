## configuration


PLOT_DIR=plot-data
AMDAR_RANGE=100 250

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
	@rm -f $(PLOT_DIR)


## --------------------------------------------------------

build: bin_cpp bin_rust jar_sbt bin_go
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
	@mkdir -p $(PLOT_DIR)

do_amdar: amdar_py amdar_go amdar_scala
	@echo "amdar"

amdar_py: do_prep
	@bash pmon/pmon 'python3 python/wc.py $(AMDAR_RANGE)' > $(PLOT_DIR)/amdar_py.tsv

amdar_go: do_prep
	@bash pmon/pmon './golang/matrix 100 200' > $(PLOT_DIR)/amdar_go.tsv

amdar_scala: do_prep
	@bash pmon/pmon 'java -cp ./java-scala/target/scala-2.12/java-scala.jar example.SMain $(AMDAR_RANGE)' > $(PLOT_DIR)/amdar_scala.tsv

amdar_java: do_prep
	@bash pmon/pmon 'java -cp ./java-scala/target/scala-2.12/java-scala.jar example.Matrix $(AMDAR_RANGE)' > $(PLOT_DIR)/amdar_scala.tsv

amdar_cpp: do_prep
	@bash pmon/pmon './cpp/matrix 100 200' > $(PLOT_DIR)/amdar_cpp.tsv

amdar_rust: do_prep
	@bash pmon/pmon './rust/target/install/bin/matrix 100 200'  > $(PLOT_DIR)/amdar_rust.tsv

## --------------------------------------------------------

graph:
	@python pmon/graph.py
