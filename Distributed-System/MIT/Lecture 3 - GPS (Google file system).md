
## Network file system 
- has two main components 
	- client side file system 
	- file server 
- users send request using a common FS api such as read() and write() to interact with the file system 
- the job of the client side file system is to send this request to the file server and get back the correct response 
- the earliest successful implementation of a network file system is the sun's NFS which had two major goals in mind (mainly NFSv2)
	- simple 
	- fast server crash recovery 
- NFS file servers are made stateless 
	- the server does not keep track of anything that happens at each client 
- Why not stateful?
	- suppose a client does the following operations: open(), read(), read() and close()
	- the client gives the filepath and asks the server to open the file i.e create an entry in the open file table of the server
	- the server creates the file descriptor and returns it back to the requesting client which then for all subsequent requests sends the file descriptor to read and write to the file 
	- here the file descriptor is a shared state between the client and the server 
	- here is why having a shared state is not good:
		- suppose the server crashes after the first read() and before the second read(), the first read() is done successfully but when the server restarts after crashing and tries to execute the second read() then it fails because the file descriptor that was open before is not present in memory because of the crash 
		- also if the client itself crashes then the server would not know when to close the file descriptor because the client after crash will never send a close() request anymore 

## NFS protocol 
- one of the main components of NFS protocol is the [[file handle]]
- clients and servers in NFS protocol are first connected through the [[NFS mount protocol]]
- other important components of the protocol includes 
	- LOOKUP
		- used to obtain the file handle 
		- the client passes the directory file handle and name of the file and the handle to that file
		- for example, if the application running in the client-side FS opens a file /foo.txt then it sends a request to the server, passing it the file handle of the root directory as well as the name of the file and if the request is successful then the server returns a file handle and the attributes of foo.txt (attributes are just file metadata i.e info that we get from the stat() command)
		- once the client gets the file handle then it can start sending the READ and WRITE protocol messages along with the file handle, offset within the file and no of bytes to read 
	- READ:
		- used to read data from the server by passing the file handle along with the READ message protocol
		- we also specifiy the offset of the file and the no of bytes to read from the file 
		- the server then returns the data along with the most up-to date attribute of the read file from the server or error in case of failure
	- WRITE:
		- it is similar to READ where instead of the server sending the data, here the client is the one sending the data to the server 
	- GETATTR and more:
		- used to get the attribute of the file
- the client keeps track of all the states of the file in the its own open file table
- the file table is index by the file descriptor 
- each application FS send by the the application running in the client is translate to NFS protocol messages such as LOOKUP, READ, WRITE etc. this is why tracking the state of all the files is important


idempotent -> effect of performing operation multiple times is the same as performing the operation a single time

- failure is handled in NFS protocol by redoing an operation if not successful the first time i.e if a write operation were to be stated as failed then the client would retry the write operation until it gets a success status back from the server 
- most of the request in the NFS message protocol are idempotent i.e performing multiple operation results as if only a single operation is being performed. LOOKUP and READ are inherently idempotent because they do not update any FS states or information
- But WRITES are also idempotent even though they update data on FS. This is because even if the pervious operation succeeded in server but the return message failed to reach the client hence the client retries the operation, in this case the same request with the same offset and the same data will be sent to the server meaning that the changes of the previous operation and the current operation are the same 

- NFS client performance can be improved by the introduction of client-side caching
- better performance is needed because sending data between the client and server through the network is expensive than reading and writing data to disk and in memory 
- first time the client reads, then the returned data is cached in the client buffer such that subsequent read request results in fast read operation thus making the initial read request expensive but all other request perform better 
- write buffering can also improve performance, for a write request, the client immediately buffers the write data in its memory and informs the user that the request was complete (making the user perform other operation). Meanwhile, all the buffered write data can be wrote in a single request rather than send unique request for each write operation

- even though caching gives performance gains it also has its downfalls such as 
- suppose we have 3 clients and a single server then the following scenarios can happen:
	- update visibility 
		- client 1 buffers its write into its cache before sending it to the server and then client 2 buffers its write (update to the same data)
		- when another client 3 reads from the FS then it reads old stale value written by client 1 or before
	- stale cache 
		- client 2 has flushed its updates to the server but client 1 still has cached data for the same data item flushed by client 2
		- if client 1 were to read the data item then it would read the stale data item from its local cache
- these problems can be solved by 
	- flush-on-close 
		- the first problem can be solved using this method
		- when the file is written to and subsequently closed by the client application then the buffered data is flushed immediately to the server 
	- GETATTR protocol
		- the second problem can be solved using this method 
		- before reading data from the cache, the client first validates the data in cache by sending the GETATTR message protocol to the server and check the last-modified date and time
		- if the validation fails then it has to read from the server and update the cache else it can read from the cache itself
- using GETATTR to validate cache has its own set of problems
	- the server is flooded with the GETATTR message for every read request from the client 
	- this problem was solved using attribute cache where the new attributes were fetched after certain time interval automatically 
- problems with caching in the server-side using write buffering
	- data from disk can be buffered in the main memory such that read request do not hit the disk and can be resolved by the cache 
	- returning a success after writing to memory rather than disk can have problems such has crashes can miss writes to the disk even though the client was informed that the write was successful
	- this can be remediate by only sending success response after the data has been written to disk 
	- other approaches is to use battery backed memory which retained data even if after crash

## From the official whitepaper of gfs 
- Component failures are the norm rather than the exception. The file system is being accessed by number of client machines. Failure is also inevitable be it an OS bug, a software bug, hardware bug, power supply failure and many more. 
- Files are traditionally huge. Files consists of many application objects such as web documents. Each file can grow rapidly and upto TBs in size because of this it is going to be difficult of manage billions of KB sized blocks or pages making up the file. 
- Files are mutated by appending new data rather than overwriting existing data. There are a lot of data access patterns such as data streams (such as live sensor data), large data repository (large database files), data generated from other machine, archival data and many more. Given this access pattern of data, appending becomes the focus performance optimization and atomicity guarantees


## design assumptions of GFS 
- system is built using machines that can and will fail. the system needs to monitor these failed machines and recover from the failure promptly
- each system stores a modest amount of file where files range from 100 MB to few GB 
- workload consists of types of read 
	- stream read 
	- random read
- workload has writes that append data to files 

### Interface of GFS 
GFS has two main things: 
- snapshot -> creates a copy of a file or a folder tree
- record append -> allows multiple clients to append data to a file concurrently while guaranteeing atomicity. it is implemented such that addition locking is not needed

### Architecture of GFS 
single master and multiple chunkserver
each chunkserver runs a linux file system that contains files 
files are divided into chunks 
each chunk is identified by a globally unique 64 bit chunk handle 
checkserver stores chunks in local disk as linux files 
chunkserver reads and writes chunk data specified by the chunk handle (which chunk) and the offset (within the chunk where)
each chunk is replicated in multiple chunk servers 

master maintain all file system related metadata 
master communicates with chunk server in heartBeat messages to give it instruction and get its state information 

GFS client communicates with the GFS master server 
GFS client implements the file system API that is used to communicate with the master and the chunk server 

caching is not done is either the chunk server and the GFS client because the dataset that GFS deals with are huge and do not provide performance benefits on caching 
chunk server stores data in linux file and so linux's buffer cache already keeps frequently accessed data in memory 

GFS master is not involved directly with the read and write operation
GFS client asks the server which chunk server it should make contact with and caches this information for many subsequent operation

The GFS client translates the filename and the offset from where to read from into chunk index within the file 
then it sends a request to the master containing the filename and the chunk index 
the master replies with the chunk handle and the location of all the replicas 
the client then sends request to one of the replicas (typically the one closed to the client) with the chunk handle and the offset within the chunk 
further reads from the same chunk does not require any more client-master interaction until the cached infromation expires or the file is reopened 


Chunk size is a key design parameter 
google uses 64MB as the chunk size 
it includes the following advantages:
 - it reduces the clients interaction with the master because request to the same chunk only requires single request to the master 
 - reduced network overhead by keeping persistent TCP connection to the chunkserver over extended period of time because on a large chunk clients are likely to perform many operations in a given chunk 

master meta data 
- contains information such as 
	- files to array of chunk handle mapping i.e given a filename returns all the chunk handles all the chunks of the file 
	- list of all replicas of each chunk handle
	- contains version number to identify the latest copy of the chunk
	- primary replica node  i.e which server is the primary chunk server for the replica
	- lease expiration time for the chunk server as the primary replica node
- contains all information in its main memory 
- write operations or updates are written to disk to a log structure storage 
- checkpoints are also introduced for continuing a master from failure

- the master does not keep a persistent record of which chunk server has a replica of a given chunk, instead it polls the chunk server for that information 
- this is because chunkservers join and leave the cluster therefore eliminating the problem of keeping the master and chunkserver in sync

master periodically scans its internal data structures to implement chunk garbage collection, re-replication because of failed chunk servers, chunk migrations to balance load 

how write operations are performed in GFS 
- the client first needs to know which chunk server has the offset of the newest update of a file 
- multiple clients updating the file 
- each client will write to the file and change the current offset of the file to some new value
- when a new client wants to append to the file then it needs to know the offset change caused by the last newest write so that it can continue append from that offset 
- for write operations there needs to be a primary chunk server 
- there are two cases for primary chunk server (the client communicates with the master server)
	- there is a primary chunk server 
	- there is no primary chunk server 
		- find the chunk server with the most up to date updates 
		- the most up to date chunk server is the one whose chunk has the version number equal to the version number stores in the master data structure 
		- assign one of the latest chunk server (if multiple chunk server has the latest version number) as the primary and others as secondary 
		- increments the version number and writes that to disk 
		- tells the primary and the secondary which chunk server is the primary and the secondary and also the latest version no
		- clients push data to all the replicas, all chunk server will keep the data in its internal LRU cache buffer 
		- once all the replicas have acknowledged receiving the data, the client sends the write request to the primary server. The primary assigns serial number to each write request 
		- the primary forwards those request to all the secondary servers along with the serial number such that the operations are done in same order in secondary as in primary 
		- 


### Big storage 
Why is it hard? 
- get big aggregate performance and harness the resource of 100s of machine to get their work done. 
- performance -> split data in many server and read from many server in parallel (Sharding)
- fault -> See constant fault when sharding because huge no of machines are involved 
- we need automatic fault tolerance system
- fault tolerance -> can be removed by replication of data (data can be out of sync between the replicas)
- risk of inconsistency 
- clever design for the inconsistency 
- if you want consistency then you pay with low performance 

What is strong consistency 
- Making the client think that they are talking to a single server.
You have one server with single thread that processes request one at a time and suppose that two clients send a write request at the same time and the server receives the request at the same time then what will happen? will the change done by the first server be persistent or the change done by the second server?
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
