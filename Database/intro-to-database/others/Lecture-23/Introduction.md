## Distributed transactions
- local transactions 
- global transactions : access and modify data in several local databases

for a global transaction, we need to have multiple nodes
these nodes can either be in a single data center (parallel database)
or they can be geographically separated as a distributed database system



- each node will have its own transaction manager which manages local transactions 
- the various transaction manager coordinate with one other to execute global transaction

- each node has two subsystems:
	- transaction manager -> responsible for following things:
		- maintaining a log for recovery purpose 
		- coordinate the concurrent execution of transaction executing on that node 
		- they reside for each local node and is responsible for a only a single node 
	- transaction coordinator -> responsible for following things:
		- starting the transaction 
		- breaking a txn into multiple sub txn and distributing those sub txn to execute in multiple nodes 
		- coordinating the termination of each txn, either all node commit the txn or they all abort

![[Screenshot 2025-02-23 at 9.03.05 AM.png|600]]

- this figure explains that each node has both a transaction manager and a transaction coordinator
- the transaction coordinator is responsible for managing the actions of all transaction manager
## Commit Protocol 
- the protocol must ensure that all the nodes that executed a txn T must agree on a final value after the execution 
- T must either commit at all nodes or it must abort

- the 2PC (phase commit) protocol operates in two phases 
- suppose T be the txn, Ni be the node that started the txn and Ci be the txn coordinator
- when a txn T is completed, then all the nodes that executed the txn T will infrom the coordinator Ci that T has completed on which Ci will then start the 2PC protocol
	- phase 1:
		- the coordinator node appends a "prepare T" log in its log manager and force writes it to stable storage
		- the coordinator node then sends the prepare T message to all other nodes that execute the transaction T.
		- The transaction manager of each node will determine whether to commit or abort the transaction depending upon the state of the transaction
		-  if the txn is not ready to commit then it sends a "no T" message back to the coordinator node and force writes it to stable storage
		- if the txn is ready then it sends a "ready T" message back to the coordinator node and force writes it to stable storage
	- phase 2: 
		- after the txn receives either the "ready T" msg or the "no T", the coordinator node then decides whether to commit the txn or not
		- if the received msg was "ready T" and the response is anonymous from all other nodes then the txn is committed by the coordinator and a "commit T" msg is send to all other nodes and after the "commit T" msg is written to stable storage 
		- if the recieved msg is "no T" from any one of the node then it has to decide to abort and then writes "abort T" into stable storage and sends the msg to all other nodes to make them abort their txn as well.
		- the coordinator node also needs to make sure not to wait for a node indefinitely and use some sort of time interval within which the other nodes need to send their response
	- in some implementation of 2PC, at the end of the txn all the nodes send a "acknoowledge T" msg to the coordinator acknowledging that they recieved the commit or abort msg. After the coordinator receives the msg then it appends a "complete T" log record to stable storage 

![[Screenshot 2025-02-23 at 9.13.15 AM.png|600]]

## Handling failures of node 
- failure of participating node
	- the coordinator node detects failure in any of the participating nodes 
	- if the participating node failed before sending a "ready T" msg then the coordinator assumes that it intended to send "abort T " and hence aborts the txn
	- if the participating node failed after sending a "ready T" msg then the C node will continue executing the txn ignoring the failed node. 

	- the failed node after recovery must perform some operation to make it consistent with other participating nodes. 
	- To do this the recovered node must examine its log before it went down
			- if the log contains "commit T" then the node executes redo(T)
		- if the log contains "abort T" then the node executes undo(T)
		- if the log contains "ready T" then it must consult either the coordinator node to determine its faith. If the coordinator node is not active then it must consult other participating node by sending a "querystatus T" msg to all the nodes 
		- if no node contains the information then the decision about txn T is postponed until one node has the needed information. this is done periodically
		- if the log does not contain any control logs (commit, abort or ready) then we know that the node failed before responding to the "prepare T" msg from the coordinator and hence needs to abort the txn T.
- failure of coordinator node
	- when the coordinator node fails then the faith of the txn T depends on the active participating nodes
		- if an active node contains the "commit T" then it is assumed that the C node failed wanting to commit the txn but failed before the msg reached to all the active node hence the txn T is committed 
		- similarly if any active node contains the "abort T" then the txn is aborted. 
		- if not all the active nodes have the "ready T" record then there is no way those nodes sent the "ready T" msg back to the coordinator and it is assumed that the coordinator wanted to abort hence the txn is aborted 
		- if none of the above cases match then all the active nodes will have the "ready T" in their log record which means all the nodes are ready to commit but the decision of the coordinator node has not been made so all the nodes wait for the C node to recover
		- the waiting for the C node creating a blocking problem if the C node is not recovered for a long time all the other txn that wants to access the data are blocked for the same duration of time.
	- recovery and concurrency control:
		- in-doubt transactions are all txn that contain neither the "commit T" nor the "abort T" control message in its local log
		- when a participant node recovers from failure then if it in a in-doubt transaction then it has to wait for the coordinator or other participating node for its next step
		- if the coordinator is not available or other participants do not have the required infromation then the txn is stalled 
		- instead a new logging mechanism is used having the structure such as "ready T L" where L is the list of all write locks held during the point by the txn
		- when the node recovers, then it will reacquire all the writes locks held before the failure listed in the log and then start a new txn instead of waiting for other nodes

## Distributed consensus problem 
- in a distributed environment with n nodes, each node is made to vote on a certain decision based on the problem
- the problem here is going to be either to commit the txn or not
- the vote for each node should be visible to all other nodes inside the distributed environment 
- one of the main properties of distributed consensus problem is non-blocking operation as long of participating nodes are alive and are communicating with other nodes
- Raft and Paxos are two major distributed consensus protocol 
- in this protocol the coordinator does not locally decide to commit or abort the txn but uses the distributed consensus protocol to determine whether to commit or abort
- since the protocol is fault tolerant, the txn will succeed even if some nodes fail as long as majority of the nodes are alive 
- the txn is declared committed by the coordinator if the consensus protocol completed successfully

- there are two possible cases for failure:
	-  **the coordinator fails before informing all participating nodes of the commit or abort status of a txn**
		- if a coordinator fails, then a new coordinator is appointed 
		- the new coordinator node checks the status of the txn by communicating with other participating nodes
		- majority of the participating nodes must respond for the decision to be made
		- if no decision were made before then the new coordinator node starts a new 2PC protocol for all participating nodes
	- **the consensus protocol fails to reach a decision** 
		- failure of the protocol can happen due to failure of participating nodes 
		- failure can also happen if majority votes cannot be reached on any decision 
		- failure can happen if a coordinator node fails after sending a commit request and the commit request was slow to reach other nodes. meanwhile a new coordinator node is appointed and it sends a abort request because the previous message could not reach other nodes. there is a conflicting request between commit and abort
		- if the protocol fails then it can re-initialed the protocol again

## Persistent messaging to avoid distributed commit problem 
- works similar how banks transfer checks 
- one bank deducts a certain amount from the total balance and prints out the check 
- the check is physically transferred to the other bank where it is deposited 
- after verifying the check, the other bank increases its local total balance amount 
- the check constitutes messages exchanged between the two banks 
- this makes sure that the funds are not lost or increased incorrectly also the check but not be duplicated and deposited more than once 

- similar persistent messaging makes sure that the message is received by the recipient exactly once 
- this is done as follows:
	 ![[Screenshot 2024-12-07 at 09.28.25.png]]
	- **sending node protocol**
		- each txn that wants to send message from one node to another node in an unreliable medium needs to send the message to a messages_to_send relation buffer instead of directly sending the message to the receiving node 
		- each message has a unique identifier and some record to identify the receiving node
		- a message deliver process monitors the message_to_send relation
		- when it finds a new message in the relation, it sends the message to that particular receiving node 
		- the concurrency control mechanism ensures that the messages are only send once the txn that send the message commits i.e the messages are sent by the message delivery process only when the txn commits
		- if the txn aborts, then its corresponding message is removed from the the messages_to_send relation
	- **receiving node protocol** 
		- the message is added to the received_message relation only if it is not present in the relation (the message identifier helps prevent the duplication)
		- the relation also has an attribute corresponding to each message whether or not the message was processed.  if is was added just now then the value for that attribute is set to false, once processed the value is set to true
		- after the txn commits or if the message is already in the relation then the message receive process sends an acknowledgement back to the message delivery process 
	- **processing message** 
		-  if there are new pending messages in the received_message relation then a new txn is creates to perform action specified in the message
		- then same txn then sets the processed flag to true


## Concurrency Control in Distributed environment
- single lock manager  
	- a single lock manager is used which resides in a single node 
	- all read write request must go through this lock manager in order acquire and release lock
	- if the lock can be granted then a lock granted message is send to the node which initiated the lock request 
	- if the lock cannot be granted then the the lock is delayed in this node and lock not granted message is send to the node which initiated the lock request 
	- advantages:
		- simple implementation
		- simple deadlock management
	- disadvantage:
		- bottleneck of a single node 
		- single point of failure
- distributed lock manager
	- all nodes have their own lock manager
	- for all read write request, each txn must consult their own lock lock manager
	- lock grant or not message is sent back to the initializing node 
	- advantage:
		- simple approach
		- no single point of failure
		- no bottleneck in a single node
	- disadvantage:
		- complex deadlock management


## Deadlock handling
- deadlock prevention
	- all the techniques used in the single node approach can also be used in distributed approach
- deadlock detection
	- use of wait-for graph
	- even though the wait-for graph of local txn can be acyclic but if we take the union between all the wait-for graph of all the txn running in different nodes then we might get deadlock
	- **centralized deadlock detection**
		- use of global wait-for graph (union of all local graphs)


## Lease
- in distributed database system, locks acquired by failed nodes results in other txn waiting for the lock to wait indefinitely until the node is recovered again
- in two phase commit, before the coordinator node sends the commit or abort operation to all participating nodes, some nodes can fail which results to the problem discussed above
- this problem can be solved by using lease which basically is lock with a expiration time
- a lease can request the lock manager to renew the lock if the request is sent before the expiration time


## Timestamp generation in distributed system
- single node distributing the timestamp for all transactions (this is done in centralized scheme)
- problem with that approach is basically single point of failure
- in distributed systems, each node generates a unique timestamp and the global timestamp is generated by concatenating the local timestamp and the node identifier
- if multiple threads are running in a single node then the timestamp could be the concatenation between the thread identifier and the node identifier
- the order of concatenation is important
	- the node identifier should be used as the least significant position of the global timestamp such that timestamp generated in one node is never greater than timestamp generated in another node
- we also need a mechanism to generate timestamps fairly such that a fast node does not always get the largest timestamp. this can be done by the following methods
	- keeping all the nodes synchronized with the central server's clock
	- if the local time of a node is greater than the server's time then the node needs to slow down, if the local time of the node is less than the server's time then the node needs to speedup

- validation based ordering in distributed settings
- the same three timestamps are used to implement validation based concurrency control in distributed systems which includes
	- begin timestamp
	- validation timestamp
	- finish timestamp
- optimistic concurrency control without read validation is mostly used in distributed settings



## Replication
- required for high availability i.e even in the case of single node failure other replicas can accept request on behalf of the failed node 
- replication done in tuple level is hard so the most used approach is replication of each partition

- asynchronous replication of data where a primary copy propagates changes to other nodes
- disadvantage of this approach is single point of failure 
- another drawback is that the other nodes are out of date for some time period until the update it propagated to this node

- benefit of this approach is that all locks are released when the txn commits in the primary copy
- if the primary copy needs to wait for other replicas to commit then the lock that it holds makes other txn wait for that lock hence the no of txn that can be executed will be less. This happens in synchronous replication where the primary copy waits for the update to persist it its participating nodes

## Dealing with locks in replicated data 
- primary copy
	- a single node is defined as a primary copy which contains all the latest data item written to the database
	- all the lock information are held in the primary copy hence if the primary copy fails then all the lock information would be lost hence the data item would be inaccessible even though other replicas are accessible
- majority protocol
	-  the basic idea of this protocol is that we make sure that at least n/2 of the node has the lock acquired for the txn to continue executing
- biased protocol
	- request for shared lock is given more favor than exclusive lock 
	- in shared lock the lock is only acquired on the node from where the data is being read from 
	- in exclusive lock all nodes that has the corresponding data item will hold the exclusive lock 
- quorum consensus protocol 
	- each node is assigned a non-negative value called the quorum value
	- this value is based on the two values
		- read quorum -> minimum total weight of the node to execute the read operation
		- write quorum -> minimum total weight of the node to execute the write operation


## Majority based protocol for working inspite of failure 
- the rule is same as before i.e the txn cannot continue until half the available node can acquire the lock 
- this approach uses version number to associate when the data item was last written 
- suppose A be a data item replicated in n different nodes n
- the txn does not operate until it has successfully obtained lock on majority of the nodes n
- read operation reads all the data item from nodes that has acquired the lock for that particular data item and the data item with the highest version number 
- write operation writes to all nodes that has acquired the lock and has the data item and changes the version number to a new number
- updates to replica can be committed using 2PC


## Reconfiguration and Reintegration
reconfiguration deals with removing failed nodes from the list of replicas of the distributed database servers such that request are now no longer routed to this server anymore 
for this the database catalog must be updated to remove the failed node from the list of replicas

- reintegration deals with making sure that when failed nodes recover, they obtain the most up to date value from other replicas or from the leader 
- recovery protocol must be applied, like redoing or undoing changes from its log before it failed, consulting other nodes for changes since it failed and then applying them locally

reintegration is easier to deal with when used alongside majority consensus protocols because we can reintegrated nodes without having to make them consistent with the current state of the system since it will catch up to all the recent changes made

the database catalog tables notes which partition tables are replicated in which nodes 


## Coordinator Selection
- maintain a backup coordinator alongside the main coordinator
- the backup coordinator maintains all the information that the main coordinator maintains and the only difference is in its function where the backup coordinator does not perform anything that affects the state of other nodes, those operations are done by the main coordinator
- when the main coordinator fails then the backup takes its place and performs all the action on behalf of the failed coordinator 
- the advantage of this approach is fast recovery from failed coordinator 
- the main drawback of this approach is the overhead to synchronize the main coordinator and the backup coordinator in each step


## Two phase commit using consensus protocol
