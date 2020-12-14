%title: GraphQL Live
%author: YooWaan
%date: 2020-12-12


-> # Title <-

-> # GraphQL どうでしょう


----------------------------------------
-> # Index <-
=============


* What is GraphQL
   * Eco System
* a little Comparsion
* Live (semi)
* Tips
* Recap


----------------------------------------
-> # What is GraphQL <-

* Language
* API
* Eco System

see [graphql.org](https://graphql.org/)
    [faq](https://graphql.org/faq/)
    [Tutorial](https://www.howtographql.com/)

----------------------------------------
-> # Intro <-

[Intoroduction](https://reactjs.org/blog/2015/05/01/graphql-introduction.html)


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
-> # Compare <-

| Item  | GraphQL  | Rest   |
| ----- | -------- | ------ |
| Query | Flexible | Stable |



https://www.npmjs.com/package/@nuxtjs/markdownit


----------------------------------------
-> # UI & API Server Building Steps <-


[1]. Define Payload (Resource)

[2]. Design endpoint

[3]. Build UI & API

  [3-1]. (API) Build API Server (or mock)

  [3-2]. (UI) API Communication code
         (UI) JSON Binding code
         (UI) Apply UI component


----------------------------------------
-> # Rest Flow <-

(1) use tool eg. swagger
  [1]. Define Payload (Resource)
  [2]. Design endpoint

(2) Write application code
  [3]. Build UI & API

(3) use tool eg. swagger
  [3-1]. (API) Build API Server (or mock)
    → routing each endpoint

  [3-2]. (UI) API Communication code
         → write each endpoing commucation code
       (UI) JSON Binding code
         → use defined class or plain json
       (UI) Apply UI component
         ➡️ use js framework

----------------------------------------
-> # Graph QL Flow <-

(1) Write GraphQL Schema
  [1]. Define Payload (Resource)
  [2]. Design endpoint

(2) Write application code
  [3]. Build UI & API

(3) use tool eg. swagger
  [3-1]. (API) Build API Server (or mock)
    → implement query and mutation

  [3-2]. (UI) API Communication code
         (UI) JSON Binding code
          → generate by GraphQL Schema
         (UI) Apply UI component
           ➡️ use js framework


[code first vs schema first](https://blog.logrocket.com/code-first-vs-schema-first-development-graphql/)
[GraphQL Code-First and SDL-First, the Current Landscape in Mid-2019](https://dev.to/novvum/graphql-code-first-and-sdl-first-the-current-landscape-in-mid-2019-547h)

----------------------------------------
-> # Make GraphQL API #1 <-

setup

* langs
  * golang
  * node
* libs
  * nuxt.js (js)
  * gqlgen  (golang)

----------------------------------------
-> # Make GraphQL API #2 <-


```
├── public   ... application distribution
├── app      ... application code
├── ql       ... graphql & generated code
└── spa      ... single page application
    ├── components
    ├── layouts
    ├── middleware
    ├── plugins
    └── pages
```



----------------------------------------
-> # Server <-




----------------------------------------
-> # UI <-



----------------------------------------
-> # つらみ <-

- Error Handle
- Transaction
- DataLoader (N+1 Problem)
- Infra Scaleout
- File Upload


https://note.com/konpyu/n/nc4fd122644a1
