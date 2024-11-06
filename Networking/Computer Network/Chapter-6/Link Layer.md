First we need to understand what a link stands for.
A link is a direct connection between two neighboring nodes. This connection could be either wired or wireless. 

The following are the responsibilities of link layer:
- move a datagram over an individual link from one node to its adjacent node or directly connected neighboring node.
- [[framing]]
- [[error detection and correction]]
- [[access control]]
- [[reliable data transfer - link layer]]

A single network datagram can be encapsulated using multiple link layer protocols such as ethernet, 802.11 wireless LANs and many more. 

Let us take an analogy of travel agency. 
A travel agency is planning a trip for a tourist travelling from Princeton, New Jersey to Lausanne, Switzerland.

Princeton -> JFK airport 
JFK airport -> Geneva's airport 
Geneva's airport -> Lausanne's train station 
Princeton limousine company -> Princeton to JFK trip is handled 
airline company -> to get tourist from JFK to Geneva
Swiss train service -> to get tourist from Geneva to Lausanne

Limousine -> Airplane -> Train (transportation mode) -> its primary job is to move tourist from one location to another 

Here the transportation mode is the protocol that is used to transfer a datagram from a sender to a receiver. 
The companies involved in transporting the tourist are routers 
The travel agency is the routing algorithm which determines the optimal path for the tourist and sends those path information to those transportation companies 
And finally the datagram is analogous to the tourist 
Different links can have different link layer protocols that are used to transfer datagram. 
Understanding the difference between a link and a node is important. A node is any network devices or network interface card inside a network device. A network device such as a personal computer implements the link layer functionality in both hardware and the software. 
- [[hardware - link layer]]
- [[software - link layer]]
