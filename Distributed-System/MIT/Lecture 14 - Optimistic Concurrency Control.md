- FaRM is a protocol that provides distributed transactions with consistency, availability and performance 
- FaRM leverages two hardware trends
	- high speed networks for better RDMA 
	- inexpensive non-volatile DRAM by battery backing up the DRAM and writing the contents to SSD in case of power failure 

- FaRM uses one-sided RDMA operations which does the following
	- instead of sending RPC like messages to remote CPU for processing read and write request it directly accesses memory location without involving the CPU for any type of processing
	- write request are sent without interrupting the CPU from its current operations 
- one-sided as in only one machine is actively involved in the operation, which in our case is the operation requesting machine
- using one-sided RDMA, FaRM avoid the CPU overhead of remote request
- coordinators use one-sided RDMA when logging records to non-volatile write ahead log at the replica

- because FaRM uses one-sided RDMA, it needs a new failure-recovery protocol
- if a machine fails, other machine might will send one-sided RDMA request which would return an undefined result
- FaRM cannot rely on the server to reject incoming request when their lease expires because all incoming request are acknowledged by the NIC and NIC have no concept of leases
- for this reason a concept called precise membership is required which does the following
	- makes sure that all machines agree on the same membership such that no machines send request to machines that are no longer in the configuration
- FaRM also uses the concept of reservation during the 2 phase commit protocol which does the following
	- since coordinator directly add records to the logs of all the participating nodes, it doesn't know the resources that are available to perform those task. 
	- if the request was sent to CPU instead, the CPU would first check the local resources available and then decide to process a prepare record or refuse the prepare record 
	- but since CPU is not used, the coordinator must reserve space for logs ahead of time to guarantee progress and avoid failure
- FaRM distributed recovery to evenly across the cluster and also it parallelizes recovery across cores in each machine 
- it also allows transactions to execute in parallel with recovery by using these two optimziations
	- rather than waiting for the the failure recovery, a lock is release on failure and given to another txn
	- txns that are unaffected by failure can continue executing without blocking
- fast failure detection due to fast network within the datacenter to exchange frequent heartbeat messages




- uses the concept of RDMA (remote direct memory access)
- doesn't deal with geographically distributed servers like spanner but only deals with replicas of a single data center
- spanner's main bottleneck was the speed of light through which packet traveled through geographically separated data center for synchronization of time
- FaRM's main bottleneck is the speed of the CPU
- uses zookeeper as configuration manager
- data is sharded based on some key and replicated in various primary and backup servers across the data center 

### concurrency control
- pessimistic concurrency control
	- uses locking, mainly 2PL where locks are acquired until the transaction commits 
- optimistic concurrency control
	- we let all the reads and writes happen without acquiring any lock and when it is time to commit we validate the reads and writes and make sure that those reads and writes are serializable with other transaction that was executing concurrently with the current transaction
	- reads require no locking and can be read directly from the DB server
	- writes on the other hand are buffered locally until the time of commit
	- during the commit phase, a validation protocol is started and all the reads and writes are checked for serializability
	- if there are any conflicts then we abort the txn else we commit the txn

### FaRM API 
- FaRM does not support traditional SQL type queries and only expose basic read and write API 
- FaRM is basically a NoSQL database with transaction support

```
txCreate()
o = txRead(OID)
o.f += 1
txWrite(OID, o)
ok = txCommit()
```

- OID are compound identifier for object which includes
	- region: all the memory of all servers are separated by regions and the configuration manager track which server tracks which region number and the client can lookup the currently primary and backup for the given region number. the client uses the region # to get the primary and backup to talk to 
	- address: memory address within the region. the client passes the address to the RDMA manager to read at a particular address

### server memory configurartion
- farm provides a global address space which consists of all memory region of all the servers inside farm config
- the global address space consists of 2 GB regions which are replicated on one leader and f backups
- a configuration manager such as zookeeper creates a mapping of region identifier to its primary and backup servers
- objects are always read from the primary region. the object is read using local memory access if it is present in local memory else the object is read from other server using a one-sided RDMA
- the region identifier are fetched from the CM and cached locally by other servers 
- each region contains lock bit as the first entry followed by version number and then the rest of the entry contains data

- each server contains a ring buffer which is a FIFO queue
- when other servers need to write then it appends a new log record to this ring buffer through the use of RDMA
- the writes are acknowledged by the NIC bypassing the receiving server's CPU


## Distributed transaction and replication
- during execution phase, transactions use one-sided RDMA to read object and buffer writes locally
- FaRM during the commit step:
	- LOCK phase
		- the transaction writes LOCK record to all primary machines where the corresponding object resides 
		- the LOCK record contains the version number of the object that was read during the execution phase, the object ID and the new value to the primary log, it also contain a list of regions that the current object resides on 
		- the primaries will then actively poll its log for any new record, on seeing the arrival of a LOCK record it will try to acquire lock for all objects with the version number specified in the log using compare and swap operation
		- if the operation succeeds then it returns a message reporting whether all lock were successfully acquired
		- locking phase can fail if the latest version number of the object changes since the transaction last read or if a lock is already acquired by another transaction concurrently
		- if it fails then it aborts the transaction in the primary and writes abort log record to all backup servers
		- why use compare and swap? primary can be multithreaded program running in different CPU and each primary process will have an active queue processing log request from the coordinator. this is why the compare and swap is used to make sure that two process running concurrently changes the same data object atomically without causing any data races
	- Validate: 
		- this phase is used for read validation
		- the coordinator reads all the objects from all the primaries using one-sided RDMA and then compares their version number
		- if any version number as changed then the coordinator aborts the transaction
	- Commit backups
		- contains the same information as the LOCK record
		- writes the record to all backup server's log
		- waits for ACK from the NIC 
	- Commit primary: 
		- this step is necessary to make sure that the coordinator knows that all primary server knows that the coordinator committed the transaction
		- for this, the coordinator writes a commit-primary log record through RDMA directly to the log of the primary
		- the coordinator waits for at least one hardware ACK from the primary
		- the primary processes this record by updating the object in place, incrementing their version and unlocking all the locks which exposes the writes committed by the transaction
	- Truncate: 
		- finally the coordinate removes all the log records corresponding to the transaction from all primary and backup servers



## NOTE: transaction coordinator and replica leaders perform separate tasks
