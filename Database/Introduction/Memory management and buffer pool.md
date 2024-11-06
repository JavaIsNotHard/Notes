memory management & buffer pool manager 
How are pages on disk brought to memory and how are they written back to memory?

What is a buffer pool? 
-> A section of the memory that the database program is running on. This is also called a buffer cache or a disk cache which basically is used t imply that it works as a cache between the disk and the database program 

The buffer pool manager manages the contains of the buffer pool i.e checks which pages to evict out, which pages to write back to the disk which pages are to be kept on buffering and more. 

Buffer pool contains array of memory section called as frames. These frames are where the buffer pool manager places pages in. The buffer pool is divided into fixed sized page length section which is equal to the page size on the disk. 

When an execution engine asks for a page then it receives a pointer to the location of the page on disk through an indirection layer called as the page table. The page table is different than the page directory. The page table resides on the memory whereas the page directory resides on the files which points to slots of pages and their location. 

The page table also contains meta-data about the page such as 
- dirty bit
- pin/reference bit 
The page table contains page table entries which in turn contains location of the page in the disk. 

Locks vs Latches in the database world vs the OS world.

## Allocation policies 
- Global policies  ->  
- Local policies  ->

## buffer pool optimization 
- multiple buffer pool
- prefetching 
- scan sharing : The main concept of scan sharing is to make use of data brought into memory by one query and sharing or allowing other query to access that data. 
	This allows multiple queries to attach to a single cursor which scans the tables needed by all the queries. This feature makes sure that we do not have multiple cursor conflict each other while accessing pages on memory.
- buffer pool bypass :  maintaining a private buffer pool for a query which the dbms manages for each query and evict each pages from the private buffer pool whenever the query  needs more memory. The problem with this approach is going to be not able to share memory among queries 

## OS page cache 
os maintains a page cache below the file system that stores pages that the OS reads from the disk. The DBMS calls a system call such as read() to the file system. The file system then checks the page cache to see if the corresponding page is in the cache, if the page is not in the cache then it goes to the disk to fetch the page. This is a slow process. The DBMS is giving away control of what is in the memory.
Most DBMS except for postgres does not use this process. Why?
-> The Database loses control over the memory 
-> Redundant copies of the same pages in the OS page cache as well as the database buffer pool 
-> Different eviction policies of the OS and DBMS

Page replacement policy 
- LRU 
- Clock 
The problem with LRU and clock is sequential flooding 
Sequential flooding : when we are doing sequential scans across a page then there will be pages that are brought into the buffer pool which may not be used in the near future. Both the LRU and the clock algorithm are going to evict pages that might be needed in the future by another query. 
The solution is to use LRU-K algorithm : 
LRU-K : instead of having a single timestamp we also have the number of last k times the page was referenced. Now instead of looking at the page with the oldest timestamp we look at the difference between the first time the page was accessed and the last time the page was accessed to get the page which hasn't been access for a long time. 
We can thing of K = 2 as a stack for example, the first reference to a page places a timestamp into the bottom of the stack, another reference places the page at the top, and finally another reference will remove the top of the stack page and replace it.
For K = 3 or more, We can maintain an access pattern by looking at how the pages was referenced 3 times.

## Better policy: priority hints 
flag pages that are more important than others. Pages that are access frequently such as a index page of a B+ tree are important to the DBMS so it can request the buffer pool to not evict this page in the near future. (This is not equivalent to the pin operation)

## Dirty pages 
If we want to remove pages from the buffer pool when it needs space to bring in more pages then it can look at the bits and decide. One of the deciding factor is the dirty bit