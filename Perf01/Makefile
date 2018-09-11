## configuration


PLOT_DIR=plot-data
AMDAR_RANGE_PY=10 120
AMDAR_RANGE=10 400

## c options

GCC=g++
C_OPT=-std=c++11 -pthread

## scala java

JAR=./java-scala/target/scala-2.12/java-scala.jar

## targets

all: dev graph
dev: clean build do_sports


## --------------------------------------------------------

clean: clean_bin clean_graph
	@echo "clean"


clean_bin:
	@rm -f cpp/matrix
	@cd rust && cargo clean
	@cd java-scala && sbt clean

clean_result:
	@rm -f $(PLOT_DIR)

clean_graph:
	@rm -f *.png

## --------------------------------------------------------

build: bin_cpp bin_rust bin_go jar_sbt
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


do_amdar: amdar_py amdar_go amdar_scala amdar_java amdar_cpp amdar_rust
	@echo "amdar"

amdar_py: do_prep
	@bash pmon/pmon 'python3 python/matrix.py $(AMDAR_RANGE_PY)' > $(PLOT_DIR)/amdar_py.tsv

amdar_go: do_prep
	@bash pmon/pmon './golang/matrix $(AMDAR_RANGE)' > $(PLOT_DIR)/amdar_go.tsv

amdar_scala: do_prep
	@bash pmon/pmon 'java -cp $(JAR) example.SMain $(AMDAR_RANGE)' > $(PLOT_DIR)/amdar_scala.tsv

amdar_java: do_prep
	@bash pmon/pmon 'java -cp $(JAR) example.Matrix $(AMDAR_RANGE)' > $(PLOT_DIR)/amdar_java.tsv

amdar_cpp: do_prep
	@bash pmon/pmon './cpp/matrix $(AMDAR_RANGE)' > $(PLOT_DIR)/amdar_cpp.tsv

amdar_rust: do_prep
	@bash pmon/pmon './rust/target/install/bin/matrix $(AMDAR_RANGE)'  > $(PLOT_DIR)/amdar_rust.tsv

## --------------------------------------------------------

graph:
	@python pmon/graph.py 'cpu%' amdar_cpu.png plot-data/amdar_cpp.tsv plot-data/amdar_go.tsv plot-data/amdar_rust.tsv plot-data/amdar_scala.tsv plot-data/amdar_java.tsv plot-data/amdar_py.tsv
	@python pmon/graph.py 'mem(kb)' amdar_mem.png plot-data/amdar_cpp.tsv plot-data/amdar_go.tsv plot-data/amdar_rust.tsv plot-data/amdar_scala.tsv plot-data/amdar_java.tsv plot-data/amdar_py.tsv
