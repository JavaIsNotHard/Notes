allows container communication over internet and not just inside a LAN or within a localhost. But HOW??

Creates a virtual network on top of the existing physical network 

uses the concept of encapsulation where we encapsulate packet of one layer into packets of another layer. example, image sending a letter to a friend in another city. instead of just putting the local address of where your friend lives, you place it inside a large envelope with the full address of your friend's city and street. The outer envelope is what the postal service uses to route the letter. When the letter reaches the destination post office, they remove the outer envelope and find the original letter with your local address and deliver it to your friend

The most commonly used encapsulation protocol is the VXLAN protocol
VXLAN wraps the original ethernet frame (layer 2) from the container into a UDP packet (layer 4)

[[VXLAN]]


1. **Container-to-Container Communication Intent:** A container, let's call it `Container-A` on `Host-A` in `LAN-A`, wants to send data to `Container-B` on `Host-B` in `LAN-B`. Both containers are part of the same overlay network and have their own private IP addresses within that network.
    
2. **Packet Creation in the Source Container:** `Container-A` creates a standard data packet with `Container-B`'s private IP address as the destination.
    
3. **Encapsulation on the Source Host:** This packet is sent out of `Container-A` to the host's networking stack. The overlay network driver on `Host-A` intercepts this packet. It then performs the following actions:
    
    - It looks up the physical IP address of `Host-B` (where `Container-B` is running). This information is typically stored in a distributed key-value store that all hosts in the overlay network can access.
        
    - It encapsulates the original packet from `Container-A` within a VXLAN packet. The outer header of this new packet contains the IP address of `Host-A` as the source and the IP address of `Host-B` as the destination.
        
4. **Routing Through the Physical Network:** This encapsulated packet is now just a standard IP packet from the perspective of the physical network. `Host-A` sends it to its default gateway, which is the router connecting `LAN-A` to other networks.
    
5. **The Router's Role:** The router examines the **outer** IP header of the packet. It sees the destination IP address is that of `Host-B`. The router, knowing the route to `LAN-B`, forwards the packet across the network towards `Host-B`. The router is completely unaware of the inner packet destined for `Container-B`. It simply performs its standard function of routing IP packets between different networks.
    
6. **Decapsulation on the Destination Host:** The encapsulated packet arrives at `Host-B`. The overlay network driver on `Host-B` receives this packet because it is addressed to the host's IP. The driver then performs the following:
    
    - It decapsulates the packet, removing the outer VXLAN and IP headers.
        
    - This reveals the original packet from `Container-A` with `Container-B`'s private IP address as the destination.
        
7. **Packet Delivery to the Destination Container:** The overlay driver on `Host-B` then forwards this original packet to the network interface of `Container-B`.
    
8. **Communication Established:** `Container-B` receives the packet as if it came from `Container-A` on the same local network. The entire complexity of the underlying physical network, including the router, has been abstracted away by the overlay network.
    

In essence, the overlay network creates a tunnel between the host machines. The router's job is simply to route the traffic for this tunnel, without needing to understand the container-specific traffic flowing within it. This powerful abstraction is what enables the flexibility and portability of containerized applications across diverse and complex network topologies