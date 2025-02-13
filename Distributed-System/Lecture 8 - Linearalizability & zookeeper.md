
# Consistency 

what does consistency mean?
the answer of what consistency means depends on the context that we are trying to answer 
- in ACID 
- read after write consistency 
	- in a distributed environment, if we make a change to a global value then next immediate read request should return the most up to date value

	

eventual consistency : as the same suggests, eventually there will be a point if we stoped accepting write request then all the nodes will return the same value for the same read request

eventual consistency is weak guarantee because it does not tell us when the nodes will converge towards the same value. by the time the value becomes consistent, there will be a lot of changes that can happen to the value

working with database is not like working with variables that run in a single thread. 

edge cases of eventual consistency only becomes apparent when there is a system failure or when there is high concurrency in the system 


# Linearizability

is a strong consistency model 
consistency in the face of concurrency
timing dependency not present in overlapping operations which means that we cannot for sure tell when two or more overlapping operations will take place within their time interval 

linearizability deals with the total ordering of operation happening in respect to real time i.e 

if we do not know the internal implementation of linearizable system then all we can do is check whether the system is linearizable or not but looking at the execution order of the request and making sure that it matches the real time order i.e the order in which the request arrived

checking for linearizability involves checking the history i.e the order in which operations take place 
we say that a system is linearizable if the invocation (start) and response (end) can be ordered or be traced in a sequential manner i.e there is an order of operation that actually yields the final outcome
![[Screenshot 2025-02-11 at 1.52.01 PM.png|600]]

Linearizability is a property and not an actual implementation

Implementing linearizable systems 
since linearizablility means that the client only sees a single copy of the data, why not make a system with only a single node?
this ensures linearizability but lacks fault-tolerance 
since we also need replication for fault-tolerance we need other methods which includes:
1. single-leader replication (potentially linearizable)
	- if you make reads from the leader and from synchronously updated followers then we can potentially obtain linearizability
	- but not all implementation of single-leader replication are linearizable either due to their design (because it uses snapshot isolation) or due to concurrency bugs (elaborate on this more) #elaborate-more 
	- there is also the problem of split brain, where more than one node acts as a leader which causes stale data between nodes and inconsistent responses between clients
2. consensus algorithms (linearizable)
	- they contain measures to prevent split brain and stale reads hence can be linearizable
3. leaderless replication (probably not linearizable)
	- dynamo-style replication where we rely on quorum for reads and writes 
	- this method is not linearizable because of the network delay between replication request among the replicated nodes 
	- ![[Screenshot 2025-02-13 at 8.56.19 AM.png|600]]
	- it is possible to make this system linearizable if we use read repairs from clients that read stale data 

The cost of linearizability
![[Screenshot 2025-02-13 at 9.31.48 AM.png|600]]

- this is a configuration of a multi-datacenter replication
- the network connection inside the datacenter is working the network between the datacenter is not working creating two independent data centers 
- if this was a multi-leader database system then even if there was a network partition between the data centers, the operation would continue normally because the leader would asynchronously queue up any writes until the network comes back alive 
- if this is a single-leader database system then there is a problem since only one of the datacenter can hold a leader database and if a client connected to a follower datacenter wants to send read and write request to the leader then it cannot because of the network partition
- for a non-linearizable system, the client could just ask from the follower datacenter and get a stale data 
- for a linearizable system, this is not possible, so for them the datacenter should be as if it were unavailable and no request can be sent to that datacenter to provide linearizability

the tradeoffs when implementing linearizability is explained by the CAP theorem which states that 
- if the network is working correctly then the system can provide both linearizability (consistency) and availability at the same time 
- but if there is a network partition then the system can choose between either consistency or availability

- when many systems were using systems that provided linearizability on a cluster of machines with shared storage, CAP theorem encouraged database engineers to explore a wider design space of distributed shared-nothing systems.





the idea is to give an illusion of having only a single replica and all operations on it are atomic
if a client successfully writes to a data system, then all the following client's read request should return the last wrote data on the data system 

![[Screenshot 2025-02-09 at 2.27.23 PM.png|600]]

in the above picture the following things are happening:
2. after the match ends, then end score is written to the leader database
3. the leader propagates the change to both follower 1 and 2 at the same time
4. because of packet processing delay or some kind of delay, follower 2 receives the update log after follower 1
5. Both the follower 1 and 2 write to their respective database 
6. client Alice sends their read request after the replica has been updated with the new value hence they receive the upto date final score news 
7. client Bob sends read request before follower 2 has replica the new update hence will not find the final score news 
this scenario is an example of a system that is not linearizable 



