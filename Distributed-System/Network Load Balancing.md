
we can scale application horizontally when we have pushed the state information to dedicated servers such as databases and CDNs and blob storage 

scaling out a stateless application is easier than scaling out a stateful application like a database since it needs to replicate state and thus requires some form of coordination

clients are decoupled from the server hence they don't need to know their individual addresses so the number of servers behind the load balancer can increase or decrease transparently

and since any arbitrary server can have user request, the load balancer can detect and remove the faulty ones

availability of a system is the percentage of time it's capable of serving requests and doing useful work

how do you calculate the availability of a server?
the probability that they are all unavailable is the product of the server's failure rates
we then subtract 1 from the product to determine the theoretical availability of the application
i.e if we have two servers each with an availability of 99% then 
1 - (0.01 * 0.01) = 0.9999 ~= 99.99%

## features offered by load balancer 

1. load balancing
	different algorithms are used for load balancing user requests which includes
	- round-robin
	- consistent hashing
	- load-aware load balancing
		balancing by load is hard
		the load balancer could periodically sample a dedicated local endpoint exposed by each server that returns a measure of how busy the server is
		but constant querying servers can be costly, which can be reduced by caching responses
2. service discovery
		mechanism the load balancer uses to discover the pool of servers it can route the request to
		we can either use a static configuration file where we add the IP-address of the servers which is hard 
		another way is to use a fault-tolerant coordination service like etcd or zookeeper where servers auto registers themselves to the coordination service with a TTL 
		this is a key feature that many cloud providers provide which is called autoscaling
3. health checks
health checks are used to detect when a server can no longer serve requests and needs to be removed from the pool
there are two types which includes
- passive
- active
passive is performed as the load balancer routes incoming requests to the servers downstream
if the server isn't reachable the request times out or the server returns a 500 status code then way the load balancer can remove this server from the pool

in active health check, the downstream server exposes a health endpoint that the load balancer can query periodically to infer the server's health
if the endpoint either returns 200 or 5xx status code if they server is overloaded
if the server endpoint times out, it also counts as error

the endpoint handler can compare the local metrics such as CPU usage, memory consumption and more with a configurable threshold to detect faulty servers

if a threshold is misconfigured or the health check has a bug, all the servers behind the load balancer may fail the health check and hence all the servers will be removed from the pool bringing the application down
but in practice, the load balacner is smart enough to detect large to be unhealthy and consider the health check itself to be unreliable

we can also implement a background process or thread called a watchdog that periodically checks and monitors the server's health
if the metric breaches a specific threshold for some time then the watchdog considers the server degraded and deliberately crashes or restarts itself
if the server restarts when it is degraded then it can avoid performance impact caused by sending request to this degraded server


## TCP load balancing

if the load in the load balancer is high then we can make the request bypass the load balancer and directly to the server using a mechanism called direct server return

A network load balancer can be built using commodity machines and scaled out using a combination of anycast and ecmp

How?

multiple load balancer machines share the same anycast IP address, this means that all the load balancer announces to the edge router that it is able to serve traffic for the same address
all the load balancer have the same BGP weight hence it uses ECMP to determine which machine to send the request to 
consistent hashing is used to ensure that packets of a specific connection are generally routed to the same load balancer instance

Although load balancing connection at the TCP level is very fast, the load balacner is just shuffling bytes without knowing what they actually. mean


Having a single Load balancer taking all the request creates a problem of single point of failure i.e if the load balancer is down then the application server behind is also becomes unreachable hence they become down too 

instead we can add the load balancing feature on the client side using the sidecar pattern
here the machine running the client application will host the load balancing application as well which isolates failure of load balancer to only a single client and not the entire application server
this approach is called as service mesh
the drawback of this approach is that now we need a control plane to manage all the sidecars
