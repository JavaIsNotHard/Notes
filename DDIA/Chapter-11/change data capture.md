- this is way to track data changes in the database and then deliver those changes to other derived systems

- basic idea is to use the database log such as WAL or replication log or binlog to reconstruct data in such a way that they can be used by different data storage systems
- ![[Screenshot 2024-12-17 at 1.32.07 PM.png|600]]
- CDC makes sure that all changes made to the system of record database is also reflected to the derived data systems
- the log consumers are called derived data systems

- a single database is required for input to the broker's queue, this database is known as the [[system of record]] since it contains the latest contents of the database 
- records can be written as even to the broker by parsing the replication log of the database
- change data capture is an asynchronously process meaning it will not wait for the consumer to finish before committing the changes on the database

database triggers can be used in our case, by registering that observes all changes to data tables and add corresponding changes to a changelog table
another approach would be to parse the replication log itself

## Initial snapshot
- we can construct a new derived data system by replaying the log 
- there can be cases where holding log for all the changes is going to take up a lot of disk space 
- this is where we can use the snapshot of the current state of the database
- the snapshot of the database must correspond to a known position in the change log such that the derived data system can get a point of reference where it can restart its execution after the snapshot has been created


## Log compaction
- we can perform log compaction inside the broker to remove duplicate keys in events and to make sure the system has up to date changes on the data in the database 
- there is a background process that periodically looks at the disk log record and checks for duplication in the log
- in log based message broker, as long as the key is not overwritten or deleted then the data remains in the log 
- the size of the log depends on the contents of the database rather than the write operation performed on the database because if the same key is used multiple times i.e overwrite the value those new values are garbage collected in the background in the future
- using this approach, we can make the consumer point to the 0 offset of the broker and then start reading data sequentially. this guarantees to contain the most recent value for every key in the database which means we get a full copy of the database without performing snapshots of the database 

Log compaction is used to setup the entire database without having to take snapshot of the entire database which would be slow and inefficient

if the log is setup such that every change has a primary key and every update for a key replaces the previous value for that key 

then whenever we are rebuild a derived system then we can start the consumer at offset 0 of the log and make it scan the log sequentially and perform every operation of the log to keep the log in sync with the data source i.e the database. this allows systems like apache kafka to no just act as a messaging system but also as a durable storage of the current state