Why could we distribute the load to multiple machines?

- Scalability -> When the data volume, write load, read load exceeds the capacity of a single machine then we can distribute the load into multiple machine 
- Fault tolerance -> If a single machine is down then we can still serve request and have data available because we have multiple servers and replicated data 
- Latency -> If the users are distribute worldwide then having machines or servers in multiple different location around the world can benefit from the low RTT of requests.

## Scaling to higher load 
- shared memory architecture (vertical scaling, scaling up)
- shared disk architecture 

### Share nothing architecture 
- horizontal scaling (scaling out)


# Replication
- we can either replicate the entire dataset into multiple machine if the dataset is small
- if the dataset is large to fit in a single database then we need to perform partitioning 

- If our data doesn't change much over time then replication is easy because we just have to replicate the data once and be done with it
- If the data changes regular in the replicate database then we need to coordinate the reads and writes between them. These are done using algorithms such as single-leader, multiple-leader and leaderless. 

 - eventual consistency 
 - read your writes 
 - monotonic reads

## Leaders and followers 
- objective is to have consistent replica of data among multiple machine or databases
- one approach is leader based replication
- in this approach we appoint a single leader and many followers, 
- all the client writes are handled by the single leader, the changes are appended to a replication log or change stream and also to its local storage
- When the leaders writes to its local storage it also sends signals and messages to its slaves or replicas as a form of replication log. The slave server will have to go through the log and make changes to their own local storage in the same order of the leader server. 
- clients can read data from both the leader and the replicas but writes can only be processed by the leader 

![[Screenshot 2024-10-26 at 08.14.40.png]]

### Synchronous vs asynchronous replication
- in synchronous replication, the leader waits for its follower to be upto date with the latest write update.
- In asynchronous replication, the leader doesn't wait for the confirmation from the followers
![[Screenshot 2024-10-26 at 08.37.06.png]]
- Here the leader waits for the new changes to the replicated in follower 1 but doesn't wait for changes to be updated in follower 2
- There is an substantial delay between follower 2 getting the replication log and follower 2 actually updates its local storage. This delay can be caused by multiple reasons. 
	- The database replica is operating in its maximum capacity 
	- There is network related issues 
	- The follower is recovering from a failure 

- Synchronous replication in good for data consistency between the leaders and the replicas because the leader waits for the replicas to complete their write operation before moving on which means the leader knows that the data have been written to all its replica. This means even if the leader where to have a downtime due to node failure, we are guaranteed that one of the followers can take place as a new leader node because they have the same data as the leader had. 
- Sync replica is also not good for performance because the leader has to wait for the replica and if the replica itself is down then this will block the entire operation of the leader and its followers
- Practically we have a single sync follower and rest of the replica are made async such that we have two databases which are guaranteed to have consistent data. This approach is called **semi synchronous**.
- making all follower async violates the durability guarantee of a database system but many applications still use this approach for its performance guarantees
### Setting up new follower

- from time to time we may need to add new followers because one of the followers died or to increase the no of replicas. 
- objective is to make sure that the new replica has the most upto date data. 
- Copying data from one node is not appropriate because clients write to database frequently, data is always in constant flux. So we do not use this approach 
- another approach is to hold a lock on the database (making it unavailable for writes) but this violates high availability. 
- Most used approach has the following steps
	-  take a snapshot of the leader database without locking the entire database. Some db has this feature builtin
	- copy the snapshot into the new followers local storage 
	- The leader must maintain a log sequence number (PostgresSQL) or binlog coordinates (MySQL) which holds the position that the replication log was in when the snapshot was taken such that after the snapshot has been copied to the replica it can read all the logs after the snapshot and be in a consistent state. 
### Handling node outages
- node can go down because of node failures or planned downtime for maintenance.
#### follower failure: catch-up recover
- the follower knows the last transaction processed before the failure. 
- this means that after the follower reconnects to the leader it can ask the leader for all the remaining logs to be processed to be upto date
#### Leader failure: failover
- when the leader fails then the system needs a new leader
- the leader is either elected manually by the db admin or automatically within the system 
- the following steps happen in automatic failure:
	- determining that the leader has failed: This can be done by using timeout i.e sending message from time to time throughout the leaders and followers and if a node does not respond after a particular time period say 30 seconds then that node is considered dead
	-  elect a new leader: this can be done by a controller node or the node that has the most upto date data is selected as the leader 
	- reconfiguring system to use the new leader: clients now need to send write request to the new leader location (done by request routing). if the older leader comes back, it still thinks that it is the leader. The system needs to make sure that the old leader becomes a follower 

- Things that ca go wrong with failure:
	- in async database, the leader may fail before it sends the latest changes to the replication log which is in the local storage o the leader database. After failure, the old leader rejoins the cluster of the new leader but it also has data that the new leader does not, so what happens to the data? The new leader may have conflicting writes to the old leader. If we discard the conflicting data from the old leader then we violate the durability guarantee (users write are lost which is not good)
	- Discarding writes is dangerous if the system is coordinating without outside systems. This happens with Github when the new leader used primary key assigned also by the old leader. They used a redis cache which stored the old leaders data which means that there was a conflict between the database and redis. This causes some private repos and data from one account to be visible from another account.
	- There can be situations where there can be multiple leaders. This is known as split brain. 
### Implementation of replication log
#### statement based replication
- SQL statements that update or change the state of the database are recorded and send from the leader to its followers, statements such as ALTER, UPDATE, DELETE
- This is not a good approach because of the following reasons:
	- call to nondeterministic functions such as NOW() which returns the current timestamp and RAND() which returns a random number will be different for the leader as well as all the followers. 
	- if a statement depends on an existing data on the database then they must be executed in the same order as they were brought from the leader. This can be limiting when there are multiple concurrently executing transaction.

#### Write ahead logging
- the log contains a sequence of bytes containing all the writes to the database.
- The log describes data in a very low level, it contains details of which bytes were changed in which disk block. this makes replication closely coupled to the storage engine 
- so changing storage engine version from one version to another can impact the way data are stored on disk 
- we can also perform a zero-time downgrade by first upgrading all the follower's database software and then performing a failover and electing a new leader such that the new leader has the new database software without any downtime. This is only possible in the case where the DBMS system allows version mismatch
- If version mismatch is not provided by the DMBS then there needs to be a downtime.

#### logical (row-based) log replication
- use of different format for replication and for storage engine. This decouples the replication database with the storage engine underneath
- instead of appending low level bytes, it stores row level operations such as 
	- for an inserted row, the log contains all the new values of all columns
	- for deleted row, the log contains information to uniquely identify the row that was deleted
	- for updated row, the log contains info to uniquely identify the row and the new value of the column
- A txn that modifies multiple rows at once contains log record for each operation followed by a record indicating that the txn was committed.
- Version mismatch between leaders and follower are allowed because the format of the replication log is different from the storage engine log

#### trigger based replication
- use of sql triggers and stored procedure 
- when a data change event occurs then the trigger would be activated and the changes would be logged into a separate table from which it can be read by a separate process.


## Problems with replication lag 
- problem with synchronous leader based apporach is that one node outage can lead to the distrubance throughout the replication
- problem with asynchronous leader based approach is that the followers are not guaranteed to be upto date with the leader database. 
  - the delay can be due to many reasons which has been discussed previously such as 
	  1. network congestion
	  2. node operating in its limit 
	  3. and more 
- but there is a guarantee that the follower will eventually catup to the leader. this is known as eventual consistency .

### Reading your your writes 
- some application lets you see the write that you just performed in the application for example when writing a comment the user can immediately see the new comment their interface. 
- For read heavy system, the leader is configured to handle all the writes as well as reads and the followers are used to handle all the reads. This becomes a problem if the user reads from the follower that is not yet consistent with the leader i.e due to replication lag the update has not yet reached this follower node. If no result is submitted to the user then they will assume that the write was lost. 
- For this we need something called as read-after-write consistency which guarantees that the data written by the user will be visible but he same cannot be said for other users write.
- Implementing read-after-write consistency in leader based replication
	- when reading something that the user may have modified, we can read it from the leader otherwise from the follower. For this we need to keep track of the values that have been updated without querying for the updated value. For information that can only be modified by the user only can be done by reading from the leader. 
	- if most part of the application is editable by the user then using the leader for all the reads will make the leader the only active node which goes against our use of distributed and replicated nodes. So instead we set a time period (one minute from the write) for when the leader will be used to serve the read request, we also actively monitor the replication nodes to keep track of which nodes have upto date data. After the time period the nodes which ave the upto data can be used to read. We also have to prevent queries on any follower that is more than one minute behind the leader. 
	- The client is made to remember the timestamp of its most recent write such that the node used to read for that client should have date until the timestamp. If the client does not have the data then it can query another node for the same thing and if no nodes have the required data then the client has to wait until the nodes have caught up to the most recent write timestamp of the client.
	- If the replicas are distributed geographically then the read request that must be served by the leader must route the request to the datacenter that has the leader node. 
- We also need to ensure cross platform read-after-write consistency which basically means devices of the same user must see the update at the same time. The issues with this implement includes the fact that the request from different devices can be routed to different data centers that are not yet consistent with one another. 

### Monotonic reads 
- this anomaly makes user see things moving backward in time. 
- This happens when the user requests multiple read queries at the same time which would be routed to different datacenter hence different values. 
![[Screenshot 2024-10-28 at 09.06.11.png]]

- Here user 2345 sends two read request at different time and both are handled by different follower nodes. Follower 2 is behind follower 1 because of replication lag which means the first request of user2345 yielded latest value but the second request of user 2345 yielded old value. This can be confusing for users.
- Monotonic read is a guarantee that this anomaly does not happen. One way to achieve this is by making the read request from a particular user be routed to the same follower node. This can be done by taking a hash of the user_id and finding an appropriate follower such that each read request will be routed to the same follower. 

### Consistent prefix reads


## Multi leader replication
- we have multiple leader accepting the writes. each leader must share data in some way to all other leaders to have consistent state in all nodes. 
- This is useful if we have datacenter in different location such that each datacenter in one location has a single leader for themself. 
- Having multiple leaders also reduces the load that needs to be handled only by a single user.

![[Screenshot 2024-10-28 at 10.57.29.png]]

- improvements done by multi leader configuration over single leader 
	- users that are geographically far from the single leader will have to face network latency between their reads and writes. If we were using multi leader then the client could then their request to the nearest leader and the change is applied to other leaders asynchronously.
	- A single leader means a single point of failure, if the single leader where to go down then it would disrupt the entire application
- the biggest downside to multi leader replication is that we could have two clients concurrently changing the value of a record in two different data centers. 
- autoincrementing keys, triggers, and integrity constraints can be problematic in multi leader configuration. These problems are why mutli leader configuration should be avoided if possible

### Handling write conflicts 
![[Screenshot 2024-10-28 at 11.07.49.png]]
- user 1 updates the title from a to b and user 2 updates the title from a to c
- they are both recorded in their local leader database. This means two database has two different values for the same record. 
- when the change is applied asynchronously to both of them then it cannot happen because leader 1 tries to change title from A to B but the database has the title C in the record and same goes for leader 2

#### sync vs async conflict detection
- single sync replication, when one user is writing to the database the second write is made to wait for the first to complete 
- in async replication with multi leader the conflict is only detected when the changes are applied asynchronously to other leaders. 
- we could in multi leader use sync approach where we wait for the leader to replicate the value to all other leaders but his would lose the purpose of using multi leader config which is used to accept writes independently. 

#### conflict avoidance 
- not resolve but to avoid conflict
- all the writes for a particular record be routed to a specific leader. 
- this becomes useless if the user write request gets routed to another leader because of there was an issue in the home data center of the user. 

#### converging towards a consistent state
- give each write a unique ID, pick the write with the highest ID as the winner and throw away the others 
- merge all the inconsistent values from different leaders into a single value 
- preserve the conflict in a custom data structure and then write separate application code to resole the conflict in the background.

#### custom conflict resolution logic
- most multi-leader replication tools let you write custom conflict resolution logic for the conflict. 
	- On write: as soon as the system detects the conflict, it can invoke a conflict handler. 
	- On read: all the conflicted writes are stored together such that when the user reads that record they will be prompted to choose which replicated data they want to choose to be stored permanently. CouchDB uses this approach.

### Multi-leader replication topologies
- replication topology describes the how writes are propagated from one node to another. 
![[Screenshot 2024-10-28 at 11.24.46.png]]

- The most generally used topology is the all to all topology where the write replication is done from one node to all other nodes throughout the data system. 

- in circular and star topology, a write may pass through several nodes before the replication is applied to all nodes. 
- Nodes have to pass data from one node to another node. 
- We also have to make sure that the node that initially generated the replication request does not continue to pass the data on such that there is no loop
- each node has a unique identifier and the replication log needs to have the unique identifier, if the replication log identifier != node identifier then forward the log else do not forward the log.
- both circular and star has a single point of failure, 


## LeaderLess replication
- The client sends their write request to all the replicas or it sends to a coordiantor node which does the same things on behalf of the client 
- The coordinator node unlike a leader node does not maintain a strict ordering
- This approach was made popular by DynamoDB. Cassandra also uses this appraoch 

### quorum writes in leaderless replica
- a single client write is send to all the replicas
![[Screenshot 2024-10-30 at 07.51.29.png]]
- user 1234 sends writes to all 3 replicas
- we say the write was successful if 2 out of the 3 replicas send a ok response of the write request. 
- the replica that was down when comes back online will have some missing data that was written to other replicas during its downtime. If the client used this replica to read data then it would get stale data 
- Instead a single read request of a user send to all the replicas like the write request such that we accept the latest read request. 
- We need to make sure that the failed node needs to eventually catch up to other replicas. These two mechanisms are used in Dynamo-style database:
	- read repair -> when read request is sent in parallel to all replica nodes then it will send all versions of the data available. The client sees that a node has a stale value and writes the newer value back to the replica. This is good for values that are read frequently.
	- Anti-entropy proess -> Running a background process to check the staleness of data. 
- why is write called successful if only 2 out of 3 replicas acknowledge the request? why not all 3?
- becuase that means at most 1 replica can be stale and if we read data from any 2 replicas than at least one of the replica will have up to date value.
- if there are n nodes and and every write must by confirmed by w replicas and we query r nodes for each read then as long as w + r > n, we will get the most up to date value
- reads (r) and writes (w) that obey this run is called quorum reads and writes.
- common choice for n would be a odd number and the value of w = r would be (n + 1) / 2 (rounded up)
- This rule works because there will only be one successful overlapping node in both read and write request. 
- If fewer than required w and r nodes are available, writes and reads return error. 
- even in the quorum rule w + r > n there will be case when we get stale data back: 
	- if sloppy quorum is used (when writes are placed on a different replicas of our n nodes)
	- if a write and a read happens concurrently
	- if the node carrying the up to date value is down 
- we need to monitor that the replicas are returning up to date data 
- in leader based replica nodes can be found behind by checking the replication log and the current position of the leader node 
### last write wins (discard concurrent writes)

### The happens before relationship
- when we have two clients A and B here are the 3 possible outcomes of a request 
	- either A's request happens before B's
	- either B's request happens before A's 
	- both A and B are concurrent and do not depend on the value modified by one other
- We need to know if there is a happens before relationship because we need to overwrite the value written by the previous request. But if the request are concurrent then we need to solve the conflict that arises
- In distributed systems, two request are concurrent to one other if they are both unaware of each other
- If two request are concurrent then one approach would be to merge the results of both the users 
### Version vector
- the above technique of merging the concurrent values for a key is a good strategy for a single replica server
- For multi replica servers we have a technique called version vector and version clock