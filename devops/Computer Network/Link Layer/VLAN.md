![[Screenshot 2025-08-27 at 12.35.39 PM.heic]]segregate a single switch into multiple virtual switch which creates a boundary between a single switch

the traffic from one switch do not leak to another switch of different VLAN

two hosts that are connected to different VLANs but the same switch still requires a router in between them for communication because VLAN creates a separate broadcast domain

when multiple VLAN must span multiple switches then it is called trunking, for this each ethernet frame that goes through the switch must be identified by its VLAN identifier. this VLAN identifier is a value inside the VLAN tag header of the ethernet format 

the ethernet frame contains a 12 bit VLAN id field inside the Q/S tag 
the Q/S tag also contains a priority field which is 3 bits in length which is defined in 802.1p

the VLAN is defined in 802.1q protocol
