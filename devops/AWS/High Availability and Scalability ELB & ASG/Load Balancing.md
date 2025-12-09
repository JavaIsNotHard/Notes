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