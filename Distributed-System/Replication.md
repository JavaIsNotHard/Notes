## Consistency model 
what happens a client sends a request to it
in an ideal world, the request executes instantaneously

but in reality, the request needs to reach the leader, which has to process it and send back a response to the client
the request executes somewhere between its invocation and its response

in a replicated state machine such as raft, any modification operation needs to go through the leader
but what about reads, if the read request were limited to the leader only then the read throughput would be limited to that of a single process
but if our system is inconsistent and we allow our followers to serve read request then two different request may result in two different responses due to the inconsistency in the system

there is a tradeoff between having a consistent system and the system performance and availability

we can define what consistency means with the help of consistency models

### strong consistency (linearizability)
if every request are served through the leader then it appears that operations take place atomically 

### Sequential consistency
real time ordering of the operation does not matter 
works like sequential thread operation that executes instruction in some order that is not guaranteed 
the system will behave as if the all instructions are interleaved in a sequential manner
this mean multiple execute order is possible and is also allowed 
suppose: in the real time ordering of the operation this is the sequence 
A : x + 1 y + 1
B:        x + 1

here the operation x + 1 between client A and client B are overlapped and any one of the operation can happen and is allowed in this guarantee as same as linearizability

all the processes in the system are executed in some sequential order similar to database txn operation orders
the operation of each individual process will happen in the order it was specified in the program

i.e in Client A's process, y + 1 can never happen before x + 1, but client B's x + 1 can happen before client A's x + 1

the consistency model that ensures operations occurs in the same order for all observers, but doesn't provide any real-time guarantee about when an operation's  
### eventual consistency

### CAP theorem 
in the face of network partition or physical partition, you can choose between consistency and availability and not both

PACELC theorem which states that in the case of partitioning, one has to choose between availability and consistency but else when teh system is running normally in the absense of partition, one has to choose between latency and consistency

there is a tradeoff between the amount of coordination required and performance
one way to design around this limitation is to move coordination away from the critical path
example, in a strong consistency system, the leader has to contact a majority of the followers, and this is the critical path of this consistency system

### Chain replication
fault tolerance is delegated to a dedicated component, the configuration manager (like zookeeper) or a control plane
the configuration manager or the control plane is reponsible for checking the chain's health and detect any fault process and removes it from the chain

all write request are sent to the head of the chain and all read request are sent to the tail of the chain

tail receives an update it applies it locally and sends an acknowledgement to its predecessor to signal that the chain has been committed

this ensures strong consistency as all writes and reads are processed one at a time 

the control plane ensures that there is a single view of a chain's topology that every process agrees with i.e every process has access to the same consistent data throughout the chain

for the control plane to provide this consistent view of the system, the control plane must be fault-tolerant which requires consensus protocol

unlike raft, a read request from a client can be served directly from the tail's local state without contacting the other replicas first, which allows for higher throughput and lower response time

write throughput can be improved by pipelining write requests
read throughput can be increased by distributing reads across replicas 
each replicas store multiple versions of an object including a version number and a dirty flag
as the change propagates from the head to the tail, the object is marked as dirty
when the change reaches the tail then the object is marked as clean and acknowledgement is sent down the replica
now when a client requests read to any replica then it ca immediately serve it if the latest version is clean

for each key, there are multiple versions of the data, this means that writes do not override each other but rather create new version 
initially the flag for all the data object is set as dirty, once the write is acknowledged by the tail then the flag is set to clean in all replicas 
if the client request gets sent to a replica whose data item is flagged as dirty then it first contacts the tail to request the latest committed version

chain replication splits the data plane from the control plane and this is a common pattern in distributed systems


