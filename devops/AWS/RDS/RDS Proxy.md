a proxy server that sits between the client and the RDS db instance

what problem it solves?

too many database connections
- RDS proxy actively maintains a preexisting connection pool of 20-30 connection with the RDS instance
- the client creates connection with the proxy and the proxy is able to handle the connection (TCP handshake, TLS handshake and more)
- if there are 1000 active client connection then proxy pools the connection between the 20-30 preexisting connection it has with RDS instance

Failover
- failure in aurora is faster than in RDS
- aurora has shared storage between the main as well as replica servers which means promotion requires no synchronization of data
- failure in RDS is also slow because RDS needs to update the DNS entry for the new primary server because our endpoint is directly connected with our DB instances. If a new instance is created then it will have a new IP which the DNS entry must be aware of. this DNS propagation takes time
- proxy automatically connects to the failover server without needing any DNS changes because the DNS endpoint points to the proxy URL
- failover time is reduced by 66%

Authentication
- we can have the proxy handle all the authentication for the DB instance such as IAM login and credentials from secrets manager

Main thing to consider is the fact that the proxy is only accessible within the VPC, no public access is given, if your application server is running inside a EC2 instance then the application can connect to the proxy. only public access is disabled

What If Your App is Outside the VPC?
Connect your on-premise network to the VPC via AWS Site-to-Site VPN