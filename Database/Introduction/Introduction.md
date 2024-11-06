System design goal 

Virtualizing the memory such that it gives an the database users the illusion that there are infinite amount of memory that the database system is running on 

Disk oriented system 
We have a disk which is logically divided into pages, the pages are identified using a page directory which contains valid page entry list 
In also have a buffer pool which is a section of the memory given to the database system by the OS. This buffer pool is where the pages are cached or stored temporarily. 
There is a higher level called the execution engine which based on the query that the user fires requests the buffer pool for pages which contains the respective data. If the buffer pool doesn't contain the page which the execution engine requires then it asks for the page from the page directory inside the disk and into the buffer pool and returns a pointer to the page address to the execution engine

This is the basic concept of virtual memory that the OS implements but we do not want the OS to perform any kind of operation in the pages needed by the dbms. 

Why not use the OS
OS uses an API called mmap() which maps a page on disk into memory making it as if the  pages were actually stored in memory and operations can be performed as if they where stored in memory. If a page requested by the execution engine is not found in the main memory then it fetches from the disk and maps the page from the disk into a memory location.
Why is this a bad thing?
- I/O stalls 
- OS performs blind read and write to the pages to and from the memory 
- Flushing of dirty pages from memory onto disk when page replacement policy are in place 
- doesn't consider DBMS as a special process. 

Database storage
# how the dbms represents data in files on the disk 

The database is collection of files on disk which is managed by the DBMS
A database can be a single file or multi file, both having their own tradeoffs. 

The format for the database files are proprietary to the dbms
So if a sqlite file where to be placed on the same directory as the mysql files and directories then we cannot expect mysql to read or parse the sqlite file.

The database files are stored on top of the file system provided by the OS i.e ntfs, ext4 but for the OS the database files are like any other regular files and directories. 

There have been many attempts to create a filesystem that is custom to run only database files and directories but the engineering required to create a custom filesystem is high and to maintain the filesystem is even harder plus the performance gain by creating a custom file system is very less 

Storage Manager 
Component of the DBMS responsible for managing database files on the disk 

All the reads and writes scheduled by the DBMS is done through the storage manager rather than through the OS, this improves the spatial and temporal locality of pages because the storage manager knows more about the DBMS than the OS.

The storage manager keeps track of the reads and writes performed on the pages as well as the free space available on the page 

Database pages 
A page is a fixed size block of data that makes up a single file i.e a file is a collection of pages.

A page contains information such as the metadata, tuples, indexes, logs and many more. 
We want pages to be self contained i.e the metadata of a tuple needs to be on the same page as the tuple this makes sure that data loss does not affect the tuple in any way. 
Most database systems do not allows mixing of data types i.e a page can contain only tuples or index value and such and such. 
Each page is identified using a page identifier generated the database system which adds an indirection layer to the pages by mapping the page id to a particular physical location where the page is located at. This allows rearranging of pages be less hectic since every change to the location of the page will make sure that the page_id is pointing to a new physical location. 
What is the size of a page? It depends on the level you are in: 
-> if in hardware level i.e disk or ssd's then 4kb is smallest unit of operation that can be done at a time 
-> if in OS level then 4kb as well. This means that at a time a OS can page in 4KB sized page into memory from the disk 
-> if the level is database then it again depends on the database in use, the smallest unit of working page of a database is 512 bytes and the largest unit of working page is 16KB. But since the hardware only guarantees a 4KB page operation at a time i.e a hardware ensures that a 4KB page operation is atomic, this can lead to torn writes if larger page sizes are selected and the system crashes before all the pages are written properly 

Page storage organization 
How are the pages in files on the disk organized?
- Heap file organization 
- sequential/sorted file organization 
- hashing file organization 

Heap file organization 
unordered collection of pages in a file and the tuples of the pages are stored in random order 
The file organization must provide the API to perform the following operations such as create/detele/update and insert, we must also be able to iterate over all the entires in the file. 
This means we need to arranges the pages in data structure that allows us the do the following operations such as storing the meta-data to know which pages exist in the file and which pages are free to use
There are two main data structures used to represent pages in the file 
- linked list 
- page directory 

Linked list organization of files 
We will have two head nodes, one which points to the the page data and another which points to empty pages. Using linked list we are able to perform all the above mentioned operations

Page directory 
Page header in the file which maintains a pointer to all the pages that are inside the file. This maps the page id to the page offset or physical location on the disk. 
The page directory also contains entries for all the free pages that are available in the file. 

Among linked list and page directory heap file organization, page directory is more widely used 

Page header 
the page header contains stuff like 
- page size 
- database version 
- compression information 
- checksum  -> this is used to check the validity of the page after a crash 
- transaction 

How are data inside the page stored? 
- tuple oriented 
- log structured 

Tuple oriented 
We assume that we are storing tuples directly into the page, appending them at the end one after another. This is a simple idea has and has a major flaw which is external fragmentation. Suppose a tuple in a middle position is deleted then if the tuples are of variable length then adding a tuple at the deleted position can lead to external fragmentation i.e used memory location that cannot be used by other tuples because the size of the free space is too less. To remove this problem we need to have a header information regarding where the free space in the pages are and sequentially scanning the page to find and compact the page to remove the fragmentation 
Another tuple oriented approach is the slotted pages approach where we will have a slot array which is basically a array of slots which points to the starting location of a tuple. Each slot array will also contain the size information about the tuple to make sure that a read to a tuple is within that tuple. This approach also has a disadvantage that we need extra space to store slot array.

How does the storage manager know where the tuple is located at?
A tuple is uniquely identified using record id. Each record id is a combination of the page id and the offset or the page slot no. This makes each tuple's record id unique to itself. when a query asks for a certain tuple then it looks at then index of the tuple which contains the record id. This record id is then broken down into page id and page slot no which eventually will help us identify the physical location of the tuple 

In postgresql we can use the following sql statement to get the page id and offset pair:
```sql
SELECT <table_name>.ctid, <table_name>.* FROM <table_name>;
```

What happens when we remove a tuple in the middle that creates a hole?
Since the slotted page approach is made for variable sized tuples we need to make sure that external fragmentation does not occur. How can we make sure of this? This is done using compaction. Whenever there is free space the storage engine is going to scan through the page and compact the page making sure that all the holes are gone. Another thing to note is that the slot array should be in sync with the operation that is being performed i.e for each tuple operation we need to make sure the slot array is updated as well. 

What exactly are tuples and how are they organized in inside the disk 
Tuples are collection of bytes. And the job of the storage engine is to interpret those bytes into attribute types and values. Tuples can contain header information among themselves just like pages do but they are also system dependent i.e different system will have different approach. Instead of storing tuple information inside the tuple it can be stored in layers above it i.e pages etc. 
The tuples are stored  in the order in which they are created. Suppose we have two attributes a and b, a is created before b. Here the record for the attribute a is going to be stored first than b. This is not necessary but most systems opt to do this. 

Denormalized tuple data 
Most of the time tuples of different tables are not stored in the same page. But this condition can be neglected when we pre join tables inside the same page. Normalizing is the process of breaking down a table into multiple tables, whereas denormalization is the process of joining multiple tables that are related. 

Problem with slotted array approach:
1. fragmentation ->  tuples of a single table may be placed on different pages
2. useless i/o -> block oriented approach disadvantage. Basically when we want to update a single tuple then we need to bring in the entire page because database storage manager works on a single block rather than a tuple. 
3. random i/o -> updating multiple tuples that are located in multiple pages is going to result in multiple random writes. This is a bad thing for non-volatile storage because sequential writes are the best thing for non-volatile storage 


Log structured file system 
in log structure file system approach, are the values in the physical location of the tuple also update or are the log records only updated?id,
A system where we cannot overwrite an existing data but keep appending new data in to the disk. This is the goal of log structured file system 
In log structured file system we are only allowed to PUT or DELETE log records i.e a page is composed up of logs rather than tuples. 
Every log record contains a unique identifier which identifies a tuple in the disk.
A log contains information about the operation performed inside the log.
The log is going to be maintained inside the main memory. 
A simple log record looks something like this PUT #123 val=a1
instead of overwriting a log record a new log record is appended to the end of the in-memory page. When the in memory page gets full then it gets flushed to the disk. To flush the in memory page into the disk we need to consult the page directory to find a free page slot then insert into the free page slots. The page inside the disk is immutable i.e we do not want to change the content of the log records inside the page.
Reading from the log structured is trickier than writing because we need to find the latest log record associated with the tuple id or record id.  We can do this sequentially but that is slow. What we do instead is use index. 
What is an index?
An index is like a glossary, we lookup a word in the end of the book and it goings to a page, we go to the page no and find the associated word. Similar a index in database in log structured approach points to the latest record associated with the tuple id.

Log structured compaction 
log records inside page are going to grow forever. To remove this problem we can compaction two pages by comparing them and only keeping log records that are latest to a particular tuple id. The log records are written to a new free page slot and the previous two pages are freed up. We can then sort then tuple for a for efficient search such as a binary search. This avoids using fine grained indexes to search records faster. 

Sorted compacted pages on disk are called sorted string table 

DEL log records of tuples need not be necessary because if they are deleted then they either might have have been deleted or they might have never existed in the first place. So we do not keep track of DEL log records during compaction 

Tuples are collection of attributes which in turn are just collection of bytes. Pages are collection of tuples and there are two ways to represent the values inside a page i.e 
1. Tuple oriented approach 
	- Direct tuple  -> we store tuples directly into page from the starting location of the page until the page fills. This approach introduces the problem of external fragmentation so is not used in many systems.
	- slotted page approach
2. Log structured approach -> key value storage of tuple id (which is provided by layers above) and collection of bytes with GET, PUT and DELETE operations in the log record. The system does not know what is in the value portion, that is the job of the actual dbms to interpret those bytes into meaningful information. 

Drawbacks of using log structured approach:
- Write-amplification -> Suppose a log record where never updated i.e for a tuple there is only one log record associated with it then during compaction that tuple is going to be read and written back multiple times. (During compaction the pages needs to be brought into the memory)

Tuple storage 
How are large values stored inside a tuple?
Most dbms do not let you store tuples that are greater than the size of the page 
overflow storage pages
base tuple where your page no and offset points to will now point to another page that is typically larger than the original table page. When the overflow page will be used will be dependent on the system that is being used. 
External storage

Database catalog 

OLTP 
OLAP
Data storage models 
n-ary or row storage model  -> ideal for OLTP workload 
Decomposition storage model or column storage model -> ideal for OLAP workload 
Common domains of tuples within a table are going to be placed together into a single page. For example, we have a table with a age attribute then we can store inside a page all the values of age corresponding to that table.
Why is this is a good thing 
Let us take an example query which only searches through either some attributes of a tuple rather than the entire tuple then what happens is when 

What are the advantages and disadvantages of column based storage model 

How to find a corresponding attribute of a tuple in a column based storage model 
- Fixed length offset 
- embedded tuple id 

Data compression 

Goals of data compress 
- lossless scheme 
- postpone decomposition or decompress of data for as long as possible during query execution. Why?
- Provide fixed length compressed data 

## System Catalog
Maintaining a data about data. They are also called as data dictionary. The information that the system must store in the catalog includes: 
- the name of the relation, the attributes of the relation, the size of the attributes of the relation, name of the views defined in the relation, integrity constraints such as key constraint, foreign key constraints defined in the relation.
The metadata about the database itself is a miniature database.
There can be relations about all the available relations in the database that can be viewed before working with any relation. The tuples of the relations can contains information about the disk location or file location of the relation. 
The metadata database is loaded into the main memory during the startup of the database system because they are accessed alot in the lifetime of the database operations.


The components of the database includes the following:
 1. Disk Manager 
 2. Buffer pool Manager 
 3. Access Methods 
 4. Operator Execution