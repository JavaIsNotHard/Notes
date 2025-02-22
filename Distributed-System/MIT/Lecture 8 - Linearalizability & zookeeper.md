
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



# Zookeeper

why do we need zookeeper like services?
- in contrast to raft which is a library, not a standalone service, we have to write a system that uses the raft library
- is there is a standalone service that can byte off the complexity required to built distributed systems and package them up into a standalone service that anybody can use 
- zookeeper is the answer, as it packages all the complexity behind its service and exposes an API for application developer to use

- zookeeper is a fault-tolerant coordination service
- zookeeper is a replicated system, an important question to consider in zookeeper is whether increasing the no of replication will also proportionally increase the amount of performance i.e if we have N times the server, can we yield N times the performance

- zookeeper underneath can use any form of replication services like raft, zookeeper uses something called as zab which is almost identical to raft

- zookeeper architecture contains the following component
	1. ZK layer
	2. Zab service 
	3. replicated log

- the client send their request to the ZK layer which then replicate the request to all the replicated servers
![[Screenshot 2025-02-16 at 10.37.45 AM.png]]
- does this replicated configuration provide N times the performance if we add N servers?
- the answer is No, because our leader here is the bottleneck. All request has to pass through the leader and also if the replication is synchronous for linearizability then the leader also has to wait for the replication to be completed in all other replicated servers
- therefore in this configuration, more servers means slower operation

- so what to do to resolve this issue?
- the internet is read heavy
- which means we can send write request to the leader but read request to the replicated servers 
- now the more servers we add, the more clients we can serve to 

- another question that arrises, is sending read request to replicated server a good approach?
- a replicated server will have all components required to serve the read request of a client but there is no guarantee that any server other than the leader will have the most up to date value of a given key
- if zookeeper is using a raft replication service underneath then there is a problem because raft uses quorum number in order to perform any operation
- this means that a quorum of replicas can return success for the leader to commit those changes in all services
- suppose in a 3 server architecture, quorum no is mainly 2, which means that it is enough for 2 servers to return success in order for the operation to commit and move further. One of the 2 servers is going to be the leader.
- suppose the third server returned failure because of some internal computing error or network error so was not able to perform the replicated operation in its local state machine
- if the client's read request were to be routes to this stale server then the client is going to receive stale results hence will not provide linearizability 

- so how does zookeeper resolve this problem?
- it doesn't, zookeeper does not provide linearizability

what are the guarantees provided by zookeeper
- writes are linearizable 
	- even if there are two or more concurrent writes, the system behaves as if it executes the write one after another in some order that matches the real time ordering
- client operations are executed in FIFO order 
	- this is a per client guarantee i.e the ordering is only guaranteed for a single client sending either a read-read or read-write or write-write or write-read request
	- write operations happen in the order in which the client specified the write request i.e client A sends Wx2 -> Wx1 -> Wx4, this is the same order that the system executes the write request which means write x 2 happens first then write x 1 and then finally write x 4
	- for this guarantee, the client could add a timestamp to each write request for the write request ordering guarantee

	- for read requests the leader is not involved, if the client issues a sequence of reads in a particular order relative to the log the on the replica its talking to, the clients read must occur in some particular point in the log and furthermore, the successive reads have to observe points that don't go backwards i.e if a client requests one read and then another read, the second read is allowed to execute in same or  later point in the log but no before the first read.
	![[dfd0.png|1000]]
	- if the current follower server is down and the request is routed to another follower server then the FIFO read guarantee still applies in the sense that the next read operation can either start from the same point or after that point
	- this is implemented by the leader tagging each read request with a Zookeeper id (Zxid) which is an entry number
	- each replica will respond with a Zxid for every read request (the current read entry number in the log) of that state machine and send it back to the client 
	- the client has to remember the Zxid of each replica so that if the read request is forwarded to another replica, the read can still be the most up to date as the previous follower

	- if a replica does not have the most recent Zxid then it has to stall and wait to execute all the pending operation before returning any response
	- this ensures that FIFO is also guaranteed between read-write as well as read-read
	- suppose a client sends a write request first to the leader (the leader is asynchronously so it immediately returns a success response to the client) and the client immediately sends a read request of the same data item just wrote, then if the replica hasn't executed the last write operation, has to wait for it to execute the last write operation just that write after read ordering is guaranteed

- is avoiding read linearizability a good programming model?
- sync operation which is a write operation is a way for the client to synchronize the replica that it is talking to by making the replica wait for it to get the commit message from the leader and execute it 
	1. the client first sends a sync write request to the leader
	2. the sync write request is propagated to all replicas
	3. the client will then wait until the replica has the sync log entry in its log
	4. having a sync log entry means that all writes before the current entry has been properly committed to the replica and hence the log entry before the sync log entry is the most recent up to date entry


## Zookeeper white paper

- zookeeper arranges data in a hierarchical structure called the zookeeper data tree 
- the zookeeper data tree is composed of znodes 
- zookeeper provides an API for the client to communicate with the Zookeeper data tree from the Zookeeper service 
- zookeeper is a replicated service which means that each node runs the same copy of the zookeeper data tree 

components:
1. zookeeper client API which exposes the Zookeeper service 
2. z-node, which is a in-memory data node in the zookeeper data tree
3. Zookeeper data tree is a file system like interface that exposes API for the client to interact with the znodes, which are basically files underneath

types of znode includes:
1. persistent znode -> exists until deleted explicitly 
2. ephemeral znode -> exists as long as the session in which it was created exists
3. sequential znode -> have a monotonically incrementing number appended to their name. Example, in a file structure /election/node_00001 for the first write entry on the node /election followed by /election/node_00002 for the next write and so on 
4. ephemeral sequential znode -> combines the property of both ephemeral znode and sequential znode

- every znode type except for ephemeral znode can have children
- when using a ephemeral znode, failure of nodes can also cause for deletion of znode


why use zookeepr?
1.  distributed configuration managmenet 
2. leader election
3. distributed locking
4. service discovery and more



- clients can `watch` on a particular znode which on change notifies the client
- a client issues a read operation with the watch flag, the operation completes as normal but the service promises to notify the client when information of that znode changes 
- watches are one-time triggers and are unregistered and have to be reregistered after a trigger goes out for a particular znode


zookeeper sessions
- a client first creates a session with the zookeeper ensemble
- each session has a associated timeout 
- a session is considered faulty if the zookeeper service does not receive anything in the session within the timeout 
- a session ends when client closes the session handle or zookeeper detects that the client is faulty

- a session is not associated with a particular zookeeper servers which enables a client to move between the zookeeper servers within a zookeeper ensemble
- the timeout is used to detect client crashes and to maintain fault-tolerance
- if a session associated with a particular client is removed then all the ephemeral nodes created within the session are also removed


zookeeper guarantees
1. linearizable writes 
2. FIFO client ordering 

example to show to these two guarantees interact:
- a system with multiple processes elects a new leader 
- the leader needs to make various changes to its configuration which is done through the zookeeper client API and needs to notify all other worker process when the update completes
- we have two important requirements here
	1. as the new leader makes change, we do not want other processes to start using the configuration that is being changed 
	2. if the new leader dies before the configuration has been fully updated then we do not want any processes to read partial updates
- suppose we have configuration in the path `/config/param1`, `/config/param2`
- before making changes, the leader deletes a special "ready" znode /ready to indicate system has not been fully updated
- once the configuration parameters are completely updated then the leader can create a new "ready" znode
- because of the ordering guarantees, the process that sees the ready znode should also see the changes made in the configuration by the leader

why delete the "ready" znode?
- other processes can "watch" the "ready" znode and wait for notification when the configuration has been fully updated
- this prevents other process from reading configuration when it is still being updated


zookeeper implementation:
![[Screenshot 2025-02-18 at 11.47.43 AM.png]]

the above figure shows the high level architecture of a zookeeper service 

- request is processed by the request processor component, upon receiving the request, the server prepares it for execution
- if the request requires coordination (write request) then they use the agreement protocol (an implementation of atomic broadcast)
- the changes are committed to the zookeeper database which is fully replicated across all servers of the ensemble 
- in the case of a read request, the replicated database will directly generate the response

- the replicated database is an in-memory database containing the entire data tree 
- for recoverability, zookeeper also uses write ahead logging where before any operation, the operation is first wrote to the disk
- also periodic snapshot of the entire in-memory database are generated

### request processor
- the zookeeper messaging layer is atomic and all replicas receive txn in the same order guaranteeing that no divergence occurs between them 
- the leader converts client request into txn before applying them and unlike client request which are not idempotent (two creates request of the same data item due to network delay will create duplicate data in the data tree), the txns are idempotent(each txn is identified by a unique id )


### Atomic broadcast message
- all writes or update requests are forwarded to the leader 
- the leader executes the request and broadcast the changes to the zookeeper state through Zab protocol
- the original server that received the request forwards the request to the leader and once majority of the server returns commit acknowledgement then the original server responds back to the client 

- to achieve high throughput, zookeeper keeps thousands of request in different stages of a pipeline
- for example, one request may just be received by the original server, one request may be waiting for ack from the replicas, one request may have just been responded back to the client and so on
- zab provides stronger ordering guarantee than regular atomic broadcast by the following mechanisms
	- changes broadcast by leader are delivered in the order they were sent
	- all changes of the previous leader are delivered to the new leader before the new leader broadcasts its own changes
- zookeeper uses TCP to deliver messages between server and client



mini-transactions in zookeeper
once all the operation succeeds, we have achieved an atomic read-modify-write of the operation
mini-transactions are different from real database transaction in the sense that they only guarantee atomic read-modify-write pattern of any sequence of operation

example, a simple service that user use to increment a count
```
x = get(x)
put(x, x + 1)
```

above is a simple example of a non-atomic counter because if there were two concurrent clients getting serviced through different servers then they both will read the same value of x (suppose x = 10) and then increment the same value twice (x = 10 + 1 and x = 10 + 1) hence the final result is x = 11 and not x = 12

```
x, v = getData("f")
if setData("f" x + 1, v)
	break
sleep
```

the above is an example of atomic counter because we have an test and set variable v which is basically the version number of the data object in zookeeper. 
when writing data, if the current version number matches the leader's version number of the same znode i. e the value is fresh and no other client has modified the value then we write our new value overwriting the previous and exit out
if there has already been a change in value and the value we read previous is stale then we sleep for some time and then re-read the value, increment the counter and again check the version number
this approach makes sure that two or more concurrent clients changing the data at the same time is atomic and correct

the herd effect
scalable lock
partial failure does not provide atomicity