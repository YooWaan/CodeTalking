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

## Result Table

<table class="no-border">
<tr>
  <th>Lang</th>
  <th>Lines</th>
  <th>Libs</th>
  <th>Matrix</th>
  <th>Runtime</th>
  <th>CPU</th>
  <th>mem</th>
  <th>Point</th>
  <th>Rank</th>
</tr>

<tr>
  <td><i class="icon-java"></i></td>
  <td>1 <small>(100)</small></td>
  <td></td>
  <td></td>
  <td></td>
  <td></td>
  <td></td>
  <td></td>
  <td></td>
</tr>
<tr>
  <td><i class="icon-cplusplus"></i></td>
  <td></td>
  <td></td>
  <td></td>
  <td></td>
  <td></td>
  <td></td>
  <td></td>
  <td></td>
</tr>
<tr>
  <td><i class="icon-python"></i></td>
  <td></td>
  <td></td>
  <td></td>
  <td></td>
  <td></td>
  <td></td>
  <td></td>
  <td></td>
</tr>
<tr>
  <td><i class="icon-scala"></i></td>
  <td></td>
  <td></td>
  <td></td>
  <td></td>
  <td></td>
  <td></td>
  <td></td>
  <td></td>
</tr>
<tr>
  <td><i class="icon-rust"></i></td>
  <td></td>
  <td></td>
  <td></td>
  <td></td>
  <td></td>
  <td></td>
  <td></td>
  <td></td>
</tr>
<tr>
  <td><i class="icon-go"></i></td>
  <td></td>
  <td></td>
  <td></td>
  <td></td>
  <td></td>
  <td></td>
  <td></td>
  <td></td>
</tr>

</table>

---

## Recap
