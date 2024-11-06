How does router determine which link it should forward the packet onto? In the internet, every end system has its own unique [[IP address]]. 
Each router has a [[forwarding table]] that maps the destination address to that router's outbound links
When a source end system wants to send a packet to a destination end system, the source includes the destination's [[IP address]] in the packet's header.

When the packet arrives at a router in the network, the router examines a portion of the packet's destination address and forward the packets to the adjacent routers.

When a packet arrives at a router, the router examines the address and searches its forwarding table, using this destination address, to find the appropriate outbound link. The router then directs the packet to the outbound link.

The router uses the destination address to index a forwarding table which is used to determine the appropriate outbound link that the packet must go through.

We have the main destination address and we also have the hop address of the adjacent routers. When we send a packet to a destination system, we attach the destination address of the destination end system. Between the source end system and the destination end system there are various other adjacent systems that the packet must go through to arrive at the appropriate destination end system. For this, each router has its own forwarding table. The job of a [[forwarding table]] is to look at the address that it receives and then map that address with the appropriate outbound link.