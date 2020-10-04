---
title: "Practice"
date: 2020-10-03T14:36:27+09:00
weight: 30
---

## Practice


---
## 2. システムあれこれ 

### 2-1. Spliit monolish



---
## Migration Patterns

- Strangler Fig Application

https://martinfowler.com/bliki/StranglerFigApplication.html
https://paulhammant.com/2013/07/14/legacy-application-strangulation-case-studies/

![](https://paulhammant.com/images/strangulation.jpg)

- UI Composition
- Branch By Abstraction

1. リプレイスする機能的な抽象モジュールを作る
2. クライアント側を抽象モジュールに切り替える
3. 抽象モジュールを新しく作成する
4. 新し方に切り替える
5. 古いものを消す

- Parallel Run
- Decoolaborator
- Change Data Capture

---
### 2-2. Decomposing the Database

- Shared Database
- DB View
- DB wrapper service
- DB as Service Interface
- Synchronize Data in App
- Trace write
- Split table
- Move to FK key to Code

