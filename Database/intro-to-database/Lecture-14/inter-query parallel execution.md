having multiple workers per operator is not going to increase the performance everytime if the disk is the main bottleneck

following are the reason that can bottleneck the disk when we have multiple worker executing in parallel at the same time:
1. all workers compete for I/O : increase in read/write throughput on disk
2. random access pattern: different worker may read different chunks or data addresses or write to random location which is bad for spinning disks 
3. buffer cache contention: since workers first query the buffer pool before going to disk, thrashing (excessive change in buffer pool items) becomes common 


this is why we need [[IO parallelism]]
