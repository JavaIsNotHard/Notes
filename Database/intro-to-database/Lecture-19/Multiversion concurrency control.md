Introduction
- creates multiple version of a single logical object in the database 
- when a txn writes, it creates a new version of the object 
- when a txn reads, then it reads the most recent version of the object 

- the job of the txn manager in a read operation is to make sure the version of data item is read in a serializable manner

- MVCC works in the principle of readers do not block writers and writers do not block readers. Why?
	- suppose we have a writer thread and a reader thread running concurrently of the same txn
	- for the writer thread to write, it creates a new version of the same data item thus if there was a context switch to a reader thread then it would read from another location than what the writer is writing to 
	- similarly for a reader thread, the location that the reader readers vs the location where the writers writes is going to be different hence no conflicting operation occurs between write and read
- MVCC without garbage collection allows for time traveling queries which allows readers to perform query execution on data items written on the past

- when txn ti creates a new data item then it creates a new version of the data item and sets the read and write timestamp for that data item as TS(Ti)
- the read timestamp of the data item is updated when the read-timestamp of data item < TS(Tj) 

## According to intro to DB CMU
- MVCC has 2 timestamps 
	- begin-timestamp -> timestamp when a particular version of the data was created
	- end-timestamp -> when the visibility of the data item end i.e timestamp of another txn that created a new version
- A status table is used which contains the commit status of all active txn 
- MVCC rules
	- read rule : used for preventing dirty reads
		- a txn with TS(Ti) can read a data item whose TS(ti) is between the range begin TS and end TS of a particular data item 
		- Also the data item must be committed (this can be done by looking at the status table of all txns)
	- write rule: used for preventing write-write conflict
		- when a new txn tries to write to a data item that is not committed and its write timestamp is less than the current txn's timestamp then it is stalled 
- MVCC is not serializable. Why?
	- because it is susceptible to write skew 
		- what is a write skew problem 
			- this normally occurs when you see a snapshot of database at the start of the txn
			- because two txn running concurrently will have their own version of the same data, modifying it will not generated any conflict until the data is committed to the global database
			- the classic example of 2 doctors making a leave appointment is an example of write skew problem
- snapshot isolation is an isolation level implementing using MVCC

## snapshot isolation
- each txn sees a snapshot of the database at the start of the txn 
- any read/write/update/delete operation are performed on that snapshot data



## Design decision for MVCC
- which concurrency control protocol to use 
	- timestamp ordering
	- optimistic concurrency control
	- two phase locking
- version storage 
	- deals with how we are storing these versions
	- implemented as linked list where one node of a list points to the location of the next version of the list
	- there is the head of the chain from which the traversal starts from 
	- we also need to deal with where the versions are stored and how they are stored and their order (oldest to newest or newest to oldest)
	- approaches to do version storage 
		- append-only storage
		- 
- how to use garbage collection
- index management 
- deletes

