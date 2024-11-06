Hash tables are in-memory data structures which means that they can be loaded in our computer memory.

Since we already have this data structure in memory which not use this as our index?

Suppose we are using the same append only database then the simplest indexing strategy is to keep an in-memory hash map where every keep is mapped to a byte offset in the physical file location

![[Screenshot 2024-10-19 at 08.18.06.png]]

As mentioned before,, whenever we update the database we also have to update the index to keep the index in sync with database and provide consistency

This approach is used by BitCask (default storage engine for Riak). Since we are storing the key and a pointer to the filesystem location, values can use more space than available memory
In thing to keep in mind is that we need to make sure the keys of the key-value pair can all be added to the memory. For example, a workload where we have key as URL to a cat video and the value is the no of times the video has been played, then the workload, there is a lot of writes, but there are not too distinct keys i.e there are a large number of writes per key, but it is also feasible to keep them all in memory.

how to avoid running out of disk space?
break the log into segments of a certain size such that when we reach the maximum segment size we start using a new segment. This means we have multiple segments each having data. We can also perform compaction in each segment because the comparative size of the segment would be smaller than the log. 
We can also perform [[Compaction]] and [[Merging]].

While the [[Compaction]] and [[Merging]] is happening in the background thread, we can continue serving read and write request from the old segment

Problems while implementing this in practice:
1. File format  -> CSV format i.e key value separated by comma is not the best format for log. It's faster to use binary format 
2. Deleting records -> To delete a key from and its associated value on disk, we need to append a special deletion record to the file called tombstone such that in the process of merging and compaction we can remove those records from the new segment.
3. Crash recovery -> If the database is restarted then the in-memory hash index is lost. To recover we have to read all the segments on disk and create a hash index out of it (this process is incredibly slow) so instead what bitcask does is creates a snapshot of the current state of the hash index and saves that on the disk such that it only needs to load that saved snapshot rather than reading the whole segment.
4. Partially written records -> Database can crash halfway through the append process. To detect such corruptions BitCask uses checksums
5. Concurrency control -> To prevent the database from race conditions and inconsistency due to write from multiple threads, we can implement a single write thread and multiple read thread implementation

Why is hash index or append only log a good approach:
1. appending and segment merging are sequential operation and for magnetic disks, sequential operation performs well than random operations.
2. Concurrency and crash recovery is simpler because the records in the log or immutable. When a crash happens we do not overwrite the previous value which means we will have both the new value as well as the new partial value in the log. 
3. Merging avoids the problem of [[data fragmentation]]

Why is hash index not a good approach:
1. The hash table must fit all the keys in memory which means if the memory is small then we run out of luck. We can store the index on disk but they are slow and require a lot of random access
2. Range queries like for loop are not available in hash indexes and we have to select one key value pair at a time.