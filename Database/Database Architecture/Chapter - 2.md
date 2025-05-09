lightweight thread package which is different from kernel thread of OS thread which are managed by the operating system themselves

the lightweight thread are managed by an application level thread scheduler that runs in the user space. the lightweight thread has the advantage that is has faster context switching time in comparison to OS threads because we do not have to switch between user space and kernel space when using lightweight thread

the lightweight thread also has the disadvantage that all the lightweight threads run in the same process i.e a thread starts a synchronous operation like I/O then it stalls all the other threads in the spawned by the same process. This can be avoided by using asynchronous I/O request using event loops

DMBS clients are those that implement the API that are called application level programs such as JDBC or ODBC

DMBS worker is a thread of execution in the DBMS that does work on behalf of the DMBS client. For each request a DBMS client sends to the server, the creates the same number of DMBS worker threads that processes the request



### DBMS process model for a uniprocessor system 

1. processor per DMBS worker 
2. thread per DMBS worker
3. process pool 

process per DBMS worker
DMBS workers are mapped directly to the OS process i.e each worker run as a separate OS process
this is the easiest to implement because the DBMS can just rely on the OS for stuff like OS protection and scheduling and each DBMS worker will get its own address space meaning no race condition is possible between DBMS workers

Data structures that needs to be shared across DBMS connections such as lock tables and buffer pool are difficult to manage because communication between processes are hard (i guess??)

in terms of scaling, the process per DMBS worker model is not very good because the state information for each process is too large to context switch between concurrency DMBS connection, degrading the overall performance of the system

Thread per DMBS worker
A dispatcher thread is listening for new DBMS client connections
each client connection is mapped to a single thread of execution in the server
the thread runs inside a DBMS server process and once the particular operation is complete, it will wait and listen for next DMBS client connection

this model comes with multi-threading problems such as race conditions, and porting issues due to separate thread interface between difference hardware and OS

process pool 
we create a pool of open process ready to execute SQL statement when new client connection is made
a central process holds all DBMS client connection and as each SQL request comes in from the client, the request is given to one of the process from the process pool
once the process executes the statement to completion, the process is returned to the process pool  and waits for the next request. 
process pool is implemented with a dynamically resizable process pool where the pool grows potentially to some maximum number when large number of concurrent connections hits and the size can decrease if the request number is less 


Shared data and process boundaries
the model described above aim to execute concurrent client request as independent as possible 
but full DBMS worker independence and isolation is not possible because they are operating in the same shared database

in thread per DBMS worker model, data sharing is easy with all threads running in the same address space
in other models, shared memory is used for shared data structures and state this means that there is a region in memory that is available for all DBMS workers to see and update during various DBMS operations

There is also a buffer that needs to be in place that holds the value between the DBMS client and the server and also when the server returns result to the client

Two main types of buffers include
1. disk I/O buffer 
	1. buffer pool: all persistent database data is staged through DBMS buffer pool. in thread per DBMS worker model, the buffer pool is a heap resident memory region that can be shared among all threads. In other models, the buffer pool is allocated in a shared memory available to all processes. when the database needs a page that resides in the disk, it generates an I/O request specifying the disk address and the free memory location in the buffer pool. when we want to flush pages to disk, a thread generates an I/O request to write data back to the disk with the page's current frame in the buffer pool and its destination address on disk. Why buffer pool? buffer pools are used to cache data in memory between the database and the disk such that the database doesn't have to seek the disk for every I/O operation. When reading from the disk, it places the page in the buffer pool and when flushing data on disk it flushes data that resides in the buffer pool. there are two main types
		1. write-back: changes are made to the buffer pool and flushed later on disk
		2. write-through: changes are made to both memory and disk immediately
	2. log tail: log entires are generated during transaction, they are initially staged in a in-memory queue which is later periodically flushed to disk in FIFO order. the queue that temporarily holds the transaction changes that has not yet been committed is called the tail log. A transaction cannot be reported as successful until a log record is flushed to the log device. until the commit log is flushed, the thread needs to hold all the resources that it was holding during its operation
2. client communication buffer: this is the buffer that holds the result tuple returned by the database. client consumes result tuple from a query cursor by repeatedly issuing the SQL FETCH command which retrieves one or more tuple at a time. instead of these stream of FETCH request to the server, we could enqueue results in advance in the client communication buffer


DBMS threads
threads were introduced was after database systems were first developed and commercialized. 
the implementation details of the OS threads vary greatly between systems
Hence for legacy, portability, and scalability reasons, many widely used DBMS do not depend on OS threads 
those that use process per worker or process pool do not face these problems but those that use the thread per worker model will face these problem hence we need a solution for that. 
the solution that was introduced was using lightweight thread packages that are handled by the database itself. 


admission control
there will be a point in the database lifecycle where it will start thrashing pages on disk due to the volume or request that it receives
in this case, instead of performing database related operations, the database spends most of its time replacing pages and thrashing
this is problem with query processing techniques such as sorting and hash joins that take up large amount of memory
hence admission control need which does the following, it does not accept new work unless sufficient DBMS resources are available