---
weight: 2
---
<!-- : .wrap -->

<!-- : .text-data -->How to


<!--: .text-intro -->Polyglot(自称)視点でどう見るのか？のお話

---
<!-- : .wrap .content-center -->

## 大枠として

<p class="text-intro">対象のものに対して、入力を与えて、対象の結果から判定します</p>

<p class="text-intro text-red">※ 結果には副次的な影響があるので正しいものになりません</p>

![sut](/img/sut.png)

## {{< svg "fa-arrow-down" >}}

パフォーマンス計測と一緒の枠組み

---
<!-- : .wrap  -->

## 青いところは、基本扱えない

<!--: .aligncenter -->![](/img/arch.png)

---
<!--: fullscreen .card-50 -->

{{< div class="flex-content" >}}
## 観点（主観）
<br/>

<p class="text-intro">定性的なもの
  <ul>
    <li>コードの書き易さ</li>
    <li>ステップ数</li>
  </ul>
</p>

※ 副次要因は「筆者自身」になります

<p class="text-intro">定量的なもの
  <ul>
    <li>実行時間</li>
    <li>CPU,メモリの使用量</li>
  </ul>
</p>

※ 副次要因は「実行環境」になります

{{< /div >}}

<figure><img src="https://source.unsplash.com/26MJGnCM0Wc/" /></figure>


---
<!--: .wrap -->

## {{< svg "fa-balance-scale">}}定性的な観点の補足

<!--: .aligncenter -->![sut](/img/sut.png)

|||v

- **入力:** 各言語のソースコード
- **対象:** 筆者自身
- **結果:** ステップ数、書き易さ

|||

<table class="no-border">
  <tr>
    <th>結果</th>
    <th>指標</th>
  </tr>
  <tr>
    <td>ステップ数</td>
    <td>短いは正</td>
  </tr>
  <tr>
    <td>書き易さ</td>
    <td>易 {{< svg fa-angellist >}}  〜 {{< svg fa-circle >}}  〜 {{< svg fa-ban >}}難</td>
  </tr>
</table>

---
<!--: .wrap -->

## {{< svg "fa-desktop">}}定量的な観点の補足

<!--: .aligncenter -->![sut](/img/sut.png)

|||v

- **入力:** 実行引数、ファイル、HttpRequest
- **対象:** 各言語のプログラム
- **結果:** 実行時間、CPU/Memory使用量

|||

<table class="no-border">
  <tr>
    <th>結果</th>
    <th>指標</th>
  </tr>
  <tr>
    <td>ステップ数</td>
    <td>短いは正</td>
  </tr>
  <tr>
    <td>書き易さ</td>
    <td>易 {{< svg fa-angellist >}}  〜 {{< svg fa-circle >}}  〜 {{< svg fa-ban >}}難</td>
  </tr>
</table>

---
<!--: .wrap -->

## 手法 :: ワークロード分析


<!-- : .aligncenter -->![](/img/workload.png)

---
<!--: .wrap -->

## ReCap

<ul class="flexblock specs">
  <li>
    <div>
      <h2>{{< svg fa-check >}}
      known-known
      </h2>
      知っていること チェックしなければいけない指標を知っていて、指標の値も知っている
    </div>
  </li>
  <li>
    <div>
      <h2>{{< svg fa-check >}}Known-Unknown</h2>
      知らないことをわかっていること 指標をチェックできること知っていて、指標の値を知らない
    </div>
  </li>
  <li>
    <div>
      <h2>{{< svg fa-check >}} Unknown-Unknown</h2>
      知らないことを知らないこと 指標をチェックできるかもわからないし、値も知らない
    </div>
  </li>
</ul>



---
<!--: .wrap -->

## ReCap

|||

#### known-known

|||

#### known-unknown

|||

#### unknown-unknown
