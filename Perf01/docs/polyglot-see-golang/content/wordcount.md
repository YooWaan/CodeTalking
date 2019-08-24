---
weight: 8
---

<!-- : .text-data -->File Read


<!-- : .text-intro -->Word Count



---
<!--: wrap -->

### 処理内容

<!--: content-left -->NxN の行列のA,Bの積計算　A・B＝C を N を大きくしていく処理をマルチスレッドで実行


---

## 定性的な観点


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

---

## Result

|||

![](/img/result/wc_cpu_linux.png)

|||


![](/img/result/wc_mem_linux.png)

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
