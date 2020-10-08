---
title: "Practice"
date: 2020-10-03T14:36:27+09:00
weight: 30
---
<!-- : .wrap -->

## Practice システムあれこれ


---
## 2. システムあれこれ

### 2-1. Spliit monolish



---
<!-- : .wrap -->

## Migration Patterns

- Strangler Fig Application

https://martinfowler.com/bliki/StranglerFigApplication.html
https://paulhammant.com/2013/07/14/legacy-application-strangulation-case-studies/

![](https://paulhammant.com/images/strangulation.jpg)

* UI Composition
  * 割愛

- Branch By Abstraction
   1. リプレイスする機能的な抽象モジュールを作る
   2. クライアント側を抽象モジュールに切り替える
   3. 抽象モジュールを新しく作成する
   4. 新し方に切り替える
   5. 古いものを消す


![](https://martinfowler.com/bliki/images/branch-by-abstraction/step-1.png)
![](https://martinfowler.com/bliki/images/branch-by-abstraction/step-2.png)
![](https://martinfowler.com/bliki/images/branch-by-abstraction/step-3.png)
![](https://martinfowler.com/bliki/images/branch-by-abstraction/step-4.png)
![](https://martinfowler.com/bliki/images/branch-by-abstraction/step-5.png)


- Parallel Run

![](https://upload.wikimedia.org/wikipedia/commons/thumb/2/2a/Parallel_running.png/800px-Parallel_running.png)

- Decorating Collaborator
- Change Data Capture

[Change Data Streaming Patterns for Microservices With Debezium ](https://www.slideshare.net/ConfluentInc/change-data-streaming-patterns-for-microservices-with-debezium)

[](https://www.slideshare.net/ToruMakabe/zozotowncloud-native-journey)

---
<!-- : .wrap -->

### 2-2. Decomposing the Database

* Shared Database
* DB View
   * ![](img/db-view.png)
* DB wrapper service
   * ![](img/db-wrap-service.png)
* DB as Service Interface
* Synchronize Data in App
* Trace write
* Split table
* Move to FK key to Code
* Transaction
  * 2 phase commit
  * Sagas
