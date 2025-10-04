Switches and bridges use the Spanning tree protocol to find the shortest route between the source and the destination in the LAN

the spanning tree protocol is also used to avoid looping paths between the nodes 
another thing we need to consider with STP is that nodes in the bridge or bridges themselves can be turned off or on, interface can be replaced and the MAC address can change. For this problem, there is a special frame called the bridge protocol data unit (BPDU) which is sued for forming and maintaining the spanning tree

The spanning tree protocol is also used to stop broadcast storm 

to understand the working of BPDU and STP we need to understand the state machine for the ports of switches and bridges

Topology change

BPDU frame format

![[Screenshot 2025-08-27 at 4.55.21 PM.jpeg]]

- STP uses BPDU frames, not only STP but also RSTP
- BPDUs are always sent to the group address 01:80:C2:00:00:00
- The _Protocol_ (_Prot_) field gives the protocol ID number, set to 0
- The _Version_ (_Vers_) field is set to 0 or 2, depending on whether STP or RSTP is in use
- TC stands for topology changes and TCA stands for topology changes acknowledgement
- _Proposal_ (_P_), _Port Role_(2 bits), _Learning_ (_L_), _Forwarding_ (_F_), and _Agreement_ (_A_) follow the TC bit

Building the spanning tree 
- first discover or elect the root bridge
- the root bridge is the one with the smallest identifier
- when the bridge first initializes then it assumes the role of the root bridge and sends configuration BPDU matching the one of its own bridge ID