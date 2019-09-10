---
weight: 7
---

<!-- : .text-data -->Multi Threading

<!-- : .text-intro -->Matrix multiply  :: Report


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

|||

<ul class="flexblock specs">
  <li>
    <div>
      <h2>{{< svg fa-check >}}
      ThreadExecutor
      </h2>
      標準ライブラリまたはSntaxSugarで簡単実装のあり・なし
    </div>
  </li>
  <li>
    <div>
      <h2>{{< svg fa-check >}}NxNの２次元配列の作りやすさ</h2>
      配列の配列の構築
    </div>
  </li>
</ul>

|||

<ul class="flexblock specs">
  <li>
    <div>
      <h2>{{< svg fa-angellist >}} 易</h2>
      標準ライブラリまたは言語のSyntax Sugarがあって、使っていてとても良い感じ
    </div>
  </li>
  <li>
    <div>
      <h2>{{< svg fa-circle >}}普通</h2>
      標準ライブラリがある。または言語のSyntax Sugarで十分かける
    </div>
  </li>
  <li>
    <div>
      <h2>{{< svg fa-ban >}}難</h2>
      なんか頑張る感じ
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

```
template<typename Functor>
void matrix(int** value, int size, Functor func) {
  for (int i = 0; i < size ;i++) {
    for (int n = 0; n < size;n++) {
      value[i][n] = func(i, n);
    }
  }    
}

template<typename Functor>
void mem(int*** value, int size, Functor func) {
    int*** adr = value;
    *value = new int*[size];
    for (int i = 0; i < size ;i++) {
        (*value)[i] = new int[size];
        for (int n = 0; n < size ; n++) {
            (*value)[i][n] = 0;
        }
    }
    matrix(*value, size, func);
}

void mul(int** left, int** right, int** ans, int size) {
    for (int i = 0; i < size ;i++) {
        for (int n = 0; n < size ; n++) {
            for (int m = 0; m < size ; m++) {
                ans[i][n] += left[i][m] * right[m][n];
            }
        }
    }
}

int calc_worker(int size, Ctx *ctx) {
    std::unique_ptr<int*[]> lmx(new int*[size]);
    std::unique_ptr<int*[]> rmx(new int*[size]);
    std::unique_ptr<int*[]> ans(new int*[size]);

    auto lp = lmx.get();
    auto rp = rmx.get();
    auto ap = ans.get();

    mem(&lp, size, lfn);
    mem(&rp, size, rfn);
    mem(&ap, size, zfn);

    mul(lp, rp, ap, size);

    ctx->notify_done();
    return 1;
}

```


### CPU/ Mem Usage

![](/img/result/graph/cpp_matrix_cpu_linux.png)
![](/img/result/graph/cpp_matrix_mem_linux.png)

### Flame graph

<embed type="image/svg+xml" src="/img/result/flame/kernel_cpp-matrix.svg" />


---

## <i class="icon-java"></i> Java

```
int[][] mul(int[][] left, int[][] right) {
    int sz = left.length;
    int[][] ans = new int[sz][sz];
    for (int ii = 0; ii < sz ;ii++) {
        int[] row = new int[sz];
        for (int nn = 0; nn < sz ;nn++) {
            for (int mm = 0;mm < sz; mm++) {
                row[nn] += left[ii][mm] * right[mm][nn];
            }
        }
        ans[ii] = row;
    }
    return ans;
}

int[][] left(int size) {
    int[][] mat = new int[size][];
    IntStream.range(1, size + 1)
    .forEach(n -> {
        int[] val = new int[size];
        Arrays.fill(val, n);
        mat[n-1] = val;
    });
    return mat;
}

int[][] right(int size) {
    int[][] mat = new int[size][];
    IntStream.range(1, size + 1)
    .forEach(n -> {
        mat[n-1] = IntStream.range(1, size+1).toArray();
    });
    return mat;
}

public void calc(int start, int end) {
    long cnt = IntStream.range(start, end+1).parallel()
    .map(sz -> {
        int[][] ans = mul(left(sz), right(sz));
        //print(ans);
        return ans.length;
    }).count();
}

```

### CPU/ Mem Usage

![](/img/result/graph/java_matrix_cpu_linux.png)
![](/img/result/graph/java_matrix_mem_linux.png)

### Flame graph

<embed type="image/svg+xml" src="/img/result/flame/kernel_java-matrix.svg" />

---

## <i class="icon-python"></i> Python

```
def matrix_calc():
    start = int(sys.argv[1])
    end = int(sys.argv[2])

    futures = []
    with ThreadPoolExecutor(max_workers=32) as e:
        for i in range(start, end):
            futures.append(e.submit(matrix_mul, matrix(i), matrix_right(i)))

    result = wait(futures)
    return len(result.done)

def matrix(size):
    return [[i for n in range(i, i+size) ] for i in range(1, size+1)]

def matrix_right(size):
    return [[n for n in range(1, size+1)] for i in range(1, size+1)]

def matrix_mul(m1, m2):
    sz = len(m1)
    return [[reduce(lambda x,y: x+y ,[m1[i][m] * m2[m][n] for m in range(0,sz)]) for n in range(0,sz)] for i in range(0, sz)]
```

### CPU/ Mem Usage

![](/img/result/graph/py_matrix_cpu_linux.png)
![](/img/result/graph/py_matrix_mem_linux.png)

### Flame graph

<embed type="image/svg+xml" src="/img/result/flame/kernel_py-matrix.svg" />


---

## <i class="icon-scala"></i> Scala

```
def calc(start: Int, end: Int): Unit = {
  val ans = scala.collection.parallel.mutable.ParArray
    .range(start, end).map(x => mul(matrix(x), mat(x))).toList
}

def matrix(size: Int): Array[Array[Int]] = {
  Array.range(1, size).map(a => Array.range(1, size))
}

def mat(size: Int): Array[Array[Int]] = {
  Array.range(1, size).map(x => Array.fill(size-1){x})
}

def mul(m1: Array[Array[Int]], m2: Array[Array[Int]]): Array[Int] = {
  val mt = m2.transpose
  m1.zipWithIndex.map { case (v, i) => v zip mt(i) map Function.tupled(_*_) reduceLeft(_+_)}
}
```

### CPU/ Mem Usage

![](/img/result/graph/scala_matrix_cpu_linux.png)
![](/img/result/graph/scala_matrix_mem_linux.png)

### Flame graph

<embed type="image/svg+xml" src="/img/result/flame/kernel_scala-matrix.svg" />


---

## <i class="icon-rust"></i> Rust

```
fn mat(sz: usize, f :fn(usize, usize) -> i32) -> Vec<Vec<i32>> {
    let mut ret: Vec<Vec<i32>> = Vec::with_capacity(sz);
    let rs = Range{start:0, end:sz};
    for i in rs {
        let xs = Range {start:1, end:sz + 1};
        let mut col: Vec<i32> = Vec::with_capacity(sz);
        for x in xs {
            col.push(f(i+1, x))
        }
        ret.push(col)
    }
    ret
}

fn mul(left:Vec<Vec<i32>>, right:Vec<Vec<i32>>) -> Vec<Vec<i32>> {
    let mut ret = Vec::with_capacity(left.len());
    for i in 0..left.len() {
        let mut data = Vec::with_capacity(right.len());
        for n in 0..right.len() {
            let mut val :i32 = 0;
            for m in 0..right.len() {
                val += left[i][m] * right[m][n];
            }
            data.push(val);
        }
        ret.push(data);
    }
    ret
}

fn matrix(start :u32, end :u32) -> i32 {
    let (tx, rx) = mpsc::channel();

    for n in start..end+1 {
        let tx = tx.clone();
        thread::spawn(move || {
            let row = |r:usize,_:usize| -> i32{ r as i32 };
            let col = |_:usize,c:usize| -> i32{ c as i32 };

            let size = n as usize;

            let lf = mat(size, row);
            let rg = mat(size, col);
            let ans = mul(lf, rg);
            tx.send(ans.len() == size)
        });
    }

    let mut count = 0;
    for _ in start..end+1 {
        let rs = rx.recv();
        match rs {
            Ok(_) => count += 1,
            Err(e) => println!("{}", e),
        }
    }

    if count == end-start+1 {
        return 0;
    }
    return 1;
}

```

### CPU/ Mem Usage

![](/img/result/graph/rust_matrix_cpu_linux.png)
![](/img/result/graph/rust_matrix_mem_linux.png)

### Flame graph

<embed type="image/svg+xml" src="/img/result/flame/kernel_rust-matrix.svg" />


---

## <i class="icon-go"></i> Golang


```
func mul(l, r [][]int) [][]int {
        sz := len(l)
        ans := make([][]int, sz)
        for i := 0; i < sz; i++ {
                row := make([]int, sz)
                for n := 0; n < sz; n++ {
                        for m := 0; m < sz; m++ {
                                row[n] += l[i][m] * r[m][n]
                        }
                }
                ans[i] = row
        }
        return ans
}

func left(sz int) [][]int {
        ret := make([][]int, sz)
        for i := 1; i < sz+1; i++ {
                row := make([]int, sz)
                for n := 1; n < sz+1; n++ {
                        row[n-1] = i
                }
                ret[i-1] = row
        }
        return ret
}

func right(sz int) [][]int {
        ret := make([][]int, sz)
        for i := 1; i < sz+1; i++ {
                row := make([]int, sz)
                for n := 1; n < sz+1; n++ {
                        row[n-1] = n
                }
                ret[i-1] = row
        }
        return ret
}

func calc(done <-chan struct{}, start, end int) []Answer {
        ch := make(chan Answer)
        var wg sync.WaitGroup
        as := make([]Answer, 0)

        go func() {
                defer close(ch)
                for i := start; i <= end; i++ {
                        wg.Add(1)
                        go func(n int) {
                                v := mul(left(n), right(n))
                                ans := Answer{n, len(v), len(v[0])}
                                select {
                                case ch <- ans:
                                case <-done:
                                }
                                wg.Done()
                        }(i)
                }
                wg.Wait()
        }()

        // main thread
        for a := range ch {
                //println(fmt.Sprintf("wait >%v", a))
                as = append(as, a)
        }

        return as
}
```


### CPU/ Mem Usage

![](/img/result/graph/go_matrix_cpu_linux.png)
![](/img/result/graph/go_matrix_mem_linux.png)

### Flame graph

<embed type="image/svg+xml" src="/img/result/flame/kernel_go-matrix.svg" />



---

## Result Table


|              Lang              | Lines   | libs   | Matrix | Runtime(sec) | CPU(%)   | Mem(mb)  | Point | Rank |
|:------------------------------:| ------- | ------ | ------ | ------------ | -------- | -------- | ----- | ---- |
| <i class="icon-cplusplus"></i> | 107 (5) | {{< svg fa-ban>}} (3)  | {{< svg fa-ban >}} (3)  | 11   (5)     | 323  (5) | 263  (2) | 23    | 6    |
|   <i class="icon-java"></i>    | 64 (3)  | {{< svg fa-angellist >}} (1) | {{< svg fa-circle >}} (2)  | 4.9   (3)    | 417 (3)  | 87  (1)  | 13    | 1    |
|  <i class="icon-python"></i>   | 36 (2)  | {{< svg fa-angellist >}} (1) | {{< svg fa-angellist >}} (1) | 11     (6)   | 180  (6) | 45   (6) | 22    | 5    |
|   <i class="icon-scala"></i>   | 20 (1)  | {{< svg fa-angellist >}} (1) | {{< svg fa-circle >}} (2)  | 1.36  (2)    | 260  (4) | 635  (5) | 15    | 3    |
|   <i class="icon-rust"></i>    | 87 (4)  | {{< svg fa-circle >}} (2) | {{< svg fa-circle >}}　(2)  | 1.20 (1)     | 731 (1)  | 518  (4) | 14    | 2    |
|    <i class="icon-go"></i>     | 89 (6) | {{< svg fa-circle >}} (2) | {{< svg fa-circle >}} (2)  | 6.4   (4)    | 425 (2)  | 480  (3) | 19    | 4    |

---

## Recap


・Pythonで並列処理しちゃダメ

・Cはチューニングしないとダメ

・Java/Rust/Scala あたりで書くと良い

・Golang は シンタックスシュガー が必要
