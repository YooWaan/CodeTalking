%title: GraphQL Live
%author: YooWaan
%date: 2020-12-14


-> # Title <-

-> # GraphQL どうでしょう

-> Schema first にどこまで迫れるか 会

memo https://www.npmjs.com/package/@nuxtjs/markdownit

----------------------------------------
-> # Index <-
=============


1. What is GraphQL
   * Eco System
2. 📡 Rest vs 🔮 GraphQL (casual)
3. Demo (semi)
4. Tips
5. Recap


----------------------------------------
-> # 1.What is GraphQL <-

* Language
   * API code
   * Client code
* Eco System


```
  [Client] --- [API] ---  [Data]
            A
             `-- ここの言語
```


see [graphql.org](https://graphql.org/)
    [faq](https://graphql.org/faq/)
    [Tutorial](https://www.howtographql.com/)

----------------------------------------
-> # Intro <-

[Intoroduction](https://reactjs.org/blog/2015/05/01/graphql-introduction.html)

design principles:

* Hierarchical
* Product-centric            ... frontend driven
* Client-sepcified queries   ... Client うれしい
* Backwords Compatible       ... 下位互換しやすいらしい
* Structured, Arbitrary Code ... 構造化できつつ、いろいろできる
* Application-Layer Protocol
* Strongly-typed             ... 型好きやん
* Introspective

----------------------------------------
-> # Eco System <-

[graphiql](https://github.com/graphql/graphiql)


```
    ,--------.
   | GraphQL  |                        ,------.
.->| Language |<-.                  ,-| VSCode |
|  | Type     |   |   ,--------.    |  `------'
|   `--------'    |  | GraphQL  |   |
|                 |  | Language |<--|  ,--------.
|   ,--------.   .|--| Service  |   | | GraphQL  |
|  | GraphQL  |<-'|  | Server   |   '-| Language |
|->| Language |   |   `--------'      | Service  |
|  |  Parser  |<-.|..                  `--------'
|   `--------'    |  |
|                 |  |   ,----------.   ,---[GraphiQL]
|    ,--------.   |  |  | Codemirror |<-.--[Alair]
|   | GraphQL  |<-'  |--| GraphQL    |  `-[Playground]
`.->| Language |     |   `----------'
/   | Interface|<----'
|    `--------'
|    ,--------.
|   | GraphQL  |
 '->| Language |
    | Utils    |
     `--------'
```


----------------------------------------

-> # 2. Rest vs GraphQL (casual)

----------------------------------------
-> # UI & API Server Building Steps <-


[1]. Define Payload (Resource schema)

[2]. Design endpoint

[3]. Build UI & API

  [3-1]. (API) Build API Server (or mock)

  [3-2]. (UI) API Communication code
         (UI) JSON Binding code
         (UI) Apply UI component


----------------------------------------
-> # 📡 Rest Flow <-

(1) use tool eg. swagger
  [1]. Define Payload (Resource)
  [2]. Design endpoint

(2) Write application code
  [3]. Build UI & API

(3) use tool eg. swagger
  [3-1]. (API) Build API Server (or mock)
    ▶️  routing each endpoint

  [3-2]. (UI) API Communication code
         ▶️  write each endpoing commucation code
       (UI) JSON Binding code
         ▶️  use defined class or plain json
       (UI) Apply UI component
         ▶️  use js framework

----------------------------------------
-> # 🔮 Graph QL Flow <-

(1) Write GraphQL Schema
  [1]. Define Payload (Resource)
  [2]. Design endpoint

(2) Write application code
  [3]. Build UI & API

(3) use tool eg. swagger
  [3-1]. (API) Build API Server (or mock)
    ▶️  implement query and mutation

  [3-2]. (UI) API Communication code
         (UI) JSON Binding code
          ▶️  generate by GraphQL Schema
         (UI) Apply UI component
          ▶️  use js framework

----------------------------------------
-> # Compare <-

[code first vs schema first](https://blog.logrocket.com/code-first-vs-schema-first-development-graphql/)
[GraphQL Code-First and SDL-First, the Current Landscape in Mid-2019](https://dev.to/novvum/graphql-code-first-and-sdl-first-the-current-landscape-in-mid-2019-547h)


個人の見解

| Item        | GraphQL      | Rest               |
| ----------- | ------------ | ------------------ |
| Schema      | GraphQL      | OpenAPI(swagger)   |
| API mock    | GraphQL tool | swagger or another |
| Client Data | GraphQL tool | ???                |
| Easy?       | same Rest    | same GraphQL       |

----------------------------------------
-> # 3. Demo

----------------------------------------
-> # Make GraphQL API #1 <-

setup

* langs
  * golang (backend)
  * node   (frontend)
* libs
  * nuxt.js (js)
  * gqlgen  (golang)

----------------------------------------
-> # Make GraphQL API #2 <-

いろいろ作り込まれちゃってます（サーセン）

```
├── public   ... application distribution(嘘 WIP)
├── app      ... application code
├── ql       ... graphql & generated code
└── spa      ... single page application
    ├── layouts
    ├── plugins   ... apollo
    └── pages     ... index.vue
```

----------------------------------------
-> # Server Steps <-

1. define graphql
2. generate code


```
less gqlgen.yml
github.com/99designs/gqlgen gen
playground http://localhost:8080/playground
DL SDL -> vscode
```


----------------------------------------
-> # UI <-

1. write codegen.yml
2. genrate code
3. edit vue

```
npm run codegen
```

----------------------------------------
-> # 3. Tips


----------------------------------------
-> # つらみ <-

Multiple Request
- Error Handle
- Transaction
- DataLoader (N+1 Problem)

Computed
- Infra Scaleout

No Specification
- File Upload  ... base64 and decode


https://note.com/konpyu/n/nc4fd122644a1

----------------------------------------

- それぞれで、エラーとTransaction の単位どうするの？がある
- N+1 がついてまわるので、query の設計を気をつける必要がある

```
 UserAgent -- query/mutation[] -+---> query/mutation #1
  Request                       |
                                |---> query/mutation #2
                                |
                                |---> query/mutation #3
                                |
                                `---> query/mutation #4
```

※ query と mutation の混在は仕様でNGになってます

----------------------------------------
-> # 4. Recap

- サーバーサイドは Rest も GraphQL もあんまり変わらない
  - GraphQL の方がクセがある感じ
- フロントエンドは ちょっと便利感がある
  - 型も守られているよ
