the most important concept in AWS networking is the concept of VPC (virtual private cloud) which is a technique to isolate AWS resources between different users or customers

basically VPC is used to isolate AWS resources between two users such that their resources don't conflict with one other. each AWS user has a default VPC which is created when a root aws user is created

normally the CIDR range of the default VPC is 172.31.0.0/16 which divides the network in two equal halves both of 65536 hosts and networks. 

now the default VPC CIDR range is subdivided into multiple subnets such that they can be distributed among multiple availability zones 

![[Pasted image 20251009095340.png | 500]]

here eu-west-1a, eu-west-1b, eu-west-1c are different availability zone within the same default vpc each having its own subnet

the ipv4 address are dual stacked with ipv6 which means that communication can happen using both ipv4 and ipv6 when sending and receiving packets 

![[Pasted image 20251009100110.png | 500]]

this means that each AZ will have both ipv4 and ipv6 addresses 

### Routing in AWS

to talk between addresses we need to be able to route 
the route table is used to define all the routes such that it tell where to move the packet in the network 
every default vpc will have a default route table but can can define different route table to different subnets 

the default VPC has the following route table
172.31.0.0/16 , target -> local which means traffic originating from this subnet are all local traffic and should be handled accordingly 
another rule is for sending data outside the network to the internet
three things you need to communicate with the internet
1. some form of communication with the internet (internet gateway)
2. route to the internet (the 0.0.0.0/0 route)
3. public address

a public subnet : has a public address for outside the internet to communicate within the subnet
a private subnet : doesn't have a public address and doesn't allow outsiders to communicate inside the subnet
since it doesn't have public address, a private subnet requires a NAT which gives the private subnet a public address but restricts any inbound traffic in the private subnet, but this is not valid if the requester is the private subnet, if the requester is our private subnet then NAT allows traffic from the destination of the requester to send request back because there is a entry in the NAT 


### network security
- security groups 
	- network access control list
- flow logs







