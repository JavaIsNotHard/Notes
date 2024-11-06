simple locking 
use lock and unlock to make sure that serializibility is maintained 

types of locks 

2 phase locking 

deadlocks 

hierarchical locking 

locks in database separate transactions that are running at the same time 
locks in database protect the content of the transaction during the lifetime of the transaction 
There are typically 4 types of locks: shared, exclusive, update, intention
The locks are managed by a lock manager 

Basic types of lock 
- s-lock (shared lock)    - every transaction can read the data locked by a shared lock. no two txn can write at the same 
- x-lock (exclusive lock) - only one transaction can read and write to a data object at a single time

 txn request locks from lock manager. 
 lock manager upgrades the lock of a txn
 lock manager is also responsible for keeping an internal state of a lock-table which contains information about which txn holds the lock and which txn are waiting to acquire a lock 
 lock manager is also responsible for deadlock detection and deadlock avoidance 

  Two phase locking 
  - growing phase 
  - shrinking phase