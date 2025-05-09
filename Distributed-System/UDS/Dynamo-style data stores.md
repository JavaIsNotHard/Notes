provides eventual consistency
highly available key-value store

replicas can accept both reads and write request
when a client sends a write request, it sends the request to all N replicas in parallel 
waits for acknowledgement from just W replicas (write quorum)
similarly if a client wants to read an entry from the data, it sends request to all replicas but waits for just R replicas (read quorum) and returns the most recent entry to the client

write quorum (W) is a number greater than half the no of replicas
the same goes for read quorum 
for a system to be consistent we must satisfy the W + R > N condition
for a read heavy workload, we can reduce the value of R and improve the read throughput but this would make writes slower and less available because we need to increase the value of W in order to satisfy the W + R > N condition

we can also configure W and R both to be small for maximum performance at the expense of consistency ( W + R < N)

this is called as **quorum replication** 

one problem with this approach is that the write request sent to a replica may never make it to the destination
this means the replica will not converge no matter how long it waits

to make sure that the replicas converge, additional mechanisms are used such as read-repair and replica synchronization

hence quorum replication can be thought of as a best-effort broadcast combined with anti-entropy mechanisms to ensure that all changes propagate to all replicas

does quorum replicate by exchanging messages with the replicas?

read-repair

replica synchronization -> replicas communicate periodically in the background to identify and repair inconsistency