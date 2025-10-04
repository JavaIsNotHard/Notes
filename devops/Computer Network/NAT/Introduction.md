allow same set of IP addresses to be used in different parts of the internet


NAT vs NAPT (network address port translation)

![[Screenshot 2025-07-21 at 9.34.42 PM.png]]

basically traditional NAT maps the private IP to a pool of IP addresses and leaves the port number unchanged

NAPT on the other hand rewrites the private IP address to a single public IP address and also changes its port number

one major limitation of NATing is that it is only allows outgoing-only type of traffic which means that external clients cannot access the servers or components inside of the NAT because they don't have a publicly accessible address which can be used to directly connect to the server within the NAT

TCP's SYN packet is used to identify when to create a new entry in the NAT lookup table. which means that when the NAT receives a SYN packet it creates a new entry in its lookup table. this helps identify which is the first packet for that particular device

some NATs rely on the TCP SYN to create bindings, and will just drop mid-connection TCP packets that correspond to unknown flows

if SYN packet is used to create new binding then FIN or RST packets are used to close the binding. This method also isn't sufficient even for TCP, because the client might have shut down without sending a FIN, for instance if it crashed or the user put their laptop to sleep.

Use a timeout and tear down connections which are idle for too long

when SYN is observed then connection timer is activated
and if no ACK is seen before the timer expires, the session state is cleared
if an ACK arrives then the timer is canceled and session timer is created
then NAT sends additional packet to the internal endpoint just to double check if the session is indeed dead (probing), if it receives an ACK then the NAT realizes that the connection is still alive, resets the timer, and does not delete the session

for UDP packets, NAT uses mapping timer to clear NAT states if a binding has not been used recently. the value of the timer to be atleast 2 minutes and recommended value is 5 minutes

### address and port translation behavior 
how NAT handles translation (mapping internal to external addresses) and filtering (deciding what incoming packets are allowed back in)
there are mainly 3 types of translation and filtering behavior which includes:
1. endpoint-independent NAT
2. address dependent NAT 
3. address and port dependent NAT
suppose we have the following mapping in the NAT
![[Pasted image 20250930095724.png | 400]]
here X:x is a private address mapping where X : private IP address and x : port number
similarly X1': external mapped IP address and x1' : external mapped port number
and Y:y is a remote address where Y: remote IP address and y : remote port

**Translation Behavior**: How is X1:x1 mapped to an external X1′:x1′?
**Filtering Behavior**: Which external responses are allowed back in?
#### endpoint independent NAT
**Translation** : in this type of NAT, once a private address X:x is mapped to a public address X1':x1' then it will always use the same mapping no matter which remote server (Y1 or Y2) it contacts

**Filtering** : any remote server (Y1 or Y2) can connect back to the private address space because there exist a mapping which mapped a single public address space to multiple private address space. example, since X:x -> X1':x1', if the remote server sends back a packet destined to X1':x1', it uses this mapping to forward the packet to the final destination X:x

#### address dependent NAT 
**translation** : for a particular destination address Y1, there exist a separate mapping for it X:x -> X1':x1' and for another destination address Y2, there exist another mapping for it X:x -> X1':x2', here both the destination address has been mapped to the same public IP address X1'
this type of NAT always uses the same public IP address for a given internal host i.e if we had another internal host X2 we would have another mapping X2':x1' and so on

**filtering** : NAT only allows packet from a particular destination IP address the client contacts but form any port of the destination IP address, suppose we have a mapping
X1:x1 -> X1':x2' for a public address Y1:y1 then, NAT allows application running from any port number of Y1 to send packet to the public address X1' i.e Y1:y1, Y1:y2, Y1:y3 ... can send packet to the public address X1'

#### address and port dependent NAT 
the most restrictive type of NAT
**translation** : the NAT decides the external mapping based on destination IP + destination port i.e even if you contact the same destination IP but to a separate destination port then it creates a separate mapping for both. example, suppose X1 contacts Y1:y1 and Y1:y2 then there will exist two mappings X1:x1 -> X1':x1' for Y1:y1 and another mapping X1:x1 -> X1':x2' for Y1:y2. previously using address only dependent NAT, both Y1:y1 and Y1:y2 could be reached from the same mapping X1':x1' for a single internal host X1

**filtering** : only packets from exact address (Y:y) that X1 had previously contacted are allowed through

one main disadvantage of using NAT is the use of checksum, because NAT converts the source IP and port when recalculating the checksum in the destination the checksum is going to be didfferent

### servers behind NAT
servers behind NAT can expose their service using something called port forwarding


### NAT traversal 

for a client to send packet to another client when there already doesn't exist a entry in the lookup table is going to impossible so NAT traversal is used

this is a method where two hosts that are in private network can directly communicate with each other which is typically not possible with NATed devices

**Common techniques for NAT traversal**
Client asks a STUN server (publicly reachable) to report the public IP/port it sees. The client shares this with the peer so packets can be sent back. Works with many “cone” NATs.

Steps for NAT traversal 
1. The signaling server : a public server that has the public IP address information of both the communicating entities 
2. Hole punching  : once both the communicating entities have each other's public IP then the connection can be initialized, but directly connecting makes the router drop the packet so both the server send each other UDP packets to create a new entry in the NAT lookup table
3. The fallback plan - the TURN server : the last option if the router has "Symmetric NAT" then there is a centralized server from which the two communicating server use to communicate with each other


#### pinholes and hole punching

pinholes -> when a client inside the NAT sends packet outside through the NAT then it creates a temporary mapping. this mapping is known as pinholes. this allows incoming traffic if there is already an outgoing request that opened that door

hole punching is basically creating pinholes intentionally in both communicating sides such that they can connect to each other through the pinholes

for this technique to work we need an external server to which both the communicating clients send their initial request, this is usually a STUN server
when both the client communicate with this external server, the server saves the mapping configuration information and exchanges this information between the clients such that both the client know the public address of each of them and have the mapping that allows the NAT to accept the packet instead of dropping it
The popular Skype peer-to-peer application uses this approach

the first packet that the client send to each other are dropped because they don't have the appropriate mapping in the NAT but for all subsequent packets the communication is facilitated 


### configuring packet filtering firewalls and NATs

In most home networks the same device is providing NAT, IP routing, and firewall capabilities and may require some configuration

#### firewall rules
A packet-filtering firewall must be given a set of instructions indicating criteria for selecting traffic to be dropped or forwarded

network administrator usually configures a set of one or more ACLs

Each ACL consists of a list of rules, and each rule typically contains pattern-matching criteria and an action

the matching criteria is either network or transport layer data or header or fields inside the header (e.g., source and destination IP addresses, port numbers, ICMP type field, etc.). actions include a specification to block or forward the traffic and may also adjust a counter or write a log entry.

we can also match based on direction of traffic i.e whether the traffic is outgoing or incoming

One of the popular systems for building firewalls is included with modern versions of Linux and is called iptables
iptables includes the concepts of tables and chains, tables contains a set of chains and each chain is a list of rules the packet are matched against in order

table contains several predefined chains and may contain zero or more user defined chains

iptables also contains 3 main predefined tables which include
1. filter table -> used for packet filtering
2. nat table -> used for NATing, basically used to change the source and destination IP address of the packet
3. mangle table -> used to alter packets and modify the IP headers of packets

filter table is the default and most commonly used table in iptables
the filter table contains 3 predefined chains
1. INPUT -> applies for all the packet coming to the local machine
2. OUTPUT -> applies for all the packet going out of the local machine
3. FORWARD -> applies for all the packet that are being routed through the machine i.e this chain is only used when the machine is acting as a router

the nat table is the translator and contains the following predefined chains
1. PREROUTING -> this chain is traversed by packets as soon as they enter the network stack, before any routing decision are made
2. POSTROUTING -> this chain is traversed by packets just before leaving the machine
3. OUTPUT -> this chain is used to alter the destination address of the locally generated packet
The `nat` table only sees the first packet of a new connection. The translation decision made for that initial packet is then automatically applied to all subsequent packets in the same connection by the connection tracking system

the mangle table is used to modify the packet and its IP headers and it contains all 5 chains as its predefined chain which includes
1. PREROUTING -> This chain catches packets **as soon as they arrive** at the network interface, **before** any routing decision is made. this means that regardless of the destination, even if the packet is not designated for this machine, the packet will traverse the PREROUTING chain found in this device
2. INPUT -> the packet only traverses the chain if the packet is designated for this machine
3. FORWARD
4. OUTPUT -> packets that are generated locally before any routing decision is made traverse through this chain, only packets generated locally i.e in the machine itself.
5. POSTROUTING -> whether the packet was generated in this machine or by a previous machine, the packet is going to traverse the POSTROUTING chain

each chain contains a packet matching crtieria and its associated action that is needed to be performed
The action (called a target) may be to execute a special user-defined chain or to perform one of the following predefined actions: ACCEPT, DROP, QUEUE, and RETURN