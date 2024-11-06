interior gateway routing protocol 
uses link state algorithm or dijsktra's algorithm for finding the shortest path inside a autonoomous system 
All the routers in the autonomous system has the information about all other routes and the information that they have at should be same through the system 
For routers to get this routing information it uses link state advertisements and store this link state advertisements inside link state database. A link state database contains a collection of link state advertisements and this is used to create a general topology of the entire autonomous system. This topology tree of the system is then used to find the shortest path and update the forwarding table at each router.
Before link state advertisements can be sent to another router, two routers need to first form a neighbour relationship. To do so a router first needs a router ID which is a unique address in the network for the router.

Once the router has its own unique address then it needs to become neighbours with other routers in the network. To do this a sends a HELLO message in a point to point link between two routers. This hello message contains the source address and a list of neighbours that the source router has. The receiving router initially performs some checking before sending out a HELLO message to the sender which contains this router's address and the sending routers address in its neighbour list. This router will move to the init state. The sending router will add the receiving router as its neighbour and sends another HELLO message to it. Here the sending router is moved to a 2-way state. Once the receiving router receives the message with it as its neighbour then it moves to the 2-way state as well and now they are ready to exchange database information.

Before sending database information, a DR (designated router) and BDR (backup designated router) are election based on the router ID. All the router in the network will only accepts routing information from DR or BDR and will ignore all other routing information to avoid flooding of routing information by non-DR and non-BDR routers. Suppose a router is sends a DOWN state information to all the routers in the network. Since it is a link state algorithm, this update information is exchanged between all the routers which causes the bandwidth to be inefficiently used for only routing information. Instead the DOWN state information is received by the DR and all other routers ignore this message. Then the DR will send the DOWN state information to all the router which will make all the router update their link state values. 

Once the exchange process starts then the neighbouring routers enter the exstart state. database description (DBD) packet to establish adjacency between the routers must be send to synchronize the state of the router's LSDB with all other router LSDB. This is done by electing a master and slave router. The master router first sends all the LSA present in its LSDB to the slave and then the slave would send all its LSA to the master. They both check the values and try to find any missing LSAs. If there are any missing LSAs in a router then that router would create a LSR (link state request) packet to infromation the other router which has the information about a subnet to send that information to it. The router would read the request and sends a link state update (LSU) packet descrbing the network. Once the first router receives the packet then it sends a LSAck which basically acknowledges the packet.

Once the LSDB is synchronized between the routers then it starts to fill the routing table using the link state algorithm. But before that the cost for each link is calculated using a reference bandwidth value and is divided by the interface bandwidth value such that 
**cost = reference bandwidth / interface bandwidth** 
the reference bandwdith is a constant that can be changed by the network admin and the interface bandwidth is the actual bandwidth of a router's interface. Once the cost is calculated then the link state algorithm is ran and the forwarding table are filled 

# OSPF area
divide the system into areas 
backbone area 
plan the subnet for each area 
area border router (ABR) -> has interface in two or more areas 
the area border router summarizes the subnet of the area to the backbone area and backbone area to other area 
backbone router -> router fully or partially inside the backbone area 
internal router -> 
autonomous system boundary router 


