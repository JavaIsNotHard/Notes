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



## NOTE: transaction coordinator and replica leaders perform separate tasks
