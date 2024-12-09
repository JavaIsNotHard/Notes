## Parallel and distributed storage

## Data partitioning 
- creating groups of dataset inside a single database. 
- or dividing a single database into multiple groups or otherwise known as partitions 
- in database system we partition tuples as the primary dataset which means that each tuple will reside in a single partition throughout the system. This partition then can be replicated in various nodes
- A single node can have multiple partition and we use various algorithms to determine which partition of which node to use to insert new values (tuples)

- two types of partition
	- horizontal partition -> partition the dataset based on rows
	- vertical partition -> partition the dataset based on column

- lets suppose we have N1, N2, N3, .... Nn nodes in the system.
- partition strategies
	- round robin -> use the forumla N((i - 1) mod n) + 1 where i is the ith item in the relation
	- hash partition -> use a hash function that computes value ranging from {1, 2, ... n} then assign the tuple to partition number N which is the value from the hash function
	- range partition -> 

## Parallel index 
- local index -> each node will have their own local index, each partition will have their own index
- global index -> all nodes will have a common index 

## global primary index 
- a global index on the attributes on which the tuples of the relation are partitioned
- each tuple will be partitioned based on values of a single attribute or a composite attribute
- a global index on attribute K is created by creating a local index on K on each partition

- for example, we have a student relation partitioned on student_ID,
- we also have a global index on student_ID
- we also need a local index on student_ID

## global secondary index


## Decentralized coordinator 
- some server that handles all the communication with various database partition 
- in the time of commit the coordinator can ask all the partition whether it is safe to commit or not. if all the nodes agree on the commit then  the coordinator will send commit request to all node

- another approach is to use a middleware between the query server and the partition which does the same thing 
- it also contains a lock manager which keeps track of all the locks held for various partition 
