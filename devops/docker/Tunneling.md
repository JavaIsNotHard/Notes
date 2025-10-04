A proxy is basically something that forwards any packet that arrives in its interface

Tunneling is basically wrapping packets of one form in packet of another form
what are VPNs

virtual private network (a whole damn network)

a VPN contains a VPN protocol that sits between the proxy server and the client and intercepts layer packets such as TCP or IP packets and tunnels those packets and sends it to the VPN server

VPN server creates their own virtual interface (not physical like wls2p0 or en0) but something called as TUN/TAP which is specific to VPNs. all the packets are passed through this TUN/TAP interface when they are routed, wraps the packet in the VPN's own protocol, changes the source IP to its own and forwards the packet to the VPN server. the VPN server is like a proxy or a forwarder whose job is to only forward incoming request to some destination address

this is the basic idea of enpasulation which is also used for encryptions where the packet that we want to encrypt are added as payload to an unencrypted packet

the basic idea is that VPNs use tunnels such as GRE tunnels to route traffic over the network, VPNs are set of software and encapsulation logic that is added by vpn clients and servers when routing traffic between them 
VPNs use IPSec to provide security and encryption of packets