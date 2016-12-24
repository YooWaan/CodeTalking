Chap 03
===========


## Overview

1. Lamba,Closure
2. Higher-order function
3. Composite function
4. Monoid
5. Monad

## Languages

- Haskell 1,
  - runGhc
- CLang(C++) 1,
- Python  1,2
- GoLang  1,2
- Scala-Java  1,


## 1.ラムダ式, 無名関数, クロージャ

### ラムダ式 ([参考](https://ja.wikipedia.org/wiki/%E3%83%A9%E3%83%A0%E3%83%80%E8%A8%88%E7%AE%97#.E5.AE.9A.E7.BE.A9))

定義は下記の通りです。

 1. < expr> ::= < identifier>
 2. < expr> ::= (λ < identifier> . < expr>)
 3. < expr> ::= ( < expr> < expr> )

1,2 は関数の定義、3は関数に引数を適用することをあわらしている。(2はラムダ抽象,3は関数適用という)

### 無名関数  [参考](https://ja.wikipedia.org/wiki/%E7%84%A1%E5%90%8D%E9%96%A2%E6%95%B0#.E7.84.A1.E5.90.8D.E9.96.A2.E6.95.B0.E3.81.AE.E7.89.B9.E5.BE.B4)

名前をつけずに定義した関数。近年主流なのはラムダ式

### クロージャ （[参考](https://ja.wikipedia.org/wiki/%E3%82%AF%E3%83%AD%E3%83%BC%E3%82%B8%E3%83%A3))

関数閉包はプログラミング言語における関数オブジェクトの一種。引数以外の変数を実行時の環境ではなく、自身が定義された環境（静的スコープ）において解決することを特徴とする。

### 使い道

- 関数の引数を同じだけど動きが異なるようにしたい
- ここでだけ必要で、他では使わない関数

## 2.高階関数

関数を引数としたり、戻り値とするもの。
厳密には第一級関数をサポートしている言語で定義するもの。


### 引数

* filter
* map
* fold

### カリー化

### 使い道
