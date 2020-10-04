@startuml
skinparam roundcorner 25
skinparam componentStyle roundcorner 0

database "Pricing Database" as db
rectangle "Our Pricing Sytem" as srv

[Eternal #1] as e1
[Eternal #2] as e2
[Eternal #3] as e3
[Eternal #4] as e4

srv -up->> db

e1 -down-> db
e2 -down-> db
e3 -down-> db
e4 -down-> db

@enduml