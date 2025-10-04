The earliest of the router used this technique
One of the most basic techniques for switching packets in the router
the input and output port in the router acts as traditional I/O port to an operating system
when an packet arrives in the input port, then it interrupts the router processor and then copies the packet from the input port to the processor's memory
the processor then extracts network layer headers from the packet and does the routing table lookup and then copies the packet to the appropriate output port

every packet requires two memory access: 1 by the input port to write the packet into the memory of the router processor and another by the output port to read the packet from the memory into the output buffer

this means that even if the memory bandwidth of the router processor is B, the overall bandwidth available is going to be B / 2
because we need to perform two memory operations for a single packet

if we increase the link speed and not the memory bandwidth then the memory bandwidth is going to be the bottleneck in our case
