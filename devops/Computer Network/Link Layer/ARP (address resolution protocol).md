JOB -> translate IP address to MAC address 

LIMITATION -> can only translate IP address to MAC address of hosts and routers in the LAN unlike DNS

each host and router will have an ARP table within its memory
this table will have the mapping of IP address to MAC address information

there are two types of ARP packets: 1. ARP query packet & 2. ARP response packet
the ARP packet is encapsulated inside the link layer frame

The ARP query packet is send as a broadcast packet with an destination MAC address of FF:FF:FF:FF:FF:FF which is used to indicate a broadcast address

The ARP response packet is sent as standard frame

each host and router will also have an ARP module which is used to process the ARP query packet and check whether the destination address in the ARP packet matches with its own IP address

If ARP protocol only works within a local subnet then how can we send packets over the subnet into the internet?


FROM TCP-IP illustrated book 

if the querier and the target host have the same IP prefix then the request sent from the querier does not need to pass through the gateway router

when communicating at link layer, ethernet compatible addresses must be used 

