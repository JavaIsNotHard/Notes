## From the official whitepaper of gfs 
- Component failures are the norm rather than the exception. The file system is being accessed by number of client machines. Failure is also inevitable be it an OS bug, a software bug, hardware bug, power supply failure and many more. 
- Files are traditionally huge. Files consists of many application objects such as web documents. Each file can grow rapidly and upto TBs in size because of this it is going to be difficult of manage billions of KB sized blocks or pages making up the file. 
- Files are mutated by appending new data rather than overwriting existing data. There are a lot of data access patterns such as data streams (such as live sensor data), large data repository (large database files), data generated from other machine, archival data and many more. Given this access pattern of data, appending becomes the focus performance optimization and atomicity guarantees

### Interface of GFS 
GFS has two main things: 
- snapshot -> creates a copy of a file or a folder tree
- record append -> allows multiple clients to append data to a file concurrently while guaranteeing atomicity. it is implemented such that addition locking is not needed

### Architecture of GFS 
single master and multiple chunkserver


### Big storage 
Why is it hard? 
- get big aggregate performance and harness the resource of 100s of machine to get their work done. 
- split data in many server and read from many server in parallel (Sharding)
- See constant fault when sharding 
- we need automatic fault tolerance system
- replication of data 
- risk of inconsistency 
- clever design for the inconsistency 
- if you want consistency then you pay with low performance 

What is strong consistency 
Making the client think that they are talking to a single server. You have one server with single thread that processes request one at a time and suppose that two clients send a write request at the same time and the server receives the request at the same time then what will happen? will the change done by the first server be persistent or the change done by the second server?
The answer to this question is tricky because there is no single answer to this question. Why? Because we have a server with a single thread that means when two request comes in only one can be handled at a time. And if two request comes at the same time then either of the request can be handled.
Here a single server would be strong consistent if another client requests a read on the same data the previous two clients wrote to, then for the server to be strong consistent it should see the data written by the last client request that would be the second request that was satisfied. 

The problem with a single server model is that it has poor fault tolerance which means if the server crashes or the disk dies then there is no other source where data can come from and we are basically left with nothing. 
So in distributed system we built replicated system. This is where the problem starts leaking in. 

Bad replication design 
We have two servers with exact replica of data. Table of keys and values. The goal is to keep this two table identical so that if one server fails then we can read and write in another server. This means that writes must be processed by both the servers. Reads have to processed one server because if they read from both and one fails then it is not fault tolerant. 
The reason this is a bad design is because we do not have an order t receive the data from the client. For example, we have two servers and 2 clients that send 2 write requests each to the server. Suppose client 1's first request changes the value of X to 1 and later a second request changes the value of X to 2. Also suppose that client 2's first request is to change the value to 2 and the second request is to change the value to 1. This leaves us with an inconsistent state where server 1's X has a value of 2 whereas server 2's X have has 1. 
How to fix this bad design?
More communication between the server 

GFS 
fix the bad replication design 
goal of GFS
big and fast 
universal reusable storage system 
Sharding data to multiple servers for more peformance automatically when request from users arrive
automatic recovery 

GFS was designed to run in a single data center 
Designed for internal use fro google employees not for sale to customers for use 
tailored for big (gigabytes to terabytes) sequential file reads and writes

What the master is storing 
- filename -> array of chuckID or chuckhandle -> tells you where to find the data or the ID of the data 
- chuck handles -> list of chunkserver that holds the replication of that data 
