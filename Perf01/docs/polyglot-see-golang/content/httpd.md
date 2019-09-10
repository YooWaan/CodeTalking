---
weight: 9
baseurl: Site.BaseURL
---
<!--: wrap -->


<div class="text-data">Http</div>

<div class="text-context">apach bench  :: Report</div>


---
<!--: wrap -->

### 処理内容

<!--: content-left -->WordCount の HTTPサーバーに ab （apache bench）で負荷をかけてみるよ


---

## 定性的な観点


|||v

<ul class="flexblock specs">
  <li>
    <div>
      <h2>{{< svg fa-thumbs-up >}}
      Request,Response の扱いやすさ
      </h2>
    </div>
  </li>
  <li>
    <div>
      <h2>{{< svg fa-building >}}HttpServer</h2>
      構築の容易さ
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

![](/img/result/ht_cpu_linux.png)

|||


![](/img/result/ht_mem_all_linux.png)

---

## <i class="icon-cplusplus"></i>

* ThreadPool みたいなの作ったり
* Http の Request 解決したり、Response 返したり

```
Count word_count(int conn, int readLength, int contentLen) {
  Count c = {0, 0, 0};
  if (contentLen >0 && contentLen <= readLength) {
    return c;
  }
  int buf_size = contentLen == 0 ? 100 : 2048;
  std::unique_ptr<char[]> buffer(new char[buf_size]);
  auto buf = buffer.get();

  int n = recv(conn, buf, buf_size - 1, 0);
  if (n < 0) {
    Err("recv error");
    return c;
  }
  if (n == 0) {
    return c;
  }
  buf[std::min(n+1, buf_size-1)] = 0;

  if (contentLen > 0) {
    return Add(char_count(buf, n), word_count(conn, readLength+n, contentLen));
  }
  auto found = endOfHeader(buf, n-1);
  if (found == NULL) {
    //std::cout << buf << std::endl;
    auto bodyLength = contentLength(buf);
    //std::cout << "Not Found" << std::endl;
    return word_count(conn, readLength, bodyLength);
  }

  auto bodyLength = contentLength(buf);
  auto len = found - buf;
  return Add(char_count(found, len), word_count(conn, len, bodyLength));
}

int handle_client(int conn, Executor* exec) {
  Count cnt = word_count(conn, 0, 0);

  std::unique_ptr< std::ostringstream > wc(new std::ostringstream);
  auto result = wc.get();
  *result << cnt.bytes << '\t' << cnt.words << '\t' << cnt.lines << END;
  auto data = result->str().c_str();

  std::unique_ptr< std::ostringstream > oss(new std::ostringstream);
  auto out = oss.get();

  *out << "HTTP/1.1 200 OK" << END;
  *out << "Server: unkown" << END;
  *out << "Cache-Control: no-cache, no-store, must-revalidate" << END;
  *out << "Content-Length: " << strlen(data) << END;
  *out << "Connection: close" << END;
  *out << "Content-Type: text/plain" << END;
  *out << END;
  *out << data;
  auto response = out->str().c_str();

  int n = send(conn, response, strlen(response), 0);
  if (n < 0) {
    Err("send error");
  }

  //std::cout << response;

  exec->notify_done();

  close(conn);
  return OK;
}
```


### CPU/ Mem Usage

TODO

### Flame graph

<embed type="image/svg+xml" src="/img/result/flame/kernel_cpphttpd.svg" />

---

## <i class="icon-java"></i> Java

```java
public static void serve(HttpHandler handler) throws IOException {
    HttpServer server = HttpServer.create(new InetSocketAddress(5100), 0);
    server.createContext("/", handler);
    server.start();
}

}

class WordWebApp implements HttpHandler {

final int OK = 200;

public void handle(HttpExchange ex) throws IOException {
    try {
        Integer length = Integer.valueOf(ex.getRequestHeaders().getFirst("Content-Length"));
        if (length == 0) {
            length = Integer.valueOf(ex.getRequestHeaders().getFirst("Content-length"));
        }
        byte[] body = count(ex.getRequestBody(), length);

        ex.sendResponseHeaders(OK, body.length);
        ex.getResponseHeaders().set("Connection", "close");
        try (OutputStream out = ex.getResponseBody()) {
            out.write(body);
        }
    } catch (InterruptedException e) {
        byte[] body = "failed".getBytes();
        ex.sendResponseHeaders(OK, body.length);
        ex.getResponseBody().write(body);
    }
}

public byte[] count(InputStream in, int contentLength) throws IOException, InterruptedException {

    List<Future<int[]>> results = new ArrayList();
    ExecutorService exec = Executors.newCachedThreadPool();

    try {
        int offset = 0;
        int alocSize = 4048;
        int size = 0;
        byte[] buffer = new byte[alocSize];
        do {
            size = in.read(buffer);
            offset += size;
            //System.out.println(">>>>>>off" + offset + ", size=" + size + ", clen?:" + (offset<contentLength));
            String s = new String(buffer, 0, size);
            results.add(exec.submit(() -> {return part(s);}));
        } while (offset < contentLength);
    } finally {
        in.close();
        exec.shutdown();
    }

    return reduce(results.stream().map(this::futureGet));
}
```


### CPU/ Mem Usage

TODO

### Flame graph

<embed type="image/svg+xml" src="/img/result/flame/kernel_javahttpd.svg" />


---

## <i class="icon-python"></i> Python

```
def count(fp, content_length):
    with ThreadPoolExecutor(max_workers=16) as e:
        futures = []
        size = 4096
        read_size = 0
        while read_size < content_length:
            remain = content_length - read_size
            sz = size if remain > size else remain
            by = fp.read(sz)
            futures.append(e.submit(wd, by.decode('utf-8')))
            read_size = read_size + len(by)

        result = wait(futures)
        return reduce(lambda x,y: (x[0]+y[0], x[1]+y[1], x[2]+y[2]),
                      [rs.result() for rs in result.done])


class RequestHandler(BaseHTTPRequestHandler):

    def do_POST(s):
        s.send_response(200)
        s.send_header('Content-type', 'text/plain')
        s.end_headers()

        length = int(s.headers['Content-Length'])
        content = '{}'.format(count(s.rfile, length))
        s.wfile.write(content.encode())

if __name__ == '__main__':
    srv_cls = HTTPServer
    httpd = srv_cls((HOST_NAME, PORT_NUMBER), RequestHandler)
    try:
        httpd.serve_forever()
    except KeyboardInterrupt:
        pass

    httpd.server_close()

    print("Server Stops - %s:%s" % (HOST_NAME, PORT_NUMBER))
```

### CPU/ Mem Usage

TODO

### Flame graph

<embed type="image/svg+xml" src="/img/result/flame/kernel_pyhttpd.svg" />

---

## <i class="icon-scala"></i> Scala

```
class WordWebApp implements HttpHandler {

    final int OK = 200;

    public void handle(HttpExchange ex) throws IOException {
        try {
            Integer length = Integer.valueOf(ex.getRequestHeaders().getFirst("Content-Length"));
            if (length == 0) {
                length = Integer.valueOf(ex.getRequestHeaders().getFirst("Content-length"));
            }
            byte[] body = count(ex.getRequestBody(), length);

            ex.sendResponseHeaders(OK, body.length);
            ex.getResponseHeaders().set("Connection", "close");
            try (OutputStream out = ex.getResponseBody()) {
                out.write(body);
            }
        } catch (InterruptedException e) {
            byte[] body = "failed".getBytes();
            ex.sendResponseHeaders(OK, body.length);
            ex.getResponseBody().write(body);
        }
    }

    public byte[] count(InputStream in, int contentLength) throws IOException, InterruptedException {

        List<Future<int[]>> results = new ArrayList();
        ExecutorService exec = Executors.newCachedThreadPool();

        try {
            int offset = 0;
            int alocSize = 4048;
            int size = 0;
            byte[] buffer = new byte[alocSize];
            do {
                size = in.read(buffer);
                offset += size;
                //System.out.println(">>>>>>off" + offset + ", size=" + size + ", clen?:" + (offset<contentLength));
                String s = new String(buffer, 0, size);
                results.add(exec.submit(() -> {return part(s);}));
            } while (offset < contentLength);
        } finally {
            in.close();
            exec.shutdown();
        }


```

### CPU/ Mem Usage

TODO

### Flame graph

<embed type="image/svg+xml" src="/img/result/flame/kernel_scalahttpd.svg" />


---

## <i class="icon-rust"></i> Rust

* C++ と一緒な感じ
* 家の小さいノートPCだとリソース食いつぶす...

```
fn countup(b: &[u8]) -> (i32, i32, i32, bool) {
    let s = std::str::from_utf8(b).unwrap();
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

fn handle_client(mut stream: TcpStream) {
    let mut data: Vec<(i32,i32,i32,bool)> = Vec::new();
    {
        let size: i64 = 2048;
        let mut done = false;
        let mut i: i64 = 0;
        let (tx, rx) = mpsc::channel();

        while !done {
            //let mut buffer: [u8; 30] = [0; 30];
            let mut buffer : Box<[u8]> = Box::new([0; 2048]);
            let rr = stream.read(&mut buffer[..]);
            let sz: usize = match rr {
                Result::Ok(sz) => sz,
                Result::Err(_) => panic!("failed read file"),
            };
            let tx = tx.clone();
            thread::spawn(move || {
                tx.send(countup(&buffer[..sz]));
            });
            i += 1;
            done = sz != size as usize;
        }

        for _ in 0..i {
            match rx.recv() {
                Ok(wc) => data.push(wc),
                Err(_) => panic!("failed recv data"),
            }
        }
    }

    let cnt = data.iter().fold((0,0,0), |total,x| (total.0 + x.0, total.1 + x.1, total.2 + x.2));
    let content = format!("{}\t{}\t{}", cnt.0, cnt.1, cnt.2);
    let res = format!("HTTP/1.1 200 OK\r\nContent-Type: text/plan; charset=UTF-8\r\nContent-Length: {}\r\nConnection: close\r\n\r\n{}", content.len(), content);
    match stream.write(res.as_bytes()) {
        Ok(_) => {},
        Err(e) => println!("Failed sending response: {}", e),
    };
    stream.flush().unwrap();
}
```

### CPU/ Mem Usage

TODO

### Flame graph

<embed type="image/svg+xml" src="/img/result/flame/kernel_rusthttpd.svg" />


---

## <i class="icon-go"></i> Golang

```
func RunParallel(reader io.ReadCloser) (Part, error) {
        done := make(chan struct{})
        defer close(done)

        count := Part{}
        if parts, err := Parallel(done, reader); err != nil {
                return count, err
        } else {
                for _, p := range parts {
                        count.Add(p.Count)
                }
        }
        return count, nil
}

func WordCount(w http.ResponseWriter, r *http.Request) {
        count, err := RunParallel(r.Body)
        if err != nil {
                fmt.Fprintf(w, "failed")
                return
        }
        fmt.Fprintf(w, "%d\t%d\t%d\n", count.Bytes, count.Words, count.Lines)
}

func main() {
        http.HandleFunc("/", WordCount)
        http.ListenAnd
}
```

### CPU/ Mem Usage

TODO

### Flame graph

<embed type="image/svg+xml" src="/img/result/flame/kernel_gohttpd.svg" />




---

## Result Table

|              Lang              | Lines   | Req/Res                      | HttpServer                   | Runtime(sec) | CPU(%)   | Mem(mb)  | Point | Rank |
|:------------------------------:| ------- | ---------------------------- | ---------------------------- | ------------ | -------- | -------- | ----- | ---- |
| <i class="icon-cplusplus"></i> | 211 (6) | {{< svg fa-ban >}} (3)       | {{< svg fa-ban >}} (2)       | 3.2   (1)    | 196  (3) | 4  (1)   | 16    | 1    |
|   <i class="icon-java"></i>    | 102 (4) | {{< svg fa-circle >}} (2)    | {{< svg fa-ban >}}(3)        | 13.2   (4)   | 116 (5)  | 620  (4) | 22    | 5    |
|  <i class="icon-python"></i>   | 52 (1 ) | {{< svg fa-circle >}} (2)    | {{< svg fa-circle >}} (2)    | 9.8     (6)  | 87  (6)  | 23   (6) | 23    | 6    |
|   <i class="icon-scala"></i>   | 70 (2)  | {{< svg fa-circle >}} (2)    | {{< svg fa-ban >}} (3)       | 12.3  (3)    | 260  (1) | 949  (5) | 16    | 1    |
|   <i class="icon-rust"></i>    | 76 (3)  | {{< svg fa-ban >}} (2)       | {{< svg fa-circle >}} (2)    | 19.5 (5)     | 140 (4)  | 84  (3)  | 19    | 4    |
|    <i class="icon-go"></i>     | 119 (5) | {{< svg fa-angellist >}} (2) | {{< svg fa-angellist >}} (3) | 5.2   (2)    | 235 (2)  | 19  (2)  | 16    | 1    |


---

## Recap

* 各言語 Http のライブラリを導入した方がみんなハッピー(実装にツラミしかない)
* チューニングポイント多すぎて。。。。副作用多すぎ
