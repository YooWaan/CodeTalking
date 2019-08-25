# Compare Language


## Language

* python
* Java
* Scala
* Golang
* C++
* Rust
* (TODO) Haskell, erlang


## Requirements Tools

- jdk
- sbt
- cargo (rust)
- gcc or others
- make
- go
- python (and requirements.txt packages for graph.png)
- apache2-utils


## Performance Check List

### Matrix Calculation

N x N の行列積計算処理を start から end まで並列処理

```
for n in start ... end:
  thread matrix[n][n] x matrix[n][n]
```

### Read File

wcコマンドと同じような処理（厳密に実装していない）を作成して、
引数で指定したファイルを順次読み込んで、wc 処理を実行

```
files = [file1, file2, file3 ... ]
for n in 0 ... end :
   thread word_count file[n % files.length]
```

### IO Socket

POSTでテキストファイルを送信して、wc 処理を結果を返す
webapp に ab (apache becnh)を実行

```
httpd:
  "/" http_request > word_count > http_response
```

```
# client
$ ab -p word_count.txt http://.....
```

## Result

[Result Summary](docs/result.md)


## Misc

[Misc](docs/misc.md)
