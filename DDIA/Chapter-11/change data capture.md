- basic idea is to use the database log such as WAL or replication log or binlog to reconstruct data in such a way that they can be used by different data storage systems
- ![[Screenshot 2024-12-17 at 1.32.07 PM.png|600]]
- CDC makes sure that all changes made to the system of record database is also reflected to the derived data systems
- the log consumers are called derived data systems

- records can be written as even to the broker by parsing the replication log of the database
- change data capture is an asynchronously process meaning it will not wait for the consumer to finish before moving on to execute other tasks
