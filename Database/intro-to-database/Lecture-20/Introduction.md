## Parallel database systems 
- fine grain parallel systems -> make use of large number of processors which are that fast.
- coarse grain parallel systems -> make use of small no of processors that are extremely fast 

- massively parallel system have their own set of memory and even their own set of disk
- mainly used to query dataset of large sizes (petabytes of data) or to handle large number of transaction per time.
- nodes i.e set of processors, memory and disk, are placed closer to each other inside a datacenter. we can have data center distributed globally but that would fall into distributed database category.

- decision-support queries 

- performance of parallel system is measured in terms of throughput (number of task that can be completed in a given time range) and response time (amount of time required to process the task and return the result back to the client)
- throughput can be increased by increasing the number of parallel transactions 
- both throughput and response time can be increased by performing the subtasks of each transaction in parallel. 

- two important issues in parallelism include speedup and scaleup
- running a given task in less time by increasing the degree of parallelism is speedup
- handling larger task in the same time range by increasing the degree of parallelism is scaleup

- the goal is to make the time taken to complete a task
- inversely proportional to the number of processors and disks allocated.  


## Linear vs sublinear speedup
- execution time of a task on a large machine is T(large), execution time of a task on a smaller machine is T(small)
- the speedup is defined by T(small)/T(large)
- the parallel system is said to demonstrate linear speed up if we increase the resources processor, memory, disk) by N then the speedup (T(small)/T(large)) is also N.
- if the speedup is below N then we say that the speedup is sublinear


## linear vs sublinear scaleup
- let Q be a task and let Qn be a task N times larger then Q.
- Let Ts be the time taken by machine Ms to complete no of task Q.
- let Tl be the time taken by parallel machine Ml to complete Qn number of tasks 
- the scaleup is also defined by Ts/Tl
- the system demonstrates linear scaleup if Tl = Ts i.e in the same time range we could complete N times the task as Q.
- the system demonstrates sublinear scaleup if Tl < Ts i.e in less the time we could complete N times more task even if we increase the parallelism by only N

- scaleup is usually a more important metric of parallel system.


## shared memory architecture
- before, processors were connected to memory via a common bus with all processors sharing a single bus
- now all processors have uniform access to the memory at the same time.
- each processor can also access memory associated with other processors.
- this architecture is known as non uniform memory architecture (NUMA)

- this requires high speed interconnection between cores and between processors which means the number of cores/processors that can be interconnected is limited. 
- instead using large sized cache is more important than using more interconnected cores/processors.
- large cache size reduces the number of access to main memory.
- L1 and L2 cache lines are local to each processors whereas L3 cache is shared among the processors.

## cache coherence 
- an update done by one core is not visible to another core because the other reads the cached version of the data item 
- this means whenever an update occurs for a data item then we must invalidate all the cache that includes that data item

- the invalidation is done lazy by modern processors by sending invalidation message to all processor cores.
- the time required to send a invalidation message and send a invalidation message produces a lag
- modern processors supports memory barrier instructions for x86 architecture
	- store barrier instruction -> forces all processors to wait until invalidation message is sent to all caches for all the updates done before this sfence instruction
	- load barrier instruction -> makes sure all invalidation messages have been applied before any further load barrier instruction