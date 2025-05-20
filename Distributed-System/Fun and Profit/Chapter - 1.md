## Distributed systems at a high level 

what new things did I learn from this chapter?

the things that we want to achieve using distributed computing i.e instead of upgrading our single computer's hardware we distribute the computing between multiple computers. 

upgrading the hardware has its own limitation which is the physical limitation on how much we can upgrade the system like how much more RAM or how much more storage and so on 

the performance gap between high-end and commodity hardware decreases with cluster size assuming a uniform memory access pattern across all nodes. here uniform memory access means that each node in the cluster is doing equal amount of work and the work is evenly distributed inside the cluster

but just increasing the number of commodity hardware will not be proprortional to performance because there are various factors that affects the performance of the system when there are multiple independent machines such as data needing to be copied betwen all the nodes in the server, computation has to coordinated between the servers and so on 

the things that we can to achieve with distributed system includes the following
1. scalability
	scalability refers to the capacity of the system to grow as the input size increases for the system or the capacity of the system to tolerant growth. here growth can be anything ranging from number of workers in the organization, number of nodes of the system, number of geographically distributed data centers and more. scalability ensures that increasing the numbers will not degrade the performance of the system rather scalability aims to improve the performance
2. performance 
3. availability
4. fault tolerance