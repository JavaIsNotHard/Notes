- hosts in the link layer uses its own link layer address which is different from the network IP address that exists in the network layer. 
- ARP (address resolution protocol) is used to translate IP address to link-layer addresses. 
- But link layer switches do not have link layer addresses.
- A link layer address is also called as a MAC address 
- The MAC address is used not to identify the devices in the network but rather to identify the network adapters or interfaces. 
- IEEE manages MAC address space. 
- A switch broadcasts all the frames coming towards it to all its interfaces. 
- When a interface finds a frame that the destination address of the frame is not the same as the interface address then it is discarded, if there is a match then the encapsulated network layer datagram and send to the network layer.
- The broadcast address to be used in link layer frame is FF-FF-FF-FF-FF-FF. 