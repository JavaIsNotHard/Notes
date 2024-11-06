input port  -> has 3 functions, physical layer function, link layer function and network layer function 
the network layer function is to queue any incoming packet, forward packets to the output port by looking at the forward table and the forward control packets i.e packets carrying routing information to the switching fabric to the routing processor. The input port has a copy of the forward table such that it does not have to disturb the routing processor every time a new packet arrives. Range based forwarding is performed as well as longest prefix matching is done i.e when a address matches two or more range then the one address that has the longest match with any of the range, that range is chosen for that address. The lookup of the address can be done in constant time by using a special memory called TCAM

output port  -> stores the forwarded packet by the input port and then sends the packet to the appropriate output link or interface.

switching fabric -> heart of the router. input port can only send packet to the output port using the switching fabric. Types of switching
- switching via memory 
- switching via bus
- switching via internetworking

routing processor

