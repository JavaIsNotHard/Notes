## Conflict serializable & its pitfalls
- conflict serializability verification of a given schedule can be done using the precedence graph.
- This requires that the DBMS know the operations in the txn beforehand such we can either swap operations or use precedence graph.
- For dynamic transactions, we need different approach for the verification and guarantee of conflict serializability. 
- we have various approaches which includes: 
	- lock based protocol
	- timestamp based protocol
	- validation based protocol

## Basic lock types
- Shared lock -> can be held by multiple txn at the same time. Used mainly when reading data items from database
- Exclusive lock  -> cannot be held by multiple txn at the same time. Used when either one of txn is doing a write operation.

- we can use shared lock between multiple txn because read-read operation between txn do not produce conflict whereas any other operation such as read-write, write-read or write-write produces conflict.

![[Screenshot 2024-11-24 at 09.25.02.png]]

- there are schedules where conflict can occur even when using basic locking protocols
- to remove this problem, we use a better version of the lock based protocol called the two phase locking protocol.

## 2 phase locking
- growing phase  -> activated when a txn acquires a lock
- shrinking phase -> once the txn releases the lock. Once in shrinking phase the txn can no longer go back to growing phase i.e once the txn has released the lock it can no longer reacquire the same lock. 
- This means that all the operations of a txn should happen between the growing and shrinking phase.

- 2 phase locking still has the problem of cascading rollback where if we abort a single txn, it causes a cascading rollback of other txn that read its writes.
- This problem can be solved using strict 2 phase locking.

## strict 2 phase locking
- in this approach the exclusive lock needs to be held till the txn commits such that another txn cannot read data item that has not been committed hence avoids the problem of cascading rollback.
- There is another variant called rigorous 2 phase locking which holds all (not only exclusive) till txn commits.

- locks are acquired automatically by the DBMS based on the reads and writes given by the query
- when a txn issues a read(Q) operation then the DBMS system acquires a shared lock on data item Q
- when a txn issues a write(Q) operation then it checks if there is a shared lock lock-S(Q) on data item Q, if there is then we upgrade(Q) the lock. Else we acquired the exclusive lock lock-X(Q)
- All locks are released after the txn aborts or commits.

## Lock manager implementation

## Deadlocks detection & avoidance 

## Multi level granuality

## database anomalies 
- dirty reads 
	- reading data written by other txn that has not committed yet
- non-repeatable reads 
	- 
- phantom problem 
- write-write conflict (lost updates)
- write skews 
- lost update

## isolation levels
- read uncommitted 
- read committed 
- repeatable reads 
- snapshot isolation