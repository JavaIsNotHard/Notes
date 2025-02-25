- Globally distributed database 

- replication in multiple datacenters 
- fault-tolerant through replication
- paxos handles each shard between different datacenters
- sharding of data within data center
- sharding is done for parallel processing of request by responding to request from different data center separated geographically

- each paxos group representing a shard has a leader 
- all writes goes through the leader 
- paxos is same as raft which means it will have local logs stored that stores all operations for consistency between servers 
- multiple datacenter for fault-tolerance 
- have copies of data near the client 

clients are webserver that the actual web browsers facing the user end connect to whenever they are using any google services 

- read-write txn 
	- spanner uses both 2 phase locking and 2 phase commit for read-write txn 
- read-only txn
	- should maintain serializability
	- should maintain external consistency
	- why not return the latest version of the data 
		- does not maintain the serializable order of the txns 
	- so what is the solution to this problem?
		- one approach is snapshot islolation
			- read-write txn will have timestamp as follows 
				- TS = Commit time of the txn
			- read-read txn will have timestamp as follows
				- TS = Start time of the txn
			- each replica has a multi-version database 
				- each write request will create a new version of the same data object without overriding the previous version of the data
				- for a read operation will it return the version of the data object that is the highest but still less than the current timestamp of the read-only txn

- since reads are done through local replica for better performance, there can be cases where the current replica was in the minority during the paxos consensus protocol and hence didn't see most updates
- spanner deals with stale data in read-only txn that read from its local replica by using something called a safe time which does the following
	- each replica tracks the max timestamp at which the replica is upto date 
	- if the current timestamp of the txn is less than the most up-to-date timestamp then the replica makes the client wait until it gets all the up-to-date log records and then returns the result to the client
- how does spanner deal with clock synchronization between geographically distributed replicas?
