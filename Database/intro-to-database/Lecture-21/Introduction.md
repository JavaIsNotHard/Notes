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
	- range partition -> example, let data items with id (1 - 100) be set at node 1, id (101 - 200) be set to node 2 and so on

## Dealing with skews in partition
- skews in partition occurs when there is imbalance in the distribution of data across the partition
- there are various techniques that can be used to correct this imbalance between the partition. Some techniques include:
	- balanced range-partitioning vector
		- before partitioning a relation, we sort the relation based on the partition key
		- then for every 1/n of the relation has been read then the value of the partition attribute of the next tuple of the same relation is added to the partition vector 
		- this is done until we scan the entire relation and keep adding the 1/n the item of the relation to the partition vector
		- this method is static i.e the partitioning is done is some later point when operations are done happening in the relation
	- virtual node partitioning
		- we create virtual nodes which are greater in number compared to real node number
		- the number of virtual nodes can be any and is typically not defined beforehand unlike the number of real nodes which has to be defined beforehand
		- the partition for the virtual node is determined using the formula ((i - 1) mod n) + 1 where n = no of real node & i = ith virtual node
		- another approach is for the virtual node to keep track of the number of tuples it is managing and the load on the virtual node. Then an algorithm can be defined such that based on these two parameters, we can distribute the load more evenly
	- dynamic partitioning:
		- split a virtual node into two when the load on a particular virtual node exceeds a certain threshold
		- similar to splitting of B+tree when it overfulls
		- 

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
