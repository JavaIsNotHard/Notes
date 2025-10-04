basically a layer 2 device which is self learning and forwards packet based on MAC address rather than IP address like routers

switches are intelligent version of bridges

a switch contains a switch table which contains entries of how to forward and filter packets based on the MAC address and the interface in which the packet arrived at 

suppose a packet with destination DD-DD-DD-DD-DD-DD arrives at the switch on interface x then here are the possible options that can happen:

1. there is no entry for the mac address DD-DD-DD-DD-DD-DD in the switch table. in this case the switch has to broadcast the frame to all other interface other than x 
2. there is an entry for the same MAC address but from the same interface x. this means its a localhost frame and shouldn't be forwarded anywhere and just discard the packet 
3. there is an entry in the table with address DD-DD-DD-DD-DD-DD in interface y != x then the switch puts the frame into the output buffer of the interface y

Switch self-learning

1. initially the switch is empty
2. for each incoming new frame with a new MAC address not inside the switch, it adds the corresponding MAC address and the interface from which the frame arrived from as an entry in the switch table
3. the entries in the switch table is deleted after some period of time 


switch are plug and play devices and do not require the intervention of the network administrator

LAN or local area network contains all the network devices such as switches and bridges as well as host station devices that are connected within the local network and those connection do not span outside the gateway router. so basically everything within the gateway router can be considered as LAN

[[Spanning tree protocol]]

