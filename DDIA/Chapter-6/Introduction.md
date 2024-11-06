## What is partitioning 

### Partitioning and replication in the same infrastructure 

### Partition based on key value
#### Partition based on key range 
#### Partition based on hash value 

#### Skewed workload and relieving hotspots


### Partition and secondary index 
#### Document based secondary partition
#### Item based secondary partition


## Rebalancing of partition
### mod N
### fixed sized partition  
There is a fixed size of partition defined beforehand, for example 1000 partition for 10 nodes which would mean 100 partition for each node. There is no guarantee that the no of partition in each node is the same or all node. 
This means we can utilize hardware mismatch by making the powerful nodes to take more load in comparison to other nodes.
This appraoch has the flaw that selecting the no of partition to be distributed over all node is a hard thing to predict. If the no of partioin are too high then rebalancing and recovery from failure is expensive but if the no is too small then it will incur overhead in performance.
### Dynamic partition 
### Partitioning proportional to the nodes 
Both fixed size and dynamic partition are proportional to the size of the dataset. 
in fixed size, as the datsset increses the cluster of nodes cannot handle it so we need to bring in new node and redistribute the partition among the node again. 
in dynamic partition, as the dataset increases or decreases a threshold of the partition value then we either shrink or merge the partition

In this approach the parition are proportional to the no of nodes. 
Each node has a fixed no of partition

## Request routing 
- routing tier as a middle man 
- round robin load balancer 
- clients be aware of the partitions and the assigment of partition
- ZooKeeper for service discovery
