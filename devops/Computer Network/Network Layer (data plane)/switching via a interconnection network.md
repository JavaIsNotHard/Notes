![[Pasted image 20250914101526.png | 400]]
The router has a **switch fabric** (like a crossbar matrix).
each input port can be connected to exactly one output port i.e we can have connection between separate input and output port at the same time, which means we can transmit data between them simultaneously
one limitation is that only one input port and one output port can be connected with each other so if there is a connection between port A -> Y then there cannot be B -> Y or A -> X at the same time as A -> Y
for N input and output port there are 2N buses for data transmission

When a packet arrives from port A and needs to be forwarded to port Y, the switch controller closes the crosspoint at the intersection of busses A and Y, and port A then sends the packet onto its bus, which is picked up (only) by bus Y

if two packets from two different input ports are destined to that same output port, then one will have to wait at the input, since only one packet can be sent over any given bus at a time
