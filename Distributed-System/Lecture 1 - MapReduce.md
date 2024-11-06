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


## Main goal using distributed system 
Our main goal when using distributed system is to create an infrastructure that other applications can use. This infrastructure must be capable of hiding or abstracting away the distributed part of the infrastructure and make it seem like it is non-distributed. 
