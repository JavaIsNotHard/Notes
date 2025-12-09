- Hello
	- used in the neighbor discovery stage
	- Each OSPF router periodically send Hello packet out of its OSPF enabled interface as multicast message (to address 224.0.0.5 for all OSPF routers). This happens every 10 seconds 
	- 
- Database description (DBD)
	- used when two routers are forming a neighbor relationship
	- they allow routers to describe the content of their LSDB without sending the entire LSDB content to the neighbor, sending the entire content of LSDB will create huge traffic in the AS
	- the receiving router will compare its LSDB with the DBD and check if there are any missing LSAs that it needs in order to be consistent with other OSPF routers
- Link State Request (LSR)
![[Pasted image 20251130170528.png]]
