servers that forward incoming traffic to different downstream servers such that different downstream servers are responding to different request which avoids hotspot in user request

service discovery in gateway server which auto discovers new downstream server when added 

![[Pasted image 20251208152034.png | 200]]

Elastic load balancer
managed load balancer
managed in the sense that they are managed by aws and we don't have to configure them manually
aws also guarantees that the load balancer is never down, it also takes care of the maintainability and high availability

it costs less to setup our own load balancer in the cloud but it takes more effort to configure them
it can be integrated with many services in the aws ecosystem

health checks
for the load balancer to send traffic to healthy or up servers, it needs a list of servers that are actually up, this list is usually created by sending requests to a health check endpoint in downstream server whose responsibility is to respond with whether the server is functioning correctly or not

here are the features of ELB in AWS:
1. listeners and target groups
	1. in the old days (classic LB), you registered instances directly to the Load Balancer, now we have an abstraction layer as follows:
		1. listener: 
		2. rule: if the path match then send to target group X
		3. target group: a logical group of targets (EC2 instances, IP address or lambda functions)
2. Cross zone load balancing: 
	1. Load balancing between different AZ such such as following:
		1. you have 2 instances in zone A and 8 instances in zone B
		2. without cross zone : the LB node in zone A sends 50% of traffic to its 2 instances (overloading them) and send other 50% of its traffic to zone B's 8 instances (underutilizing them)
		3. with cross zone: LB node talk to each other, distributing traffic evenly across al 10 instances regardless of which zone they are in
3. sticky session: creates a session for a new request to a particular server for a particular duration, when the the same user resends another request, it forwards the request to the same server
4. connection draining: server A needs patching so you remove server A. if you don't use connection draining then ELB will cut the connection immediately and all the current request that are being processed will be halted. so instead using connection draining makes sure the current active connections are not dropped or cut off for a set duration to let them finish but don't take any new request during this period


types of aws load balancer
- application load balancer (http)
- network load balancer (tcp)
- gateway load balancer (ip)

load balancer security
since the load balancer needs to be capable of receiving http request from anywhere, we need to create security group rules that allows request to arrive at port 80 and 443 and the source ip as 0.0.0.0/0

in the ec2 instance level, we create a incoming security group entry that allows traffic from the security group of the load balancer


why are layer 4 LB better performant than layer 7 LB?
- Lower layers = less processing → faster.
	- A TCP LB only deals with:
		- TCP handshake
		- Connection forwarding
		- Basic routing
	- An HTTP LB must:
		- Parse HTTP headers
		- Parse HTTP body (sometimes)
		- Understand cookies, hostnames, paths
		- Evaluate rules (path-based, hostname-based, header-based)
		- Potentially terminate TLS
		- Inspect requests for health checks
- L4 load balancers treat packets as raw bytes.
- TCP LB:
	- Opens TCP connections to backend
	- Forwards packets with almost no inspection
- HTTP LB often handles TLS termination (expensive)
- HTTP(S) LB usually performs:
	- TLS handshake
	- Certificate validation
	- Decryption & encryption
	- Sometimes re-encryption to backend
- **TCP LB** is like a security guard who only checks your ticket and lets you in.
- **HTTP LB** is like a guard who checks your ID, scans your fingerprints, checks your bags, and asks why you're visiting.



### Application load balancer

- routes traffic based on HTTP traffic
- supports http/2 https and websocket
- routing based on:
	- path in URL (example.com/users OR example.com/posts)
	- hostname in URL (com.example.com OR other.example.com)
	- query string & headers (example.com/users?id=123&order=false)
- port mapping feature to redirect to a dynamic port in ECS



### Network load balancer
- forwards traffic based on TCP and UDP
- handles millions of request per second
