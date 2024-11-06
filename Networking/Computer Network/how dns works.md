DNS stands for domain name system which is an application layer protocol that is used to translate a hostname i.e human readable into a IP address that a computer understands. There are many reasons to use DNS which includes:
1. Host aliasing: A single host can have more than one cannonical name associated with it. This means that DNS can be used to translate a cannonical name into the original hostname 
2. Email aliasing
3. load balancing : A single hostname can be associated with a set of addresses such that each address is assigned to a separate server to fulfill the request for the original hostname. When a lookup for a hostname is performed that has more than one address then the first address associated with it is given and the order of the address is changed. This makes sure that a single server is not handling all the requests. 

## Centralized DNS server
A simple approach to implement DNS would be to have a central DNS server which contains all the hostname to IP address entries. This makes it easier to implement DNS but is not practical at all due to the following reasons
1. single point of failure: If the central DNS server where to go down then no translation can be done
2. heavy load: since there are only one server all the lookup request will have to be performed by the single DNS server making the server manage heavy load 
3. maintenance

## Hierarchical DNS servers 
1. Root DNS server
2. Top level domain server 
3. Authoritative DNS server

There are only 13 physical root dns server which are managed by 12 compaines. The root dns server maintains the address of all the TLD servers. 

The TLD servers maintains the address of the authoritative dns servers. These server includes com., edu., org. and many more domain names. 

Every organization that has a publicly accessible hosts such as a web server or a mail server will have a authoritative dns server that has the IP address for that server. The organization can have these DNS server either in their physical location or can pay other compaines providing these services to host the DNS records. 

Recursive vs iterative dns query