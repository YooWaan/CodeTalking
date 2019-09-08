---
weight: 8
---


<!-- : .text-data -->File Read


<!-- : .text-intro -->Word Count  :: Report



---
<!--: wrap -->

### 処理内容

<!--: content-left -->英字のテキストファイルを指定Byteで分割してマルチスレッド処理を行って単語数、行数などをカウントします

単純に *WC* コマンドと同じ処理をしています


---

## 定性的な観点

|||

<ul class="flexblock specs">
  <li>
    <div>
      <h2>{{< svg fa-check >}}
      文字列の扱い易さ
      </h2>
      標準ライブラリのありなし  易 🦸 〜 😀 〜 🤔 難
    </div>
  </li>
  <li>
    <div>
      <h2>{{< svg fa-times >}}ファイル読み込みとマルチスレッド処理管理</h2>
      dddd
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

![](/img/result/wc_cpu_linux.png)

|||


![](/img/result/wc_mem_linux.png)

---

## <i class="icon-cplusplus"></i>

```c++
Count char_count(char* buffer) {
    Count c = {0, 0, 0};
    std::unique_ptr<char[]> ss(buffer);
    bool inword = false;
    for (int i =0, len = std::strlen(buffer); i < len ;i++) {
        c.bytes++;
        if (buffer[i] == ' ') {
            if (inword) {
                inword = false;
                c.words++;
            }
        } else if (buffer[i] == '\n') {
            c.lines++;
        } else {
            inword = true;
        }
    }
    return c;
}

do {
    auto ptr = buffer.get();
    fin.read(ptr, bufsize);
    if (fin.bad()) {
        std::cerr << "cant read file " << filename << std::endl;
        return ERR;
    }

    // copy
    auto rsz = fin.gcount();
    auto buf = new char[rsz+1];
    std::memcpy(buf, ptr, rsz);
    buf[rsz] = '\0';

    // count
    //std::cout << "buf:" << buf << ", " << ptr << std::endl;
    auto ft = std::async(std::launch::async, char_count, buf);
    futures.push_back(std::move(ft));

} while(!fin.eof());


Count cnt = {0, 0, 0};
for (auto& ft : futures) {
    try {
        Count c = ft.get();
        cnt.bytes += c.bytes;
        cnt.words += c.words;
        cnt.lines += c.lines;
    } catch (std::future_error& e) {
        std::cout << e.what() << std::endl;
    }
}
```

### CPU/ Mem Usage

![](/img/result/graph/cpp_wc_cpu_linux.png)
![](/img/result/graph/cpp_wc_mem_linux.png)

### Flame graph

![](/img/result/flame/kernel_cpp-wc.svg)

---

## <i class="icon-java"></i> Java


```Java
int[] part(String s) {
    final int[] ret = new int[]{0, 0, 0};
    s.chars().forEach(i -> {
            char ch = s.charAt(i);
            ret[0] += 1;
            ret[1] += wd(ch, ' ', '\n');
            ret[2] += eq(ch, '\n');
        });
    return ret;
}

public void count(String filename) throws IOException, InterruptedException {
    int alocSize = 4048;
    Path path = Paths.get(filename);
    CharBuffer buf = CharBuffer.allocate(alocSize);
    ExecutorService exec = Executors.newFixedThreadPool(16);
    List<Future<int[]>> results = new ArrayList();

    try (BufferedReader rd = Files.newBufferedReader(path)) {
        int size = 0;
        do {
            buf.clear();
            size = rd.read(buf);
            char[] cs = buf.array();
            String s = new String(Arrays.copyOf(cs, cs.length));
            //System.err.println(s);
            Future<int[]> future = exec.submit(() -> {
                return part(s);
            });
            results.add(future);
        } while (size == alocSize);
    } finally {
        exec.shutdown();
    }

    int[] result = sum(results.stream().map(this::futureGet));
    System.err.println(String.format("%d\t%d\t%d", result[0], result[1], result[2]));
}
```

### CPU/ Mem Usage

![](/img/result/graph/java_wc_cpu_linux.png)
![](/img/result/graph/java_wc_mem_linux.png)

### Flame graph

![](/img/result/flame/kernel_java-wc.svg)


---

## <i class="icon-python"></i> Python

```
def wd(ss):
    is_word = True
    ch_cnt = len(ss)
    wd_cnt = 0
    lf_cnt = 0
    for i, c in enumerate(ss):
        if c == ' ':
            is_word = True
        elif c == '\n' or c == '\r':
            lf_cnt += 1
        else:
            if is_word:
                wd_cnt += 1
                is_word = False

    return ch_cnt, wd_cnt, lf_cnt

def count(fp):
    with ThreadPoolExecutor(max_workers=16) as e:
        futures = []
        size = 4096
        i = 0
        with open(fp, 'rb') as fin:
            while i != -1:
                by = fin.read(size)
                futures.append(e.submit(wd, by.decode('utf-8')))
                if len(by) == size:
                    fin.seek(size * i)
                    i += 1
                else:
                    i = -1

        result = wait(futures)
        return reduce(lambda x,y: (x[0]+y[0], x[1]+y[1], x[2]+y[2]), [rs.result() for rs in result.done])

```

### CPU/ Mem Usage

![](/img/result/graph/py_wc_cpu_linux.png)
![](/img/result/graph/py_wc_mem_linux.png)

### Flame graph

...


---

## <i class="icon-scala"></i> Scala

```
def countup(ss: String): (Int, Int, Int) /* ch, word, line */ = {
  def eqC(c: Char, e: Char): Int = {
    return if (c == e) 1 else 0
  }
  def wdC(c: Char, e1: Char, e2: Char): Int = {
    if (c == e1) {
      return 1
    }
    return eqC(c, e2)
  }
  def rd(x: (Int, Int, Int), y: (Int, Int, Int)): (Int, Int, Int) = {
    return (x._1 + y._1, x._2 + y._2, x._3 + y._3)
  }
  def chP(c: Char): Int = {
    //println(">" + c)
    return 1
  }
  return ss
    .map(c => (chP(c), wdC(c, ' ', '\n'), eqC(c, '\n')))
    .reduce(rd)
}

def count(filename: String): (Int,Int,Int) = {
  val alocSize = 4048
  val path = Paths.get(filename)
  val buffer = ByteBuffer.allocate(alocSize)
  var futures: List[Future[(Int,Int,Int)]] = List()
  //val es =ExecutionContext.fromExecutorService(Executors.newCachedThreadPool())
  val es =ExecutionContext.fromExecutorService(Executors.newFixedThreadPool(12))

  try {
    tryResource(Files.newByteChannel(path, StandardOpenOption.READ))(_.close()) { rc =>
      var size = 0
      do {
        size = rc.read(buffer)
        val s = new String(Arrays.copyOf(buffer.array(), size), Charset.forName("utf-8"))
        buffer.clear()
        val c = new Callable[(Int,Int,Int)]() {
          def call(): (Int,Int,Int) = {
            return countup(s)
          }
        }
        futures =  es.submit(c) :: futures
      } while(size == alocSize)
    }
  } finally {
    es.shutdown()
  }

  futures.map(_.get()).reduce((a,b) => (a._1 + b._1, a._2 + b._1, a._3 + b._3))
}
```

### CPU/ Mem Usage

![](/img/result/graph/scala_wc_cpu_linux.png)
![](/img/result/graph/scala_wc_mem_linux.png)

### Flame graph

![](/img/result/flame/kernel_scala-wc.svg)


---

## <i class="icon-rust"></i> Rust

```
fn countup(i:i64, b: &[u8]) -> (i32, i32, i32, bool) {
    let s = std::str::from_utf8(b).unwrap();
    //println!("[{}]{}",i, s);
    let cs = s.chars();
    return cs.fold((b.len() as i32, 0,0, false), |t, ch| {
        match (ch, t.3) {
            ('\n', _) => (t.0, t.1, t.2+1, false),
            (' ', true) => (t.0, t.1+1, t.2, false),
            (' ', false) => (t.0, t.1, t.2, t.3),
            _ => (t.0, t.1, t.2, true),
        }
    });
}

fn word_count(file: &String) -> i32  {
    let mut f = File::open(file).unwrap();

    let size: i64 = 2048;
    let mut done = false;
    let mut i: i64 = 0;
    let (tx, rx) = mpsc::channel();

    while !done {
        //let mut buffer: [u8; 30] = [0; 30];
        let mut buffer : Box<[u8]> = Box::new([0; 2048]);
        let rr = f.read(&mut buffer[..]);
        let sz: usize = match rr {
            Result::Ok(sz) => sz,
            Result::Err(_) => panic!("failed read file"),
        };
        let tx = tx.clone();
        // Start Thread
        thread::spawn(move || {                  // move ownership
            tx.send(countup(i, &buffer[..sz]));
        });
        i += 1;
        done = sz != size as usize;
    }

    let mut data: Vec<(i32,i32,i32,bool)> = Vec::with_capacity(i as usize);
    for _ in 0..i {
        match rx.recv() {
            Ok(wc) => data.push(wc),
            Err(_) => panic!("failed recv data"),
        }
    }

    let cnt = data.iter().fold((0,0,0), |total,x| (total.0 + x.0, total.1 + x.1, total.2 + x.2));
    eprintln!("{:?}", cnt);
    return 0;
}
```

### CPU/ Mem Usage

![](/img/result/graph/rust_wc_cpu_linux.png)
![](/img/result/graph/rust_wc_mem_linux.png)

### Flame graph

![](/img/result/flame/kernel_rust-wc.svg)


---

## <i class="icon-go"></i> Golang

```
func CountUp(page uint64, data []byte) Part {
        ds := len(data)
        part := Part{Page: page, Count: Count{Bytes: uint64(ds)}}

        r, size := utf8.DecodeRune(data[0:])
        part.First = isSp(r)
        part.WordCount(part.First)

        for i := size; i < ds; {
                r, size := utf8.DecodeRune(data[i:])
                part.WordCount(isSp(r))

                if r == '\n' {
                        part.UpLine()
                }

                i += size
        }
        return part
}

func RunParallel(filename string) (FileCount, error) {
        done := make(chan struct{})
        defer close(done)

        count := FileCount{FileName: filename}
        if parts, err := Parallel(done, filename); err != nil {
                fmt.Errorf("%s : [%v]\n", filename, err)
                return count, err
        } else {
                for _, p := range parts {
                        count.Add(p.Count)
                }
        }
        return count, nil
}


func Parallel(done <-chan struct{}, filename string) ([]Part, error) {
  fp, err := os.Open(filename)
  if err != nil {
          return nil, err
  }
  ch := make(chan Part)
  defer func() {
          fp.Close()
  }()

  var wg sync.WaitGroup
  reader := bufio.NewReader(fp)
  page := uint64(0)
  parts := make([]Part, 0)

  for {
          buf := make([]byte, readSize)
          n, err := reader.Read(buf)
          if n == 0 {
                  break
          }

          wg.Add(1)
          go func(pcnt uint64, buf []byte) {
                  defer wg.Done()
                  part := CountUp(pcnt, buf)
                  select {
                  case ch <- part:
                  case <-done:
                  }
          }(page, buf[:n])
          page += 1

          if err == io.EOF {
                  break
          }
          if err != nil {
                  return nil, err
          }

        }


        go func() {
                wg.Wait()
                close(ch)
        }()

        for p := range ch {
                parts = append(parts, p)
        }

        return parts, nil
}

```

### CPU/ Mem Usage

![](/img/result/graph/go_matrix_cpu_linux.png)
![](/img/result/graph/go_matrix_mem_linux.png)

### Flame graph

<embed type="image/svg+xml" src="/img/result/flame/kernel_go-matrix.svg" />


---

## Result Table


|              Lang              | Lines   | String                    | Task管理                  | Runtime(sec) | CPU(%)   | Mem(mb)  | Point | Rank |
|:------------------------------:| ------- | ------------------------- | ------------------------- | ------------ | -------- | -------- | ----- | ---- |
| <i class="icon-cplusplus"></i> | 91 (4)  | {{< svg fa-ban >}} (3)    | {{< svg fa-circle >}} (2) | 7   (4)      | 139  (4) | 34  (2)  | 19    | 4    |
|   <i class="icon-java"></i>    | 64 (2)  | {{< svg fa-circle >}} (2) | {{< svg fa-circle >}}(2)  | 2.7   (2)    | 175 (3)  | 675  (4) | 15    | 1    |
|  <i class="icon-python"></i>   | 42 (1)  | {{< svg fa-circle >}} (2) | {{< svg fa-circle >}} (2) | 12     (6)   | 164  (6) | 22   (6) | 23    | 6    |
|   <i class="icon-scala"></i>   | 97 (5)  | {{< svg fa-circle >}} (2) | {{< svg fa-circle >}} (2) | 3.4  (3)     | 317  (1) | 970  (5) | 18    | 3    |
|   <i class="icon-rust"></i>    | 78 (3)  | {{< svg fa-circle >}} (2) | {{< svg fa-circle >}} (2) | 11 (5)       | 115 (5)  | 143  (3) | 20    | 5    |
|    <i class="icon-go"></i>     | 155 (6) | {{< svg fa-circle >}} (2) | {{< svg fa-ban >}} (3)    | 2.3   (1)    | 241 (2)  | 17  (1)  | 15    | 1    |



---

## Recap

- jvm 勢（Java, Scala）はいい感じ
- Rust,C はあんまりな感じ
- 書き心地は言語で差分ない感じ
