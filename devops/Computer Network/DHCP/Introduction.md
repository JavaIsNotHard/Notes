every interface to be used with TCP/IP networking requires an IP address, subnet mask, and broadcast address (for IPv4)

the broadcast address can be obtained using the address and the mask in the same network or the same subnet

The design of DHCP is based on an earlier protocol called the Internet Bootstrap Protocol (BOOTP), BOOTP does not have a mechanism to support changing that information after it has been provided
DHCP extends the BOOTP model with the concept of lease

DHCP comprises two major parts:
1. address management : used for dynamic allocation of addresses and provide address leases to client
2. delivery of configuration data : includes DHCP protocol’s message formats and state machines

DHCP can provide three layer of allocation:
1. dynamic allocation : dynamic allocation, whereby a client is given a revocable IP address from a pool (usually a predefined range) of addresses configured at the server
2. automatic allocation : addresses are not revoked 
3. manual allocation : DHCP is used to convey the address but the address is fixed for the requesting client

The lease duration is an important configuration parameter of a DHCP server
Longer lease durations tend to deplete the available address pool faster but provide greater stability in addresses and somewhat reduced network overhead because there are fewer request to renew the address
Shorter leases tend to keep the pool available for other clients, with a consequent potential decrease in stability and increase in network traffic load

### message format for BOOTP
![[Pasted image 20251005100218.png]]