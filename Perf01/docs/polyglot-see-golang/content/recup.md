---
weight: 10
---

<!-- : .text-data -->Conclusion


---

## 勝手なRank



| Lang            | <i class="icon-cplusplus"></i> | <i class="icon-java"></i> | <i class="icon-python"></i> | <i class="icon-scala"></i> | <i class="icon-rust"></i> | <i class="icon-go"></i> |
| --------------- | ------------------------------:| -------------------------:| ---------------------------:| --------------------------:| -------------------------:| -----------------------:|
| Thread Point    |                             23 |                        13 |                          22 |                         15 |                        14 |                      19 |
| WordCount Point |                             19 |                        15 |                          23 |                         18 |                        20 |                      15 |
| Http Point      |                             16 |                        22 |                          23 |                         16 |                        19 |                      16 |
| Point 合計      |                             58 |                        50 |                          68 |                         49 |                        53 |                      50 |
| Point 平均      |                             19 |                        17 |                           23 |                          16 |                         18 |                       17 |
| Thread Rank     |                              6 |                         1 |                           5 |                          3 |                         2 |                       4 |
| WordCount Rank  |                              3 |                         1 |                           5 |                          2 |                         4 |                       1 |
| Http Rank       |                              1 |                         5 |                           6 |                          1 |                         4 |                       1 |
| Rank 合計       |                             10 |                         7 |                          16 |                          6 |                        10 |                       6 |
| Rank 平均       |                             3.33 |                         2.33 |                          5.33 |                          2.00 |                        3.33 |                       2.00 |



---
<!--: .wrap -->

## Polyglot な Summary

Golangは手続き型でかけるし、性能そこそこだしいいかな感

JVM優秀

Python は書きやすくなかったら オワコン

結局 コード量とか性能を見ると Scala とかに着地する。 が関数プログラミングという壁がある



== Python ドーピングの裏側 ==

```
AMDAR_RANGE_PY=90 130
AMDAR_RANGE=10 400
AB_ARGS_PY=-n 100 -c 4 -p ./test-data/500kb.txt
AB_ARGS=-n 10000 -c 4 -p ./test-data/500kb.txt

run_matrix: do_prep
        @bash pmon/pmon 'python3 python/matrix.py $(AMDAR_RANGE_PY)' > $(PLOT_DIR)/amdar_py.tsv

run_http:
        @sh ./ab_bench.sh 'pyhttpd' 'python3 python/httpd.py' '-n 20 -c 4 -p ./test-data/500kb.txt' 1 '$(PLOT_DIR)/ht_py.tsv'
        @sh ./ab_bench.sh 'gohttpd' 'golang/httpd' '$(AB_ARGS)' 1 '$(PLOT_DIR)/ht_go.tsv'
        @sh ./ab_bench.sh 'javahttpd' 'java -cp ./java-scala/target/scala-2.12/java-scala.jar example.HttpApp 10000' '$(AB_ARGS)' 2 '$(PLOT_DIR)/ht_java.tsv'
        @sh ./ab_bench.sh 'scalahttpd' 'java -cp ./java-scala/target/scala-2.12/java-scala.jar example.SMain 10000' '$(AB_ARGS)' 2 '$(PLOT_DIR)/ht_scala.tsv'
        @sh ./ab_bench.sh 'rusthttpd' './rust/target/install/bin/httpd' '$(AB_ARGS)' 1 '$(PLOT_DIR)/ht_rust.tsv'
        @sh ./ab_bench.sh 'cpphttpd' './cpp/httpd' '$(AB_ARGS)' 1 '$(PLOT_DIR)/ht_cpp.tsv'
```

---
<!--: .wrap -->

# Summary つづき

<hr/>

### 言語横断で評価ってむりぽ

### 横断的なワークロード分析って難しい

* CPUの使い方とか、みんな異なりすぎ

---
<!--: .wrap bg=bg-black bg=aligncenter bgimage=https://source.unsplash.com/bj3l739cwc8 -->

<b class="text-data bg-trans-light">end</b>
