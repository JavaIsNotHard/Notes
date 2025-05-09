## What is Distributed System?
Infrastructure that needs more than one computer connected to each other to get a job done.
Because of the nature of distributed system all devices needs to be spread out physically in different locations. 

## Why not to use distributed system? 
When the problem can be solve using a single computer then there is no need to add in the complexity of a distributed system
Basically we need to try everything out before we start using distributed system 

## Now why to use distributed system?
There are many important reasons why distributed architecture is fancied: 
1. Parallelism 
2. Fault tolerance 
3. Physical Reason -> This can be confusing so let's explain it. Suppose we have a bank that has many branches that are spread across the country. Each branch has to find some way to communicate with other branches. This is the nature of distributed system and can be used in such scenarios.
4. Security -> When computation are divided into multiple isolated computers then the the failure of security breach of one isolated computer cannot affect the performance of the overall system.

## Why distributed system is hard? 
1. Concurrency 
2. Partial Failure 
3. Performance 

## Types of distributed infrastructure
- storage 
- communication 
- computation 

## Main goal using distributed system 
- Our main goal when using distributed system is to create an infrastructure that other applications can use. 
- This infrastructure must be capable of hiding or abstracting away the distributed part of the infrastructure and make it seem like it is non-distributed. (Abstraction)
- For example, for a storage system we could abstract away the distributed nature and make it seems like an ordinary file system that has trivial operations such as read(), write() and more 

## Topics in distributed system: 

### Implementation 
- Tools that are used to build such distributed systems 
- this includes tools like RPC (remote procedure calls), threads, concurrency control and more 
- RPC is used to mask the fact that we are trying to communicate through an unreliable network 
- Threads are a way to harness multicore computers and also a way to structure concurrent operation 


### Performance 
- Scalability -> if we add 2x the computer then we should get 2x the throughput 
- Just because we added N times the computer does not guarantee the solution
	- as we add more computation, the bottleneck will shift from one computation service to another 
	- some services will get more load than another service 
	- slowest of N latency makes the system as slow as the slowest of the N nodes in the system


## Fault tolerance 
- single computers have high fault tolerance than distributed ones 
- in a system with thousands of computer then there will definitely be some nodes that will fail
- the system must be designed to overcome and hide the failure to the application programmers using the infrastructure 
	- notions of what it means to be fault tolerant:
	- availability -> under "certain" kinds of failure the system will keep operating 
	- recoverability -> if a failure occurs then the system will stop responding to request and then wait for someone or something to fix the problem before continuing to operate
	- a good available system will be able to recover as well 
	- tools for fault tolerance 
		- non voliate storage like hard drive or SSD for logging the state of the system to recover from failure when the power comes back on 
			- but NV storage are expensive to update so better to use techniques that avoid writing to NV storage 
		- another technique is replication where we replicate the NV storage 
		

### Consistency 
- what does consistency mean in distributed environment 
- strong consistency vs weak consistency 


## Map Reduce 
- programming model to compute large data sets in distributed manner and are executed in large cluster of commodity machines or computing machines 
- this provides with abstraction of map and reduce function where both functions have no idea of the hidden complexity of parallelism, fault tolerance and more 

- ### Components of Map Reduce model
	- user program:
		- forks itself into master and workers 
	- master user program (forked from the user program): 
		- splits the input data into M pieces where each piece is of 16 to 64 MB  in size 
		- schedule the map workers and notify the reduce workers 
	- map workers 
	- reduce workers 
	- Map function 
	- Reduce function
	- Distributed file system 

	- takes in set of key, value pairs and outputs a set of key, value pair 
	- there are two functions, Map & Reduce 
	- Both are user defined, the map function takes input pair and produces intermediate key/value pairs, the library groups together key/value pair with the same key and passes them to the reduce function
	- The reduce function takes in the intermediate key and a set of values as input and typically just zero or one output value is produced per reduce invocation 
	- map -> (k1, v1) -> list(k2, v2)
	- reduce -> (k2, list(v2)) -> list(v2)


	- the map invocation are distributed across multiple machines by partitioning the input data set into M splits 
	- reduce invocation are distributed by partitioning the intermediate key space into R pieces using a partitioning function (hash(key) mod R)

- user submits job to a scheduling system 
- each job consists of a set of tasks 
- each task is scheduled to available machine within the cluster 

![[Screenshot 2025-01-09 at 2.18.57 PM.png|700]]

- the user program first splits the input data into M pieces typically 16 to 64 MB each and then starts copies of the program on a cluster of machines 

- one of the copies of the program acts as a master and the others act as workers. There are M map tasks and R reduce tasks. Master program picks one idle worker program and assigns it a map task or a reduce task 

- the worker which is assigned to the map task reads the input split and parses key/value pairs out of the input data and passes each key/value pair into the user defined map function. The map function produces an intermediate key/value pairs which are buffered in memory of the map worker 

- the buffered intermediate pairs are periodically written on disk and partitioned into R regions using the partitioning function (hash(key) mod R). The location of these pairs are passed back to the master who is responsible for forwarding these location to the reduce workers so the mapper sends the location of these output intermediate file location to the master node which then informs the reduce worker about the location

- when the reducer worker are notified about the location of these data then it uses remote procedure call to read data from the local file system of the map worker. when the reduce worker has read all the intermediate tasks from the disk then it sorts the intermediate task by key, groups together pairs of the same key.

- the reduce worker iterates through the sorted intermediate data and for each unique intermediate key encountered, it passes the key and the set of intermediate value to the reduce function. The output of the reduce function is appended to a final output file for this reduce partition 

- After completion of all map and reduce tasks, the output is available in R output files 
- These output files are either read by another MapReduce job or is used by a distributed application that is able to deal with input that is partitioned into multiple files 


### Master program data structure 

- for each map and reduce task, it stores the state associated with it such as idle, in-progress and completed and the identity of the worker machine 
- keeps track of the location of each R file regions in the local file system of the map worker 

### Fault Tolerance 
- worker failure 
	- the master pings the worker periodically 
	- if no response is given after certain amount of time then the worker is marked as failed by the master 
	- any map task completed by the failed worker is reset back to its idle state and now is eligible for scheduling by other workers 
	- any map task or reduce task in progress on a failed worker is also reset back to its idle state and is eligible for scheduling by other workers 

	- completed map task (not reduce task) are made to re-execute because their output is stored in local disk of a failed machine and therefore is inaccessible
	- reduce task's output are placed on global disk storage
	
- master failure 
	- make the master add checkpoint of its current state such that new master copy will start from the previous checkpoint
	
- semantics in the presence of failure 
	- the distributed implementation of map and reduce operations perform the same as a non-faulting sequential execution of those operation
	- this is achieve by using atomic commits of map and reduce task 

