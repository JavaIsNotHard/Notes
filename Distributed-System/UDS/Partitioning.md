split large data into small partitions or shards that fit into individual nodes

the gateway service is usually in charge of routing request to the nodes responsible for the partition
the mapping between the partition and nodes is maintained by a fault-tolerant coordination service like etcd or Zookeeper

types of partition
1. range partition
2. hash partition
		1. consistent hashing
		a hash function randomly maps both the partition identifiers and keys onto a circle 



what is command line argument?

command line argument is a feature that helps user to send arguments to the program through the command line