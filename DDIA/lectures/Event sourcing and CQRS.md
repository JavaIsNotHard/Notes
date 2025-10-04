how does event sourcing and CQRS relate with one other?

CQRS differentiates commands from queries which means that the system that perform updates are different from the system that performs reads

we can have the command side produce events similar to that of event sourcing and let the query side to subscribe to the event log to keep its internal state up to date with the current state in the command system 

the update events can be store in different schemas in the read system. for example since the events are not tied to any database schema we can use the event to project a new caching server, database server, elastic search search and more, basically using events allow us have different schemas 


can only guarantee eventual consistency and not strong consistency because different read system can read the event log at different times due to network issues

advantages of event sourcing includes:
1. audit trail -> event are represented as audits in financial statements
2. debugging
3.  historic state -> we can get historic data 