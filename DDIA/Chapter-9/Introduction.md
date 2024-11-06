- the best way of building fault-tolerant system is to find some general-purpose abstraction with useful guarantees. 
- For example a simple abstraction is transaction in database where it guarantees atomicity, isolation and durability. 
- For distributed system, one of the most important abstraction is consensus i.e getting all nodes to agree on something
- Consensus can be used in cases for example in single leader based replication, when a leader node fails all then follower need to agree on a new leader. 

## Consistency guarantee 
- in a distributed envrionment normally when we read the same value from 2 different database replica at the same time then we might get different results. This is because the write request may not be fulfilled in both nodes at the same time.
- Most distributed systems have eventual consistency as their guarantee which says that if we stop write request for nodes for a particular length of time then all the nodes will have the same data i.e nodes will converge to the same data.
- This is a weak guarantee because during the convergence time period we will receive stale data or nothing at all. 
- If we have strong guarantee on the consistency then we have weak performance but if we have weak guarantee then we can have better performance. 
- Distributed consistency model and Transaction isolation level are overlap in many ways but they do differ in the case where transaction islation level deals with managing race conditions when there dfferent transaction are running concurrently whereas distributed consistency deals with coordinating state of all replicas during faults or delays.

## Linearizability
- the idea behind linearizability -> giving the illusion that there is only a single replica, that every client have the same view of the data and have do not worry about replication lag.
- Linearizability is recency guarantee -> logical view is that there is only one copy of data and when we read that data we get the most up-to date value.
- concurrency in database -> when two or more operations are not related to each other or do not depend on the result of the previous or future operation.
- 