- There are two main differences between how  per-router controlled control plane works vs how a SDN enabled control plane works, this includes:
	- The algorithm whether it is link state algorithm for distance vector is computed in the network controlled application component of the control plane rather than every inside the router.
	- The packet switch sends link update information to the SDN controller rather than directly to other routers.
![[Fri Feb  9 04:35:25 PM +0545 2024.png]]
In this example, we assume that a dijkstra's link state routing algorithm is used to find the shortest route. And suppose that the link between s1 and s2 is broken down then the following actions are performed: 
1. s1 finds the link between itself and s2 is down so notifies the SDN controller of the link-state change using the [[OpenFlow]] port-status message
2. The message is passed to the state management of the controller which updates its entry in the link-state database.
3. 