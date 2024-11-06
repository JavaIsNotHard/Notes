## Snapshot isolation and repeatable reads 
- read committed has the non repeatable read anamoly which basically means the same user sees different version of the data at different time. This is also called lost read for a temporary time because the data will eventually show up
- There are cases where non repeatable read are critical:
	- When performing a system backup for a large dataset then it would take a lot of time. While the backup happens we can continue the write to the database. This could end up with some part of the database containing older version of the data and some part containing newer version.
	- When running analytical queries, periodic integrity checks that everything is in order (monitoring for data corruption). These queries will return nonsensical results if they observe different parts of database at different time.
- Snapshot isolation prevents this problem

### Snapshot isolation 
- Have a snapshot of the database for each transaction such that each txn sees only their write values 
- each txn reads from a consistent snapshot of the database i.e the txn will sees all the data that was committed in the database at the start of the transaction. 


## Write skews and phantom 
- write skews are a type of race condition that can happen when concurrent write takes place. 
- when two or more txn read overlapping data, and then update based on those reads without directly conflicting with each other. 
- Suppose we have doctor call on application where patient call doctor for appointment, at a particular pointi n time atleast one doctor shoudl be available to take the call. Suppose Alice and Bob are two doctors on call and they are both unwell and request to leave. Suppose they press the request to leave button at the same time and two txn start at the same time then the following things can happen. They check the condition that there are 2 doctors or more doctors or call. Both satisfies the condition and goes on to set false for on shift.
![[Screenshot 2024-11-04 at 09.48.30.png]]

## Serializability
- serializable isolation is considered to be the strongest isolation level 
- Even though the transaction may execute in parallel, the end result is as if they had been executed in a serial fashion i.e without any concurrency. 
- Options for implementing serializable isolation: 
	- Actual serial execution
	- two phase locking 
	- serializable snapshot isolation
### Actual serial execution
- remove concurrency entirely 
- execute only one transaction at a time in a serial order on a single thread 
- prevents conflict between transactions
- what made single thread of execution possible for transactions?
	- RAM got cheaper hence we could store most of the data in memory and not on disk
	- OLTP workload are short and finish quick whereas analytical workload require consistent read data hence this workload can be execute using snapshot isolation outside of the single threaded execution loop
- In order to get the most out of a single threaded execution, the transactions need to be structured differently from their traditional form.

#### encapsulating txn in stored procedure 
- early days of database, the intent was that all the database transaction could be encompassed in a single flow i.e in a single transction can handle all the user activities. 
- It would be neat if we could store the entire process in a single transction such that the operations are atomic.
- Unfortunately this is not ideal becauase in most user facing application users take time for making decisions so dedicated transactions for each user while the user takes time will create a lot of concurrent transaction that are mostly idle. 
- Many databases are not made to handle a lot of concurrent transaction at the same time so most OLTP applications keep transaction short by avoiding waiting for user within the transaction
- Even if we remove the user idle time we still have the problem that most OLTP workload are executed interactively i.e one statement at time. The user makes a query, reads the result and modifies the result and stores the result back. 
- Each request takes a network delay to bring from the application code (user) to the database and execute the query. 
- In a single threaded database, the database would have to wait for the application code to send the remaining queries for the rest of the transaction. 
- To prevent the idle time of execute, stored procedures (set of SQL statement made ready beforehand inside the query executor waiting for arguments to be passed into) are used 
![[Screenshot 2024-11-04 at 13.48.12.png]]

### 2 phase locking
- similar to dirty write prevention but has stronger lock requirements.
- this has read lock and write lock 
- when a txn wants to read a object then it holds the read lock first and if a txn wants to write to an object then it holds the write lock first. 
- ![[Screenshot 2024-11-04 at 16.13.06.png]]
- A shared object can have more than one read locked transaction reading the data object at the same time but as soon as a write locked transaction comes it the new txn has to wait until all the read locked transactions are committed or aborted.
- Similarly if an object holds a write lock then another txn whether it has a read lock or write lock has to wait for the first txn to complete. 
- If a txn reads first and then writes then it may upgrade its shared lock to an exclusive or write lock.
- After a txn has acquired a lock then it must hold the lock until the end of the txn.
- This approach gets us serializability must lacks on the performance. 
- The latency of the response depends on the number of txn waiting in queue for a lock to be released by another txn.
- Deadlocks are also another problem with this approach

### predicate locks
- in the write skew problem, when two txn entered the application code block at the same time it resulted in lost updates and unsatisfied conditions. 
- This problem can be solved using predicate locks. 
- Predicate locks are similar to 2 phase locks in the sense that both have a shared/exculsive locks.
- 2 phase lock belongs to a particular object (i.e a row in a table) whereas predicate locks are held by all objects that match some particular condition
`SELECT * FROM bookings WHERE room_id = 123 AND end_time '2018-01-01 12:00' AND start_time < '2018-01-01 13:00';`
- This query searches for all the room that are free at a particular time period