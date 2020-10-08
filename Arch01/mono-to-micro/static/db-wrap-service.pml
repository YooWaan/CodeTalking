@startuml
skinparam roundcorner 25
skinparam componentStyle roundcorner 0

database "Entities Database" as db
rectangle "Entities Service" as srv

[App #1] as e1
[App #2] as e2
[App #3] as e3

srv -left-> db

e1 -down-> srv
e2 -down-> srv
e3 -down-> srv

@enduml
