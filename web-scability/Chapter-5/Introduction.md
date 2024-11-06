How to scale the data storage servers or databases 

Before, vertical scaling of database server i.e adding more disk space, RAM and computing power was enough to scale the database properly 
But with the rise of more internet users we need to think about the aspect of concurrency. Previously if one database storage server could handle all the request then nowadays we need a cluster or clone of each server for the database system to scale properly. For this horizontal scaling has become necessary in my ways. 

## Scaling with MySQL
There are many ways to scale relational database which includes
1. Replication 
2. Sharding 

### Replication 
Have multiple copies of the same data on different machines 
Helps to synchronize the state of two servers where one server is the master and the next is the slave. 
When using the replication technique the clients can read through your slave server but can only write through your master server. To maintain consistency between the master and the slave, the the slave runs the last ran update statement such as create, insert, update and delete in its own machine. 

The core concept is to replicate the content between master and a slave
All the data-modification commands such as updates, deletes, inserts or create are sent and written to a binlog file, with a time stamp and a sequence number 
Once the statement is written to the binlog, then it can be sent to the slave server to execute the statements in the binlog to make it consistent with the master server 
The master server are executing a statement will return a response to the client and continue performing other transactions. The slave server can request the binlog file from the master server anytime. The slave server provides the sequence number of the statement that it last executed. The slave server then writes all these statements to its own relay log 

MySQL replication are asynchronous which means that the master server does not wait for the slave server to execute the content of the relay log. 
This allows decoupling of the master from its slave which means that you can easily connect and disconnect slave server without the master server being affected. 

This also allows multiple slave server replication where the read queries are distributed through all the slave servers. The slave machines do not communicate with each other 

You can have different slave machines running different read queries such as fast and slow queries 

When a slave dies then it does not affect the performance of the storage system because another slave server can be brought in and since the master server record of all the changes, the new slave server can connect to the master server and ask for all the pending changes it needs to apply.

### Failure of slave vs failure of master
Failure of slave server is not a big concern but failure of the master server is a big concern because the master server holds all the upto date state of the database and the slave server may not be upto date with the master server due to replication delay 
First you need to find the slave which has the highest sequence number or which is the most upto date server.
Then you appoint that server as the master server 
If you have more than one slave then we need to make sure that all the slave server are synchronoized with the master server 


### Master-Master configuration
Due to the complex nature of recovering of the master server we introduce a new topology called the master to master configuration
You introduce a new master which takes in all the write commands and syncrhonizes with the other  master server
In MySQL replication the statement includes  the server which appended in the binlog which means that when another server replicates the binlog it will not rerun the statements that it produced.
In case of failure of one master, another master can take control and start operating as if nothing happened 

How to manage software upgrade or maintenance
If you have master A and master B and you wanted to upgrade master A server then the following steps take place:
1. You upgrade the master B and its slaves 
2. You stop all the writes coming into the master A
3. You wait for all the writes from A to replicate to master B 
This method makes sure you are not writing to the same server at the same time 


Writing to two master server at the same time is not advised because of data inconsistency and high complexity

If you want to scale your active data set to a large size (about 5 tb) then this is not a good use case because all the data set must be present on each machine

Active data set are those which are accessed frequently which means that the database can buffer it in memory or fetch it from disk. When the data set is small then you can buffer it in memory but when the active data set is large then we need to perform disk I/O which is random in order 

Active data set depends on the type of the application that we are developing. For example in a e-commerce site, data such as information about some purchase you made are active in the time or the purchase but slow the use of the data is going go down. 
Another example is going to be a music streaming application. For a popular artist the songs that they publish are going to be streamed by a lot of people for almost all day of the year which means the active nature of this data is not going down but is rather consistent with time.

Replication is not a way to solve the problem of large active data set problem. 

MySQL replication is an asynchronous process and any changes to the master needs some time to be applied to the slave itself. The replication delay (which is the time required for the slave to be in consistent state to the master server) creates timing issue which can result in inconsistent data or stale data being returned to the user. 

The replication lag is high because of the nature of MySQL slave servers. All the slave server run in a single thread which means that parallelism is not possible. 

How to avoid timing issues:
1. Caching the data that was just written to the client in a database in-memory cache such as redis or memcached
2. Sending critical read request to the master server to get the most up-to date data 
3. Minimize the replication lag. This can be achieved by directly executing all the statements in the master to all the slaves instead of writing to the binlog and after some time reading the statement to update the slave.

Open source tools like pt-table checksum or pt-table-sync can help you discover inconsistency in the data set. 

It is also a good strategy for young startups to use hosted MySQL solutions such as Amazon Relational database. This type of services gives you a lot of features as well as easy to maintain for small applications which is going to be hard in self-hosted database servers. 

### Data sharding (partitioning)
Basically you break down a large data set into small components and then you pour each small components into separate buckets or data storage. 
For example, you have a large table with about 100,000 columns. The key ideas to to break this large data into smaller dataset which could be each of 100, 1000, or even 10,000 data sets. Once you break the data down, you place each of them in separate servers which means you do not now have to each through those 100,000 column but rather just 10,00 or even 1,000 columns. 

The first step to data sharding is to choose a sharding key. The sharding key is responsible for the identification of the server which holds the data that you need such that you do not scan all the database server for the data. 

For a online store a sharding key could be a userId which uniquely identifies each user. Then we need some algorithms that will redirect us to a particular server when a certain key is given as input. For example a simple algorithm could be something like all the userId that are even will be placed on server 1 whereas all the userId that are odd will be placed on server2. 
Reads and writes both need to respect the sharding algorithm. When we write we need to make sure we are writing to the correct data bucket. 
Each piece of data must reside on a single server and no servers need to communicate or synchrnoize their state or data set with each other. 

The use of appropriate sharding key is a must. For example if we shard based on the country origin then we get irregular amount of data in each server. Server that holds country that have more population will contain more data set whereas the server holding the data set of country with small population will have small data set. 

It is not possible to make each bucket of equal size but we need to ensure that each bucket is small and you have a lot of them to end up with a good distribution of data 

Sharding allows you to scale database horizontally 

Disadvantages of sharding:
- you cannot make execute queries spanning multiple shards. you need to run a part of it on each shard and then merge the results 
- You lose the ACID properties not for the individual shards but when making changes across multiple shards 
- modulo-based mapping produces unwanted results, for example if module(3, 8) = 2 where 3 is the number of shard servers and the user_id =8 then we say that the data lies in server 2. Then suppose we ran out of space and added another server clone to the shard server, then the same operation module(4, 8) = 0, which means just adding another server resulted in invalid server entry 

To prevent the last problem (modulo-based mapping), we can use a external mapping which contains all the user_id or some shard key to its respected server no.  This method has a flexibility of allowing cherry-picking of user_id and placing them in a separate server. 



## Scaling NoSQL 
NoSQL was introduced to handle growing large amount of data that was built for scalability by making significant tradeoffs to achieve this. 

Traditionally making sacrifices was not the nature of database designers 
until the CAP theorem which stated that there was no way we can support consistency, availability and partition tolerance at the same time 

In a distributed environment we have nodes (servers) and network connections that allow the connection between the nodes. 
1. Consistency ensures that all the nodes see the same data
2. Availability guarantees that any available node can server client when other nodes fail 
3. Partition tolerance ensures that system can operate in the face of network failures

### Eventual consistency vs Global consistency
Global consistency makes sure that when two clients asks two different server for the same data at the same time then they get the same data all the time 
Eventual consistency does not guarantee this, instead it gives the most recent data it contains which may not be globally the same

Eventual Consistency is an tradeoff that systems use in order to achieve high availability. Clients do not wait for the entire server to be ready before reading or writing data. 

The optimistic approach where you hope for the changes to be made later on brings on conflict data issue. Suppose client  1 and client 2 make an update request to the same dataset in different server then the changes made by client 1 will be replicate in server 2 whereas the changes made by client 2 will be replicate to server 1. This means client 1 and 2 will now look at changes they did not make and two servers will have conflicting results

The solution to this problem is 'most recent write wins'
Another approach is to keep all the version of the data for the same item and then push the responsibility of the conflict onto the client. 

NoSQL data stores empty additional self-healing strategies.
Cassandra database employs a read repair mechanism which helps in the consistency issue that can be found in distributed systems

## Faster recovery to increase availability
Some systems favor availability over consistency while others favor consistency over availability.
A good example of system that favors consistency over availability is mongoDB.
MongoDB auto shards and distributes data among multiple servers 
Only one server has a copy of a particular data and anytime a update needs to be made, it needs to be done through the server which has the actual data. Which means that if the server with the data becomes unavailable then MongoDB rejects all writes to the data. 
MongoDB supports replica sets which basically replicates the data among multiple servers but they only act as replicas or backup for the primary server during failure. 
Whenever the primary server is down then an election is held among the replica set to elect a new primary server. Once a server is elected then replication among the replica set begins which replicates all primary nodes's data to all the replica nodes.
This may look like MongoDB supports both consistency and availability but things are not so easy 
MongoDB replica sets use asynchronous replication of the replica nodes. When a write occurs then the primary node chanegs the data first and then the changes are slowly propagated along the secondary or replica servers. Which means that if the primary node fails before the secondary nodes change their data then the data is permanently lost.

## Cassandra Topology 
NoSQL data stores have some common patterns to distribute data among multiple servers, replicate information, and handle failure.

Features of Cassandra includes:
- all nodes are functionally equal 
- does not have a single point of failure
- all nodes perform the same functions

Clients can connect to any node in the cluster of nodes. 
The node that the client chooses becomes the client's session coordinator. 
The coordinator takes responsibility for all the internal cluster activities like replication or sharding

Each node knows the status of other nodes and what data they are responsible for
They can delegate the query to the correct server

Even though each node has the same functionality, it does not mean they are identical 
Each node has a subset of the overall data set
Nodes communicate with each other to know where parts of the data live in.

It follows wide column approach 
Table contains rows where two rows can have different columns (relational database will need all rows to have the same column)

You can dynamically create fields when needed in NoSQL wide column storage. This means you can make changes rapidly without needing to perform expensive operations like ALTER table 

Fewer tools for searching data. 

Data is partitioned based on rows key, the session coordinator hashes the row key to a number then based on the row key it finds the partition that the row key belongs to 

Replication is also possible in Cassandra but it does not have a master slave server relationship. Every replicated server is equally important 

Based on the partition range (the range can contain multiple server) the query is forwarded to all the servers which means if any one of the server id won then the remaining server can still process the query. 
Queries for failed servers are buffered and replayed when the server becomes available again. 


