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

<!--: content-left -->NxN の行列のA,Bの積計算　A・B＝C を N を大きくしていく処理をマルチスレッドで実行


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
