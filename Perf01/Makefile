## configuration

OS=`uname | tr [A-Z] [a-z]`

PLOT_DIR=plot-data
AMDAR_RANGE_PY=50 120
AMDAR_RANGE=10 400

WC_FILES=test-data/big.txt test-data/poem.txt test-data/500kb.txt
WC_ARGS=50 $(WC_FILES)

AMDAR_PLOT_FILES=plot-data/amdar_cpp.tsv plot-data/amdar_go.tsv plot-data/amdar_rust.tsv plot-data/amdar_scala.tsv plot-data/amdar_java.tsv plot-data/amdar_py.tsv
WC_PLOT_FILES_EXCLUDE_SCALA=plot-data/wc_cpp.tsv plot-data/wc_go.tsv plot-data/wc_rust.tsv plot-data/wc_java.tsv plot-data/wc_py.tsv
WC_PLOT_FILES=$(WC_PLOT_FILES_EXCLUDE_SCALA) plot-data/wc_scala.tsv

#

## c options

GCC=g++
C_OPT=-std=c++11 -pthread

## scala java

JAR=./java-scala/target/scala-2.12/java-scala.jar

## targets

all: dev graph
dev: clean build exec_langs


## --------------------------------------------------------

clean: clean_bin clean_graph
	@echo "clean"


clean_bin:
	@rm -f cpp/matrix cpp/wc golang/matrix golang/wc
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
	@cd cpp && $(GCC) $(C_OPT) wc.cpp -o wc
	@cd cpp && $(GCC) $(C_OPT) httpd.cpp -o httpd

bin_rust:
	@cd rust && cargo install --root target/install

jar_sbt:
	@cd java-scala && sbt assembly

bin_go:
	@cd golang && go build -o matrix matrix.go 
	@cd golang && go build -o wc wc.go 
	@cd golang && go build -o httpd httpd.go 


## --------------------------------------------------------

exec_langs: do_prep run_py run_go run_scala run_java run_cpp run_rust
	@echo "sports"

do_prep:
	@mkdir -p $(PLOT_DIR)

run_py: do_prep
	@bash pmon/pmon 'python3 python/matrix.py $(AMDAR_RANGE_PY)' > $(PLOT_DIR)/amdar_py.tsv
	@bash pmon/pmon 'python3 python/wc.py 6 $(WC_FILES)' > $(PLOT_DIR)/wc_py.tsv

run_go: do_prep
	@bash pmon/pmon './golang/matrix $(AMDAR_RANGE)' > $(PLOT_DIR)/amdar_go.tsv
	@bash pmon/pmon './golang/wc $(WC_ARGS)' > $(PLOT_DIR)/wc_go.tsv

run_scala: do_prep
	@bash pmon/pmon 'java -cp $(JAR) example.SMain $(AMDAR_RANGE)' > $(PLOT_DIR)/amdar_scala.tsv
	@bash pmon/pmon 'java -cp $(JAR) example.SMain 25 $(WC_FILES)' > $(PLOT_DIR)/wc_scala.tsv

run_java: do_prep
	@bash pmon/pmon 'java -cp $(JAR) example.Matrix $(AMDAR_RANGE)' > $(PLOT_DIR)/amdar_java.tsv
	@bash pmon/pmon 'java -cp $(JAR) example.WordCounter $(WC_ARGS)' > $(PLOT_DIR)/wc_java.tsv

run_cpp: do_prep
	@bash pmon/pmon './cpp/matrix $(AMDAR_RANGE)' > $(PLOT_DIR)/amdar_cpp.tsv
	@bash pmon/pmon './cpp/wc $(WC_ARGS)' > $(PLOT_DIR)/wc_cpp.tsv

run_rust: do_prep
	@bash pmon/pmon './rust/target/install/bin/matrix $(AMDAR_RANGE)'  > $(PLOT_DIR)/amdar_rust.tsv
	@bash pmon/pmon './rust/target/install/bin/wc 1000 $(WC_FILES)'  > $(PLOT_DIR)/wc_rust.tsv

## --------------------------------------------------------

graph:
	@echo $(OS)
	@python pmon/graph.py 'cpu%' amdar_cpu_$(OS).png $(AMDAR_PLOT_FILES)
	@python pmon/graph.py 'mem(kb)' amdar_mem_$(OS).png $(AMDAR_PLOT_FILES)
	@python pmon/graph.py 'cpu%' wc_cpu_$(OS).png $(WC_PLOT_FILES)
	@python pmon/graph.py 'mem(kb)' wc_mem_$(OS).png $(WC_PLOT_FILES_EXCLUDE_SCALA)

