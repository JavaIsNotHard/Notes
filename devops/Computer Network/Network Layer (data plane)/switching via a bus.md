both the input and the output port are connected via a shared bus where only a single packet can be transmitted through the bus at a time

switching in this method occurs by appending an extra packet identifying header to the packet which is used to indicate which output port should process or accept this packet

the input port then forwards the packet to all the output port in the router, the output port then on the basis of the header appended previously checks if it is the designated output port for that packet, if yes it transmits the packet out, else it discards the packet

If multiple packets arrive to the router at the same time, each at a different input port, all but one must wait since only one packet can cross the bus at a time.

the bottleneck in this approach is the limitation of only being able to send one packet at a time over the shared bus