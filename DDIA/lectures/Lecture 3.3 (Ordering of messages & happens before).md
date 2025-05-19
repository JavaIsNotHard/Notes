ordering of messages or events meant the sequence in which the events are observed and processed across a single machine or distributed machines

Ordering of messages is important to make sure that the events are processed in the correct order in which they are received such that it maintains consistency between the operations that they perform

in a single machine model, all the messages in the single machine are processed in the same order that they were received, so if event a is called before event b then event a will be processed before event b

but this guarantee cannot be expected in distributed environment because of distributed system problems such as network delay, queuing, head of line blocking and many more problems which means even if physically a client A sends event A first before client B sends event B, it could be that the server processes client B's event B first before event A and this is allowed in distributed settings

now lets suppose that we have 3 servers A, B and C, server A sends event m1 to both B and C and server B sends event m2 to both A and C. it can happen that server C sees m2 before it sees m1 due to some network delay. how can we solve this problem?

we could attach physical timestamp with the event before sending the event to other clients but it also has the problem that even if two clocks are in sync with each other using NTP (network time protocol) it could be that timestamp of a later event is less than the timestamp of the its previous event.

Suppose in the same 3 server setup, lets say we attach timestamp t1 and t2 with events m1 and m2. it could be that t2 < t1 for various reasons such as clock drifts that happens that the NTP server cannot sync. this means the order a before b is still not maintained even though that is what happened physically between the server

to solve this problem we have the happens before relation

## Happens before relation

mathematical model of events that has happened in the system 
we need to first understand what are the events that can happen in the system:
- it could be a single node processing the execution stack 
- sending of the message is one event and receiving of the message is another event 

in such a system we say that event A happened before B iff:
- A and B occurred in the same node and A was executed before B in the local execution order. we are assuming this is a single threaded application that processes one event at a time and then moves to the next i.e there is a strict [[total order]] of the events that happen in the node. in a multithreaded architecture, we can assume each thread to be a single node (like a single server in a distributed environment)
- A is an event that some message M was sent and B is an event that this message M is received (assuming that messages are unique to prevent ambiguity)
- there exists an event C such that A -> C and C -> B then A -> B in what is called a [[partial order]]

