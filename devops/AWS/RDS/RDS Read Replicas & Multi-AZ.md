Read Replicas are used in RDS to enable scaling the main database

we can have replicas within the same AZ, in different AZ and in different regions

we can have upto 15 replicas for a single main RDS instance

eventually consistent asynchronous replication model of RDS

here the replication are eventually consistent which means that the clients can get back stale data if the read replica have not received the most upto date data from the main database instance because eventually consistent model doesn't guarantee this

Replica instances can also be promoted as the main database rather than just processing read request, they can now process both read and write request

one of the most common use case of read replica is when we want to perform analytics on the database. Instead of running analytic queries on the main DB (they are heavy on the DB), we allow analytic queries to the read replica. This makes the main production database unaffected 


Replication inside the same region but different AZ will not cost
But replica between different regions will cost

we can make our read replicas standby servers as well by making sure that the replication are synchronous rather than asynchronous

### Multi-AZ (Disaster Recovery)

Multi-AZ is mainly used for disaster recovery which means if the main DB is down or affected then we can use another DB as a recovery which will have the most upto date data

In this model, we have a standby DB instance which is connected with the main DB instance. 

The main DB instance synchronously replicates itself with the standby instance

Multi-AZ has a one DNS name for both the main server and standby instance which allows automatic failover, which means if the main DB is down then it automatically routes the DB traffic to the standby server without any downtime

This is not used for scaling because the standby server does not accept both read and write request

HOW DOES THIS HAPPEN??? i.e how to go from single AZ to multi-AZ

the main instance creates a snapshot
a new database is restored from the snapshot
once the most upto date snapshot is restored then the main instance starts synchronization between the two databases