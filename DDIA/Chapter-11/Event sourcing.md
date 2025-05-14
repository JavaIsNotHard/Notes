- involves storing all changes to the application state as a log of change events 

the idea behind both event sourcing and change data capture are the same, the idea is that we are capturing changes to the state of something, the difference between the two is the something, in event sourcing it would be the application state whereas in  CDC it would be changes to the database rather than the application state
the biggest difference between the two are as follows:
CDC:
1. CDC allows the database to be mutable i.e we can change the internal state of the database through various SQL statements 
2. the log of changes are extracted at a low level i.e replication log and parsed

Event sourcing:
1. application logic is built on the basis of events that are written to the event log
2. the event log are append-only and updates or deletes are prohibited 


[[deriving current state from event log]]

[[Commands and events]]