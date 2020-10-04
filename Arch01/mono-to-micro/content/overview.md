---
title: "Overview"
date: 2020-10-03T14:43:17+09:00
weight: 10
---

<!-- : wrap -->

## 0-1. MicroService とは

> Microservices are independently deployable services  modeled around a business domain.

ビジネスドメインをモデル化した、独立してデプロイできるもの

- Independent Deployability
- Modeled around a Business Domain


<hr/>

### from Principles, Practices and Culture (以下PPC)

🚧 TODO WRITE

- Microservices are ideal for *big systems*
   - ある程度規模が出てきたものを扱うもの
- Microservices architecture is *gool-oriented*
   - 目的を解決するアプローチ
- Microservice are focused on replaceablity
   - 既存コンポーネントを維持ではなく、換えていくことに焦点を当ててます

<hr/>

### What Advantages Can Microservices Bring ?

独立性から得れるもの

- 堅牢性と規模の向上
- 技術要素の組み合わせ
- 依存関係の解決が必要となる開発が不要
- システム理解の容易性
- lang, deploy, style, platform の柔軟性が上がる

🚧 TODO WRITE

TODO 補足 別の本

---

## 0-1. Monolith とは

>  ... referring to a unit of deployment. When all functionality in a system had to be deployed together, we consider via monolith. 

- Single process monolith
- Distributed monolith


### Advantages of Monoliths

TODO


### from PPC

🚧 TODO WRITE

*Tech*

- Lessens dependencies between teams, resulting in faster code to production
   - 依存を減らすことでリリースサイクルを向上
- Allows lots of initiatives to run in parallel
   - パラレルに主体的に動きを許容します
- Supports multiple tech/lang/framworks
   - エンジニアの行動範囲が広がります
- Enable gracefull degraduation of service
   - 劣化の速度を下げます
- Promote ease of innovation through disposable code - it is easy to fail and move on
   - コードを捨て易くなるので、失敗に対してのリカバリが容易になります

---

*Biz*


![](https://www.oreilly.com/content/wp-content/uploads/sites/2/2020/01/msar_0201-a762ef3efa52bf559517ac80e291c64a.png) 