the input port of a router has 4 main functionality
1. physical layer
	- the physical layer functionality refers to the concept of converting electrical signals coming from the wire to bits and bytes that the router can understand
2. link layer
	- It deals with things like **frame recognition, error detection, and synchronization**. this layer understands the link-layer frame that encapsulates the network layer packet
3. forwarding
	- once the packet has been received and framed, the input port must decide where to send it next in the router, for this it consults the forwarding table to find out which output port should receive the packet
4. control packet function
	- special packets, those that are used by routing protocols such as OSPF and BGP aren't forwarded like normal packets, instead they are directly send to the routing processor of the router