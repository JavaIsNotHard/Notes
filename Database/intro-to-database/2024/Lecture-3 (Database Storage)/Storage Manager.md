Responsible for managing the files on disk 
basically moving data back and forth from disk to memory and vice versa
operations like scheduling disk writes and memory flush to disk are handled by storage manager
which operations are batched and which are send immediately

Files are collection of pages
the DBMS is responsible for tracking with is being read and written to this pages
how to reuse space, how to perform compaction, how to expand data across pages are also responsible of storage manager

[[Database Pages]]