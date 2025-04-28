### isolation
1. dirty write : happens when a transaction overwrites the value written by another transaction that hasn't committed yet 
2. dirty read : happens when a transaction observes a write from a transaction that hasn't committed yet 
3. fuzzy read : happens when a transaction reads an object value twice but sees a different value in each read because another transaction updated the value between the two reads
4. phantom reads : happens when a transaction reads a group of objects matching a specific condition, while another transaction concurrently adds, updates, or deletes objects matching the same condition


an isolation level protects against one or more of these types of race condition
the stronger the isolation level, the more protection it offers against race conditions, but the less performant it is

read uncommitted (forbid dirty writes)
read committed (forbid dirty reads)
repeatable read (forbid fuzzy reads)
serializable (forbid phantom reads)

to add a real-time requirement on the order of transaction we need a stronger isolation level: strict serializability: serializable + linearizable

after serializability, the challenge becomes maximizing concurrency while still preserving the appearance of serial execution which is defined by a concurrency control protocol which can be categorized into pessimistic and optimistic 

pessimistic concurrency control can be guaranteed by using 2Pl protocol (2 phase locking)
this protocol has two phases: growing phase and the shrinking phase
in growing phase the transaction is allowed only to acquire the lock and not release them 
in shrinking phase the transaction is permitted only to release locks but not acquire them 
problems which this protocol includes cascading aborts, deadlocks 

an optimistic concurrency control executes a txn without blocking based on the assumption that conflicts are rare and transactions are short-lived

