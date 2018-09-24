## configuration

OS=`uname | tr [A-Z] [a-z]`

PLOT_DIR=plot-data
AMDAR_RANGE_PY=90 130
AMDAR_RANGE=10 400

WC_FILES=test-data/big.txt test-data/poem.txt test-data/500kb.txt
WC_ARGS=100 $(WC_FILES)

AMDAR_PLOT_FILES=plot-data/amdar_cpp.tsv plot-data/amdar_go.tsv plot-data/amdar_rust.tsv plot-data/amdar_scala.tsv plot-data/amdar_java.tsv plot-data/amdar_py.tsv
WC_PLOT_FILES_JVM=plot-data/wc_scala.tsv plot-data/wc_java.tsv
WC_PLOT_FILES_EXCLUDE_JVM=plot-data/wc_cpp.tsv plot-data/wc_go.tsv plot-data/wc_rust.tsv plot-data/wc_py.tsv
WC_PLOT_FILES=$(WC_PLOT_FILES_EXCLUDE_JVM) $(WC_PLOT_FILES_JVM)

HT_PLOT_JVM=plot-data/ht_scala.tsv plot-data/ht_java.tsv
HT_PLOT_NO_JVM=plot-data/ht_cpp.tsv plot-data/ht_go.tsv plot-data/ht_rust.tsv plot-data/ht_py.tsv
HT_PLOT_FILES=$(HT_PLOT_NO_JVM) $(HT_PLOT_JVM) 

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
	@rm -f cpp/matrix cpp/wc cpp/httpd golang/matrix golang/wc golang/httpd
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

exec_langs: do_prep run_matrix run_wc
	@echo "sports"

do_prep:
	@mkdir -p $(PLOT_DIR)

run_matrix: do_prep
	@bash pmon/pmon 'python3 python/matrix.py $(AMDAR_RANGE_PY)' > $(PLOT_DIR)/amdar_py.tsv
	@bash pmon/pmon './golang/matrix $(AMDAR_RANGE)' > $(PLOT_DIR)/amdar_go.tsv
	@bash pmon/pmon 'java -cp $(JAR) example.SMain $(AMDAR_RANGE)' > $(PLOT_DIR)/amdar_scala.tsv
	@bash pmon/pmon 'java -cp $(JAR) example.Matrix $(AMDAR_RANGE)' > $(PLOT_DIR)/amdar_java.tsv
	@bash pmon/pmon './cpp/matrix $(AMDAR_RANGE)' > $(PLOT_DIR)/amdar_cpp.tsv
	@bash pmon/pmon './rust/target/install/bin/matrix $(AMDAR_RANGE)'  > $(PLOT_DIR)/amdar_rust.tsv

run_wc: do_prep
	@bash pmon/pmon 'python3 python/wc.py 6 $(WC_FILES)' > $(PLOT_DIR)/wc_py.tsv
	@bash pmon/pmon './golang/wc $(WC_ARGS)' > $(PLOT_DIR)/wc_go.tsv
	@bash pmon/pmon 'java -cp $(JAR) example.SMain 25 $(WC_FILES)' > $(PLOT_DIR)/wc_scala.tsv
	@bash pmon/pmon 'java -cp $(JAR) example.WordCounter $(WC_ARGS)' > $(PLOT_DIR)/wc_java.tsv
	@bash pmon/pmon './cpp/wc $(WC_ARGS)' > $(PLOT_DIR)/wc_cpp.tsv
	@bash pmon/pmon './rust/target/install/bin/wc $(WC_ARGS)'  > $(PLOT_DIR)/wc_rust.tsv

run:
	#@bash pmon/pmon 'java -cp $(JAR) example.SMain 25 $(WC_FILES)' > $(PLOT_DIR)/wc_scala.tsv
	@bash pmon/pmon 'java -cp $(JAR) example.WordCounter 100 $(WC_FILES)' > $(PLOT_DIR)/wc_java.tsv
	#@bash pmon/pmon './rust/target/install/bin/wc 100 $(WC_FILES)'  > $(PLOT_DIR)/wc_rust.tsv

#
# bash pmon/pmon './golang/httpd' > plot-data/ht_go.tsv
# bash pmon/pmon 'java -cp ./java-scala/target/scala-2.12/java-scala.jar example.SMain 1000' > plot-data/ht_scala.tsv
# bash pmon/pmon 'java -cp ./java-scala/target/scala-2.12/java-scala.jar example.HttpApp 1000' > plot-data/ht_java.tsv
# bash pmon/pmon './rust/target/install/bin/httpd' > plot-data/ht_rust.tsv
# bash pmon/pmon './cpp/httpd' > plot-data/ht_cpp.tsv
# bash pmon/pmon 'python3 python/httpd.py' > plot-data/ht_py.tsv
#
# ab -n 1000 -c 10 -p ./test-data/500kb.txt http://127.0.0.1:5100/
#



## --------------------------------------------------------

graph: graph_matrix graph_wc graph_http
	@echo $(OS)

graph_matrix:
	@python pmon/graph.py 'cpu%' amdar_cpu_$(OS).png $(AMDAR_PLOT_FILES)
	@python pmon/graph.py 'mem(kb)' amdar_mem_$(OS).png $(AMDAR_PLOT_FILES)

graph_wc:
	@python pmon/graph.py 'cpu%' wc_cpu_$(OS).png $(WC_PLOT_FILES)
	@python pmon/graph.py 'mem(kb)' wc_mem_no_jvm_$(OS).png $(WC_PLOT_FILES_EXCLUDE_JVM)
	@python pmon/graph.py 'mem(kb)' wc_mem_jvm_$(OS).png $(WC_PLOT_FILES_JVM)
	@python pmon/graph.py 'mem(kb)' wc_mem_all_$(OS).png $(WC_PLOT_FILES)

graph_http:
	@python pmon/graph.py 'cpu%' ht_cpu_$(OS).png $(HT_PLOT_FILES)
	@python pmon/graph.py 'mem(kb)' ht_mem_no_jvm_$(OS).png $(HT_PLOT_NO_JVM)
	@python pmon/graph.py 'mem(kb)' ht_mem_jvm_$(OS).png $(HT_PLOT_JVM)
	@python pmon/graph.py 'mem(kb)' ht_mem_all_$(OS).png $(HT_PLOT_FILES)

