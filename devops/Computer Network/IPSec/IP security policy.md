each IP packet is related to a security policy

IPSec security policy is mainly determined by the interaction of two databases
- security association database
- security policy database

![[Pasted image 20250927120401.png | 600]]

### security association

When two devices decide to communicate securely using IPsec, they first negotiate a set of rules. This agreement, called a **Security Association (SA)** ,defines everything about the secure connection: the encryption algorithm, the authentication method, the keys to be used, etc

one way logical connection between a sender and a receiver 
if a peer relationship is required using two way connection then two security associations are created, one between the sender and the receiver and another between the receiver and the sender

it is identified by 3 main parameters
- security parameter index -> 
	- 32 bit unsigned integer assigned to a particular SA.
	- The SPI is carried in AH and ESP headers to enable the receiving system to select the SA under which a received packet will be processed.
	- its main purpose is to tell the receiving device exactly which **Security Association (SA)** to use to process an incoming packet
	- a single host can have multiple SA with multiple destination host, when the device receives the packet it inspects the IPSec header for the SPI, IPSec protocol, destination IP address 
- Destination IP address 
- Security protocol identifier


### Security association database

A security association is normally defined by the following parameters in an SAD entry
- Security Parameter Index
- Sequence Number Counter -> generate sequence numbers
- Sequence Counter Overflow: A flag indicating whether overflow of the Sequence Number Counter should generate an auditable event and prevent further transmission of packets on this SA. this basically means that if the sequence number reaches 0 in the security association then the current SA must be terminated and the device must negotiate a brand new SA with new keys
- anti-replay window -> mechanism used by the receiving device to accept legitimate out of order packets while still filtering out malicious ones, in this method a window is defined with a particular size (about 64 to 128 packets). all the packets within that window are valid packets
	- for example our current window is as following (937 - 1000 which is 64 packets)
	- when a new packet arrives #1005 then the window is incremented by 5 positions so the new window becomes (942 - 1005)
	- packet is within the window but not yet seen #998 then slot number 998 is marked as received and the packet is accepted as valid
	- the packet is within the window but already seen #998 again, now since the window has already previously validated this packet so this time it must be a replay attack packet hence it discards the packet
	- the packet is out of the window range i.e the packet is too old #900. the packet number 900 falls in the range before 942 so is also discarded
- AH Information: Authentication algorithm, keys, key lifetimes, and related parameters being used with AH
- ESP Information: Encryption and authentication algorithm, keys, initialization values, key lifetimes, and related parameters being used with ESP


### Security policy database

rulebook that dictates how traffic should be handled 
component that determines whether data needs protection, what kind of protection they need and if the packet requires any protection at all 
for every inbound and outbound packets the SPD is consulted 
this decision making process is guided by a set of rules called the security policy

every IP packet can be in one of these 3 security modes
1. PROTECT -> 
2. BYPASS 
3. DISCARD

SPD works with the help of something called as selectors 
selectors are fields within the IP header or transport layer header such 
1. source and destination IP address
2. protocol
3. source and dest port number
4. direction of traffic

when a packet arrives , these values are extracted and compared against the selectors defined in SPD's policies, the first matching policy are applied 

#### how are SAD and SPD related

for outbound traffic, after the security policy is determined using the SPD, the SAD is consulted to get the currently active SA connection between the communication clients, if the security policy says PROTECT then all the necessary information for protecting the traffic or the packet is available in the SA such as algorithms to be used, keys and many more 

#### how SPD and IKE are related

when the packet needs protection but there exist no SA in the SAD between the communicating parties then IKE is triggered. IKE is mainly used to negotiate new security parameters between the parties and then establish a new SA

![[Pasted image 20250927165516.png]]
the following figure shows a basic SPD entries

### IPSec traffic processing

- IPSec works in a packet by packet basis 
- all outbound IP packet are processed by the IPSec logic before transmission
- all inbound IP packet are processed by the IPSec logic after reception and before passing to the upper layer protocol

![[Pasted image 20250927165716.png | 500]]

the processing for outbound packets is defined in the following figure

![[Pasted image 20250927165746.png | 500]]

the processing for inbound packet is defined in the following figure

### Encapsulating security payload (ESP)
