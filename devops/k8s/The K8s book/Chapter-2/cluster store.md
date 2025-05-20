A cluster store is another component of the [[control node]], this is the only component in the control plane that is stateful
the cluster store is implemented using etcd which is a highly available distributed key value store 
typically etcd runs in the same node as the [[API server]] which means that for each node there is typically a single etcd instance
In production, we have multiple control plane nodes which means we have multiple etcd instance. suppose we have 3 control nodes then that means we have 3 etcd instance. The number of replica is typically an odd number to satisfy the quorum rule such that in the case of split brain problem we can still get a majority vote i.e if 1 node is down but 2 nodes are up, the 2 nodes can still take request from clients 

Another approach is to separate the etcd service as its own cluster of machines from the control plane node. This solves the problem of SPOF and moves the bottleneck of the cluster store away from the control node 

High availability does not correspond to better recoverability which means we need to implement mechanisms to ensure we can recover from failures using techniques such as WAL 

if split brain occurs then the control node moves to read only mode preventing any updates from reaching the nodes. 

ETCD handles consensus problem using the RAFT protocol