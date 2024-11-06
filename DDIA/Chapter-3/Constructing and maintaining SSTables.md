SSTables are data structures that are used on disk but reads and writes first persist in memory. Maintaining a sorted structure on disk is possible by using b-tress. Maintaining a sorted structure in-memory is easier using various structures such as red-black trees and AVL tress. No matter the order of writes to the memory, the result is always a sorted sequence of key value pairs. 

1. When a write request comes in, it is intercepted by the balancing tree (red-black or AVL). This in-memory structure is also called a [[Memtable]]
2. The [[Memtable]] has a threshold (it can only hold some amount of key value pairs), once the [[Memtable]] exceeds the threshold then the pairs are written down on disk to the SSTables. This segment becomes most recent segment of the database 
3. In order to serve the read request, we need to first try the [[Memtable]] then scan the most recent segment on disk then the second most recent segment and so on. 
4. From time to time we run compaction and merging on the segment records. 

This method has one drawback, if the database loses power then all the [[Memtable]] contents are gone. To avoid the loss, we need to keep a backup log on disk such that for read write request, first the log is appended with the new write request then only the [[Memtable]]. Once the power comes back the [[Memtable]] can look into the log and reconstruct the table as previously mentioned.

