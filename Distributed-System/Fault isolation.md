there are some faults that cannot be tolerated with redundancy alone because of their high degree of correlation such as poison pill and noisy neighbour   

poison pill -> if there is a bug in the application code then no matter how many redundant nodes we deployed, if the bug is triggered then it can bring the entire system down

noisy neighbour -> a client request takes a lot of resource making other client wait for their request to be served 

the blast radius i.e the affected areas is the entire application here. we can reduce this by partitioning the user request itself i.e a particular user will only be requesting a particular server which reduces the affect of the faults to that server itself and does not propagate to other servers

this is known as the bulkhead pattern 

## Shuffle sharding 

the problem with the previous pattern is that the unlucky non-faulty clients are also affected because they can also be routed to the same faulty server
to solve this issue we can use the shuffle sharding technique which does the following
1. it divides the partition in the bulkhead pattern into virtual partitions i.e random subset of a partition
2. suppose we have 10 instances of a server then how many combinations of 2 virtual instances can we create out of these 10 instances?
		C(n, k) = n!/k!(n-k)! i.e we have 45 ways we can select 2 virtual instances out of the 10 total instances 
3. each user gets assigned 2 out of these 10 partitions supppose User A -> partition 1 and partition 7, User B -> partition 2 and partition 5 and such


## Cellular architecture


