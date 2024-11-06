- ARP can be thought of as having the same job of that of a DNS. 
- DNS is used to translate hostnames into IP addresses whereas ARP are used to translate IP addresses into their respective MAC addresses. 
- DNS works for host that live anywhere on the internet whereas ARP is used only for hosts and routers in the same subnet. 
- ARP has a ARP table which is basically mapping between a IP address and its MAC address in the same subnet. 
- All the network adapters in the subnet have a ARP table containing all the mappings. 
- An ARP table also contains a TTL (time to live) duration for a particular entry which is set fo 20 minutes in most of the devices. 
- An ARP packet is a special type of packet that is send by a sending host. A ARP query packet is used to query all the hosts and routers in the subnet to determine the MAC address. 
- The ARP query packet is send to all the adapters in the subnet using the destination address set to boardcast address
- Each adapter in the subnet passes the ARP packet upto its ARP module.
- The job of a ARP module is to check for any mapping of the destination IP address, if there is then it would send back a ARP packet having the source address as the destination address. 
- ARP is a protocol between the link layer and the network layer


When passing data to a router, it first creates a link layer frame. When host 1 knows the address of the router then it creates another link layer frame, this time it attaches a network layer datagram with the host 2's IP address. So basically two frames for a single data transfer