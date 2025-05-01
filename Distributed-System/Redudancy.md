Redundancy also referred to as replication helps achieve better availability
only some forms of redundancy actually improves availability, four prerequisites are:
1. the cost of adding redundancy must not cost more availability than it adds 
2. the system must be able to detect which of the redundant components are healthy and which are not 
3. the system must be able to operate in degraded mode 
4. the system must be able to return to fully redundant mode 

let's example all the prerequisites with an example,
a load balancer is used in a redundant system but the load balancer also increases the system's complexity and therefore the system can fail in multiple ways but the benefits it provides always outweighs the risks. this satisfies the first condition

the load balancer can detect faulty redundant servers using health checks. this satisfies the second condition

the load balancer also removes the faulty node from the system assuming that the rest of the system is capable of handling the request even if one of the node fails hence the system is essentially operating in degraded mode. this satisfies the third condition

the system must not only operate in only degraded mode and needs to be able to recover properly otherwise there wouldn't be enough server to handle the load and the whole system will go down. masking node failures can be done through replication of nodes i.e when we bring out a new node the node must be consistent with the other services which can only be achieved using replication. This is the fourth condition

## Correlation

Redundancy is only helpful if the redundant nodes can't fail for the same reason i.e when failures are not related 
