when allowing replicas to accept writes, the order of the writes will diverge in some point, so for the replication to be useful, the divergence can only be temporary
ie. the replicas have to eventually converge to the same state
this can be obtained using the eventual consistency model which can be described as 
- eventual delivery -> update applied to one replica is eventually replicated to all replicas
- convergence -> replicas that have applied the same updates eventually reach the same state

in eventual consistency the convergence guarantee was weak meaning that the replicas even if they had the updates similar to replicas that are consistent will not have the same state as the other replica. why?
- they might receive the update at different times
- the updates might be applied in different order
- they have incomplete knowledge of the full set of operation 
eventual consistency only guarantees that the state will be the same after some time eventually when no update is being sent for some period of time

one way to reconcile conflicting writes is to use consensus to make a decision
that all replicas agree with

but we do not want to perform consensus and want replicas to be consistent without consensus so we can do the following

we can produce a deterministic outcome for any conflict by making sure that each replica follow the same rule (such as the write with the greatest timestamp always wins) without using consensus
here each replica will make the same decision about which write should win

this guarantee is called as strong eventual consistency which is descibed as 
- eventual delivery -> same as eventual consistency
- strong convergence -> replicas that have executed the same updates have the same state i.e every update is immediately persisted instead of eventually



how do we guarantee that replicas strongly converge?
for this we need a object replicated across N replicas where the object is an instance of some data type that supports query and update operations
these happens when the object receives the following operations
1. if the replica receives a query operation then it returns value from its local state
2. if it receives an update operation then it first applies it to its local copy and then broadcasts the updated object to all replicas
3. when a replica receives a broadcast message, it merges the object in the message with its own

before they used operational transformation for these conflict free replication without consensus but later used CRDT (conflict free data type )
consensus -> pick one valid outcome from a bunch of valid outcome
collaboration -> keep all the updates and merge them 

how replication happens in strong eventual consistency:
1. state-based 
	send state between replicas and the replicas are going to do their thing (merge) based on their state. here are the properties of this type of replication
	1. commutative -> the order of merging does not matter
	2. associative -> grouping doesn't matter
	3. idempotent -> merging the same state twice has no effect
2. operation-based 
	whenever the replica does an update, the update itself is send to other replicas. for example, updates such as "increment x by 1" or "remove x" and more

### state based replication
- all the updates are first applied to the local data storage 
- then they are eventually converged by sending the state information after the updating to other replicas
- the other replica on receiving the update will perform a merge with the new data and the current data in its local storage and then store the merged data 
- now this replica will send its own state information periodically and so eve


the replicas will converge to the same state if:
1. the object's possible states form a semilattice
2. the merge operation returns the least upper bound between two object's states

semi-lattice : a set that has a partial order and a operation that can take any two value and give the upper bound of those values 

if: 
1. the payload or the value in a replica form a semi-lattice
2. the updates are increasing 
3. merge computes the least upper bound
then the replicas converge to LUB of last values and these data types are called convergent replicated data type which is part of the family of conflict free data type


### operation based replication
- do not sent the full state rather send the update
- expect the replica to redo the update
- in the state based replication, each replica talked to other replica once in a while 
- but here every time we do an update, it has to be propagated to other replicas 

 if we can to converge then we want our operation to be commutative i.e the order of the operation does not matter 
 - if the operations are concurrent then we want them to commute 
 - if the operations are not concurrent then we want them to be replayed in the same order as the real time order in all replicas


the use of reliable boradcast protocol is not necessary and an unreliable broadcast protocol can be used to implement the broadcast as long a  they periodically exchange and merge their states to ensures that they eventually converge


data types that are designed to converge when replicated, like registers, counters, set, dictionaries and graphs
to make a register convergent, we need to define a partial order over its values and a merge operation
there are two register implementation that meets these requirements
1. last-writer-wins
2. multi-value

### last writer wins 
associates a timestamp for each update to make the updates totally ordered
when a receiver receives an update from a client then it generates a new timestamp and updates the register's state with that and the new replica
when a replica receives a  register state from its peer, it merges it with its local copy by taking the one with the greater timestamp and discarding the order
one problem with this approach is that conflicting updates that happen concurrently are handled by taking the one with the greater timestamp which may not always make sense
this is where multi-value register shines

### multi-value register
keep track of all the concurrent updates and return them to the client application and allow them to choose which update to keep and the rest to discard

