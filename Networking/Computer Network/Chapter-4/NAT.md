network address translation 
private address 
3 groups of address that are same in all private network 
10.0.0.0 - 10.255.255.255
172.16.0.0 - 172.31.255.255
192.168.0.0 - 192.168.255.255

Each host in a private network is given on of the following private address group 
This private address is private to a network and cannot be used to send packets outside of the network. Why? Because we have group of private address for all private networks  
what happens to the mapping inside the nat table when for example we have two host sending data at the same time over the network? Because as of my understanding, the NAT-enabled router only has a single public address 
That means instead of the network address, the host are differentiate using their port number interesting 
suppose host a and host b have address 1.1.1.1 and 2.2.2.2 and the NAT routers external interface has the address 10.0.0.0 then when the packet of host a reaches the NAT router then it translates the source address to the address of the router and assigns a unique port number suppose 1000 which is not in use for the router. When host B 