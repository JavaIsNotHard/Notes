
every component that are part of kubernetes have the same release version

different kubernetes core components can exists in different release version

none of the other components should have a version higher than t

![[Pasted image 20260130150236.png]]

when should we upgrade?? 
 

### how to upgrade ??
upgrade one minor version at a time i.e rather than upgrading from v1.10 to v1.13 we upgrade from v1.10 to v1.11 to v1.12 and finally to v1.13

### Strategies to upgrade

we first upgrade the control node 

then we either
1. down all the nodes and upgrade it then restart the nodes and the scheduler will schedule new pods to it
2. down one node at a time, schedule the pods in the downed node to other nodes and when the node is upgraded schedule other pods (not the previous pods)
3. add a new node, move the workload of one node to the new node and then down time old node one at a time, adding new node one by one 