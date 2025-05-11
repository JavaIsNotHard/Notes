- a single write is amplified as multiple writes to different system. For example, a write to a database results in a write to the search index as well as the local cache server
- this has many concurrency and fault-tolerance problem 

example of the concurrency problem can be visualized something like this
![[Screenshot 2025-05-11 at 12.57.53 PM.png]]

here, there are two clients 1 and 2 where client 1 updates the value of X to A and client 2 updates the value of X to B and we need the change to be propagated to two different data stores, the database and the search index.

suppose client 1's update value gets sent to the database first than client 2's and client 2's update request reaches the search index first than client 1's which means the final value at the database would be B and the final value at the search index would be A which are inconsistent with one other

we also have the problem of fault-tolerance because if the search index were to go down and not get any request while the database accepts requests then search index falls behind the database are both are now inconsistent with one other as well 

- also in a replicated environment, each system will have their own leader node which do not coordinate with one other which results in conflict as well 
- so we need our source data which is the database to act as the leader and other data systems as followers of the leader 
- this approach is called [[change data capture]]

dual write problem such as concurrency and fault tolerance can be can be avoided using techniques such as version vectors and two phase commit or distributed transaction protocol