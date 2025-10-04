virtual extensible LAN
extends the functionality of [[VLAN]]
VXLAN use 24 bit segment id known as VXLAN identifier or VNI which enable up to 16 million VXLAN segments to coexist in the same administrative domain


VXLAN provides a pipe like mechanism for two containers to communicate over different LAN or between different segments in the VXLAN

VXLAN depends on a special type of switch called VTEP (VXLAN tunnel end point)
this is a virtual switch interface and is used to encapsulate and decapsulate packets

there is a VTEP interface in both the sending side and the receiving side which creates a tunnel which is a UDP tunnel
this interface is used to encapsulate layer 2 ethernet frame and adds a VXLAN header and sends it as a UDP packet over the internet 