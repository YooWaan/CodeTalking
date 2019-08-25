---
weight: 7
---

<!-- : .text-data -->Multi Threading


---
<!--: .wrap -->

## <i class="icon-cplusplus"></i>

- posix thread

https://computing.llnl.gov/tutorials/pthreads/#Thread

## <i class="icon-java"></i>

- native thread

http://openjdk.java.net/groups/hotspot/docs/RuntimeOverview.html#Thread%20Management|outline

## <i class="icon-python"></i>

- グローバルインタープリンタロック（GIL）
- インタプリタのスレッドによって保持されるスレッドセーフでないコードを、他のスレッドと共有してしまうことを防ぐための排他 ロックである。インタプリタのひとつのプロセスごとに必ずひとつの GIL が存在する。

https://docs.python.org/ja/3/c-api/init.html?highlight=gil#thread-state-and-the-global-interpreter-lock


---
<!--: .wrap -->

|||

## <i class="icon-scala"></i>

- same java

```
import java.util.concurrent.ThreadPoolExecutor
import java.util.concurrent.ForkJoinPool

class ForkJoinTaskSupport(val environment: ForkJoinPool = ForkJoinTasks.defaultForkJoinPool)
extends TaskSupport with AdaptiveWorkStealingForkJoinTasks

class ThreadPoolTaskSupport(val environment: ThreadPoolExecutor = ThreadPoolTasks.defaultThreadPool)
extends TaskSupport with AdaptiveWorkStealingThreadPoolTasks
```

|||

## <i class="icon-rust"></i>

- the green-threaded model is called the M:N model:

https://doc.rust-lang.org/1.30.0/book/second-edition/ch16-01-threads.html

## <i class="icon-go"></i>

- gorutine

https://christina04.hatenablog.com/entry/why-goroutine-is-good

---
<!--: wrap -->

### 処理内容

<!--: content-left -->NxN の行列のA,Bの積計算　A・B＝C を N を大きくしていく処理をマルチスレッドで実行

```python
def matrix_mul(m1, m2):
    sz = len(m1)
    return [[
    reduce(lambda x,y: x+y ,[m1[i][m] * m2[m][n] for m in range(0,sz)])
     for n in range(0, sz)]
     for i in range(0, sz)]
```

scala

```scala
def mul(m1: Array[Array[Int]], m2: Array[Array[Int]]): Array[Int] = {
  val mt = m2.transpose
  m1.zipWithIndex.map { case (v, i) => v zip mt(i) map Function.tupled(_*_) reduceLeft(_+_)}
}
```

---

## 定性的な観点


<ul class="flexblock specs">
  <li>
    <div>
      <h2>{{< svg fa-check >}}
      ThreadExecutor
      </h2>
      標準ライブラリのありなし  易 🦸 〜 😀 〜 🤔 難
    </div>
  </li>
  <li>
    <div>
      <h2>{{< svg fa-times >}}NxNの２次元配列の作りやすさ</h2>
      dddd
    </div>
  </li>
</ul>

---

## Result

|||

![](/img/result/amdar_cpu_linux.png)

|||


![](/img/result/amdar_mem_linux.png)

---

## <i class="icon-cplusplus"></i> C++

<script src="http://gist-it.appspot.com/https://github.com/YooWaan/CodeTalking/blob/PF/Perf01/cpp/matrix.cpp"></script>


### CPU/ Mem Usage

![](/img/result/graph/cpp_matrix_cpu_linux.png)
![](/img/result/graph/cpp_matrix_mem_linux.png)

### Flame graph

![](/img/result/flame/kernel_cpp-matrix.svg)

---

## <i class="icon-java"></i> Java

<script src="http://gist-it.appspot.com/https://github.com/YooWaan/CodeTalking/blob/PF/Perf01/java-scala/src/main/java/example/Matrix.java"></script>


### CPU/ Mem Usage

![](/img/result/graph/java_matrix_cpu_linux.png)
![](/img/result/graph/java_matrix_mem_linux.png)

### Flame graph

![](/img/result/flame/kernel_java-matrix.svg)

---

## <i class="icon-python"></i> Python

<script src="http://gist-it.appspot.com/https://github.com/YooWaan/CodeTalking/blob/PF/Perf01/python/matrix.py"></script>


### CPU/ Mem Usage

![](/img/result/graph/py_matrix_cpu_linux.png)
![](/img/result/graph/py_matrix_mem_linux.png)

### Flame graph

![](/img/result/flame/kernel_py-matrix.svg)

---

## <i class="icon-scala"></i> Scala

<script src="http://gist-it.appspot.com/https://github.com/YooWaan/CodeTalking/blob/PF/Perf01/java-scala/src/main/scala/example/Mat.java"></script>


### CPU/ Mem Usage

![](/img/result/graph/scala_matrix_cpu_linux.png)
![](/img/result/graph/scala_matrix_mem_linux.png)

### Flame graph

![](/img/result/flame/kernel_scala-matrix.svg)

---

## <i class="icon-rust"></i> Rust

<script src="http://gist-it.appspot.com/https://github.com/YooWaan/CodeTalking/blob/PF/Perf01/rust/src/main.rs"></script>


### CPU/ Mem Usage

![](/img/result/graph/rust_matrix_cpu_linux.png)
![](/img/result/graph/rust_matrix_mem_linux.png)

### Flame graph

![](/img/result/flame/kernel_rust-matrix.svg)

---

## <i class="icon-go"></i> Golang

<script src="http://gist-it.appspot.com/https://github.com/YooWaan/CodeTalking/blob/PF/Perf01/golang/matrix.go"></script>


### CPU/ Mem Usage

![](/img/result/graph/go_matrix_cpu_linux.png)
![](/img/result/graph/go_matrix_mem_linux.png)

### Flame graph

![](/img/result/flame/kernel_go-matrix.svg)


---

## Result Table

<!--: no-border -->
| Lang                           | Lines   | libs   | Matrix | Runtime(sec) | CPU(%)   | Mem(mb)  | Point | Rank |
| ------------------------------ | ------- | ------ | ------ | ------------ | -------- | -------- | ----- | ---- |
| <i class="icon-cplusplus"></i> | 107 (5) | 🤔(3)  | 🤔(3)  | 11   (5)     | 323  (5) | 263  (2) | 23    | 6    |
| <i class="icon-java"></i>      | 64 (3)  | 🦸 (1) | 😀(2)  | 4.9   (3)    | 417 (3)  | 87  (1)  | 13    | 1    |
| <i class="icon-python"></i>    | 36 (2)  | 🦸 (1) | 🦸 (1) | 11     (6)   | 180  (6) | 45   (6) | 22    | 5    |
| <i class="icon-scala"></i>     | 20 (1)  | 🦸 (1) | 😀(2)  | 1.36  (2)    | 260  (4) | 635  (5) | 15    | 3    |
| <i class="icon-rust"></i>      | 87 (4)  | 😀 (2) | 😀(2)  | 1.20 (1)     | 731 (1)  | 518  (4) | 14    | 2    |
| <i class="icon-go"></i>        | 155 (6) | 😀 (2) | 😀(2)  | 6.4   (4)    | 425 (2)  | 480  (3) | 19    | 4    |

---

## Recap


・Pythonで並列処理しちゃダメ

・Cはチューニングしないとダメ

・Java/Rust/Scala あたりで書くと良い

・Golang は シンタックスシュガー が必要
