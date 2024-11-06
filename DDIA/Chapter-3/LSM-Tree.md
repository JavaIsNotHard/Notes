LSM-trees stand for log-structured tree. They are used with [[SSTables]] (which is a format to store data on disk).  LSM tree use the concept of [[Memtable]] which was previously described. 

Storage engine based on the principle of merging and compaction are called LSM storage engine. 

[[Performance Optimization of LSM-trees]]

LSM-tree also has the advantage of being able to perform range queries
