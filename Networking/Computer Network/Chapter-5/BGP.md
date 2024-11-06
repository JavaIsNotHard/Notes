border gateway routing protocol
communication between one AS and another 
destination are CIDRed address of the form a.b.c.d/x 
routers forwarding table will have entries of the form (x, I) where x is the prefix address and I is one of the interface number for one of the router's interface .
BGP provides the following things:
- reachability information to neighbour AS 
- determine the best route to the prefix or the subnet

policy based routing protocol 
path advertisement when a new network is added to the autonomous system 
the path advertisement contains the prefix or the address of the network as well as bgp attributes

Each AS communicates with each other using a semi-transparent TCP connection using port 179. BGP TCP connection within the AS is called internal BGP connection and TCP connection between two gateway router is called external TCP BGP connection.
The following are the BGP messages exchanges between two host inside or outside the AS:
- OPEN : open a connection between two BGP peers
- UPDATE : advertise a new update information using the TCP connection
- KEEPALIVE  : keep the connection alive in absence of UPDATES
- NOTIFICATION : report error and close the connection

BGP is a path vector algorithm instead of a distance vector algorithm because instead of distance between the two routers it advertises the path between the prefix and the host. 

Whenever a new network is added to the AS, the AS that network belongs to will advertise this information to all the AS in the internet. This advertisement contains the prefix of the network + some attributes. These attributes include:
- AS-PATH : list of all the AS that the advertisement as passed through to reach that particular host
- NEXT-HOP : the IP address of the router to forward any packets destined to prefix x

BGP routing algorithm 
the forward table for each internal router is set by using the path advertisement. Suppose that AS3 sends a BGP update message of "AS2 AS3 x" to AS1 and the next-hop attribute value set to the address of the interface that is connected to AS1. the gateway router of AS1 knows this routing information and sends that to all the internal router in the AS saying that all the packet destined to x will be passed through the gateway router. and within the AS it uses OSPF to find the optimal path to the gateway router