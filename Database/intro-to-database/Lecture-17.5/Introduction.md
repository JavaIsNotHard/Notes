## Timestamp-ordering protocol
- txns are ordered based on timestamps
- each txn is assigned a unique timestamp before it begins its first operation
	- the timestamp value can be system clock time 
	- or it can be a logical counter
- A data item Q is associated with two values:
	- write-timestamp(Q) -> the largest timestamp of any txn that executed a successful write to data item Q
	- read-timestamp(Q) -> the largest timestamp of any txn that executed a successful read to data item Q.

- why is read-write operation a conflict -> this creates non-repeatable reads, when the same txn re-reads the same data item in quick succession it gets two different results.
- why is this anamoly a bad thing? -> this violates the isolation property of txn i.e ensuring a consistent view of the data items throughout the lifetime of the txn.

## Rules of timestamp-ordering protocol
- when the txn performs a read operation on data item Q then: 
	- if TS(t1) < write-timestamp(Q) then the txn t1 is trying to read value written b a future txn so this operation is rejected and the txn is rollbacked
	- if TS(t1) >= write-timestamp(Q) then the txn t1 reads value written by itself or some past txn so this operation is allowed and the read-timestamp(Q) is set to the max of read-timestamp(Q) and TS(t1).
- when the txn performs a write operation on data item Q then:
	- if TS(t1) < read-timestamp(Q) then it creates read-write conflict hence the operation is rejected and the txn is rollbacked back
	- if TS(t1) < write-timestamp(Q) then it prevents write-write conflict and rejects the operation.
	- any other case the txn is allowed to write the value and change the value of write-timestamp(Q) to TS(t1)

- pros of this protocol
	- prevents deadlock
	- ensures conflict serializability
- cons of this protocol
	- starvation of txn
	- can generate non-recoverable schedules

- non-recoverable schedules can be prevents using following methods
	- preventing writes to be visible until the txn commits. 
		- basically buffer the write values such that any uncommitted values are not visible to other txns.
	- using some form of locks to prevents reads of uncommitted data. 

- thomas' write rule